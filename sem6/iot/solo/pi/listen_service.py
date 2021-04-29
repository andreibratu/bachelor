import os
import sys
import time
import string
import logging
import subprocess
import multiprocessing
from typing import List
from random import choice
from copy import deepcopy

import wave
import torch
import pyaudio
import firebase_admin
import soundfile as sf
from firebase_admin import credentials
from firebase_admin import firestore
from transformers import Wav2Vec2Tokenizer, Wav2Vec2ForCTC


class Keyword:
    def __init__(self, id: str, keyword: str, count: int):
        self.id = id
        self.keyword = keyword
        self.count = count

    def __str__(self):
        return f"[KEYWORD {id} {self.keyword} {self.count}"

    __repr__ = __str__


# Firebase config
cred = credentials.Certificate("firebase.key.json")
firebase_admin.initialize_app(cred)
FIREBASE_DB = firestore.client()

# Logger config
logging.basicConfig(
    format="%(asctime)s %(levelname)-8s %(message)s",
    level=logging.INFO,
    datefmt="%Y-%m-%d %H:%M:%S",
)
LOGGER = logging.getLogger("list.service")
LOGGER.setLevel(level=logging.INFO)
fh = logging.FileHandler("listen.service.log", mode="w+")
LOGGER.addHandler(fh)

# Constants
RECOGNIZE_WORKERS_COUNT = 3
WAIT_SECS = 0
FORMAT = pyaudio.paInt16
CHANNELS = 1
RATE = 44100
CHUNK = 1024
RECORD_SECONDS = 10

AUDIO = pyaudio.PyAudio()


def _record(file_path: str):
    try:
        stream = AUDIO.open(
            format=FORMAT,
            channels=CHANNELS,
            rate=RATE,
            input=True,
            frames_per_buffer=CHUNK,
            input_device_index=0,
        )
        frames = []

        for i in range(0, int(RATE / CHUNK * RECORD_SECONDS)):
            data = stream.read(CHUNK)
            frames.append(data)

        stream.stop_stream()
        stream.close()

        waveFile = wave.open(file_path, "wb")
        waveFile.setnchannels(CHANNELS)
        waveFile.setsampwidth(AUDIO.get_sample_size(FORMAT))
        waveFile.setframerate(RATE)
        waveFile.writeframes(b"".join(frames))
        waveFile.close()
    except Exception as e:
        exc_type, exc_obj, exc_tb = sys.exc_info()
        lineno = exc_tb.tb_lineno
        LOGGER.error(f"Line {lineno} [_recoord]: {e}")
        raise e


def _fetch_keywords() -> List[Keyword]:
    docs = FIREBASE_DB.collection("keywords").stream()
    docs = [{**d.to_dict(), "id": d.id} for d in docs]
    LOGGER.info(f"[_fetch_keywords]: {docs}")
    kws = list(
        map(
            lambda x: Keyword(
                id=x["id"], keyword=x["keyword"], count=x["count"]
            ),
            docs,
        )
    )
    return kws

    LOGGER.info(f"[_recognition_worker {os.getpid()}]: Fetched keywords {kws}")


@firestore.transactional
def _increment_kw_occurences(transaction, kw: Keyword):
    # Update occurences for keyword identified by [id] atomically
    try:
        kw_ref = FIREBASE_DB.collection("keywords").document(kw.id)
        snapshot = kw_ref.get(transaction=transaction)
        transaction.update(kw_ref, {"count": snapshot.get("count") + 1})
        LOGGER.info(
            f"[_increment_kw_occurences]: Incremented {kw.keyword} to {kw.count + 1}"
        )
    except Exception as e:
        exc_type, exc_obj, exc_tb = sys.exc_info()
        lineno = exc_tb.tb_lineno
        LOGGER.error(f"Line {lineno} [_increment_kw_occurences]: {e}")
        raise e


def _generate_string(len: int) -> str:
    try:
        # Generate a random string of given [len] to identify a recorded sample
        return "".join([choice(string.ascii_letters) for _ in range(len)])
    except Exception as e:
        exc_type, exc_obj, exc_tb = sys.exc_info()
        lineno = exc_tb.tb_lineno
        LOGGER.error(f"Line {lineno} [_generate_string]: {e}")
        raise e


