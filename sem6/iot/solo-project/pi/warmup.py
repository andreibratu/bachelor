import torch
import soundfile as sf
from firebase_admin import credentials
from firebase_admin import firestore
import firebase_admin
from transformers import Wav2Vec2Tokenizer, Wav2Vec2ForCTC

tokenizer = Wav2Vec2Tokenizer.from_pretrained("facebook/wav2vec2-base-960h")
model = Wav2Vec2ForCTC.from_pretrained("facebook/wav2vec2-base-960h")