def _upload_worker(log_queue: multiprocessing.Queue):
    # Upload phrases containing keywords
    try:
        LOGGER.info(f"[_upload_worker {os.getpid()}]: Says hello")

        logs = FIREBASE_DB.collection("logs")
        while True:
            transcription, kws = log_queue.get()
            for kw in kws:
                transaction = FIREBASE_DB.transaction()
                _increment_kw_occurences(transaction, kw)
            new_log_ref = FIREBASE_DB.collection("logs").document()
            new_log_ref.set(
                {
                    "phrase": transcription,
                    "keywords": [kw.keyword for kw in kws],
                    "timestamp": firestore.SERVER_TIMESTAMP,
                }
            )
    except Exception as e:
        exc_type, exc_obj, exc_tb = sys.exc_info()
        lineno = exc_tb.tb_lineno
        LOGGER.error(f"Line {lineno} [_upload_worker]: {e}")
        raise e


def _recognition_worker(
    file_queue: multiprocessing.Queue,
    log_queue: multiprocessing.Queue,
) -> str:
    # Extract text from soundfiles using hugging face model
    # huggingface.co/facebook/wav2vec2-base-960h

    try:
        LOGGER.info(f"[_recognition_worker {os.getpid()}]: Says hello")

        # Init models
        tokenizer = Wav2Vec2Tokenizer.from_pretrained(
            "facebook/wav2vec2-large-960h-lv60-self"
        )
        model = Wav2Vec2ForCTC.from_pretrained(
            "facebook/wav2vec2-large-960h-lv60-self"
        )

        LOGGER.info(
            f"[_recognition_worker {os.getpid()}]: Speech models are up"
        )

        while True:
            # Read audio file
            file_path = file_queue.get()
            kws = _fetch_keywords()
            speech, _ = sf.read(file_path)
            LOGGER.info(
                f"[_recognition_worker {os.getpid()}]: Received {file_path} @ {time.ctime()}"
            )

            # Tokenize
            input_values = tokenizer(
                speech, return_tensors="pt", padding="longest"
            ).input_values  # Batch size 1

            # Retrieve logits
            logits = model(input_values).logits

            # Take argmax and decode
            predicted_ids = torch.argmax(logits, dim=-1)
            transcription = tokenizer.batch_decode(predicted_ids)[0]

            words = list(map(lambda w: w.lower(), transcription.split(" ")))
            LOGGER.info(
                f"[_recognition_worker {os.getpid()}]: Transcription <<{words}>>"
            )
            recognized_kws = []
            for kw in kws:
                for w in words:
                    if w == kw.keyword:
                        recognized_kws.append(deepcopy(kw))
            if len(recognized_kws) != 0:
                logging.info(
                    f"[_recognition_worker {os.getpid()}]: Match {[x.keyword for x in recognized_kws]} for {words}"
                )
                log_queue.put((transcription, recognized_kws))
            # Clean up after processing
            os.remove(file_path)
            LOGGER.info(
                f"[_recognition_worker {os.getpid()}]: Cleaned up {file_path}"
            )
    except Exception as e:
        exc_type, exc_obj, exc_tb = sys.exc_info()
        lineno = exc_tb.tb_lineno
        LOGGER.error(f"Line {lineno} [_recognition_worker]: {e}")
        raise e


if __name__ == "__main__":
    try:
        file_queue = multiprocessing.Queue()
        log_queue = multiprocessing.Queue()
        workers = [
            multiprocessing.Process(
                target=_recognition_worker,
                args=(
                    file_queue,
                    log_queue,
                ),
            )
            for _ in range(RECOGNIZE_WORKERS_COUNT)
        ] + [multiprocessing.Process(target=_upload_worker, args=(log_queue,))]
        for worker in workers:
            worker.start()
        # Wait for workers to init models
        LOGGER.info(
            f"[__main__]: Sleeping {WAIT_SECS} seconds to wait for models"
        )
        time.sleep(WAIT_SECS)
        LOGGER.info("[__main__]: Started to listen")
        while True:
            # Start listening
            path = f"{_generate_string(10)}.wav"
            LOGGER.info(f"[__main__]: Recording {path}")
            _record(path)
            LOGGER.info(f"[__main__]: Recorded {path}")
            file_queue.put(path)
    except Exception as e:
        exc_type, exc_obj, exc_tb = sys.exc_info()
        lineno = exc_tb.tb_lineno
        LOGGER.error(f"Line {lineno} [__main__]: {e}")
        raise e
