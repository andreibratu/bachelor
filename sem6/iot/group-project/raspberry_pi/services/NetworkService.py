import threading
import uuid
import time
import urllib.request
import firebase_admin

from firebase_admin import credentials
from firebase_admin import firestore
from firebase import Firebase
from firebase import Storage

import paths
from models.attempt import Attempt
from models.user import User


class NetworkService:

    def __init__(self, engine):
        self.__cred = None
        self.__default_app = None
        self.__db = None
        self.__storage: Storage = None
        self.__isRunning = True
        self.__engine = engine

    def initialize(self):
        self.__cred = credentials.Certificate("./anna-59816-firebase-adminsdk-poyno-31fac5515c.json")
        self.__default_app = firebase_admin.initialize_app(self.__cred)
        self.__db = firestore.client()

        firebaseConfig = {
            'apiKey': "AIzaSyACDTkM3UQ7VruNao6zANuyBScBuwJz-1A",
            'authDomain': "anna-59816.firebaseapp.com",
            'projectId': "anna-59816",
            'storageBucket': "anna-59816.appspot.com",
            'messagingSenderId': "995680614256",
            'appId': "1:995680614256:web:9a8d08d0b75dcaf5ea01b5",
            'measurementId': "G-3B7X6Y7MLR",
            "databaseURL": ""
        }

        fb = Firebase(firebaseConfig)
        self.__storage = fb.storage()
        self.__start_task()

    def add_attempt(self, attempt: Attempt):
        new_ref = self.__db.collection('attempts').document()
        new_ref.set(
            {
                "createdAt": str(attempt.create_date),
                "photoUrl": attempt.photo_url,
                "userID": attempt.user_id
            }
        )

    def download_photo(self, url):
        buffer = urllib.request.urlopen(url)
        with open(paths.Paths.downloaded_image_path, "wb") as file:
            file.write(buffer.read())
    
    def update_user(self, user):
        new_ref = self.__db.collection('users').document(user.id)
        # new_ref.update(
        #     {
        #         "coordinates": user.coordinates.tolist()
        #     }
        # )

    def upload_photo(self):
        image_id = str(uuid.uuid4())
        path = "./" + paths.Paths.image_path
        self.__storage.child("attempts/" + image_id + ".jpg").put(path)

        return image_id

    def shutdown(self):
        self.__isRunning = False

    def __get_users_from_db(self):
        ref = self.__db.collection("users")
        objs = ref.stream()
        objs = [{**o.to_dict(), "id": o.id} for o in objs]

        users = []
        for obj in objs:
            user = User.create_from(obj)
            if user.coordinates is None:
                self.download_photo(user.photoUrl)
                user.coordinates = self.__engine.face_recognition.predict(paths.Paths.downloaded_image_path)
                self.update_user(user)
            if len(user.coordinates) > 0:
                users.append(user)
        print("Sync ended")
        self.__engine.user_manager.set_users(users)

    def __start_task(self):
        task = threading.Thread(target=self.__sync_local_users)
        task.start()
        pass

    def __sync_local_users(self):
        while self.__isRunning:
            print("Sync with db")
            self.__get_users_from_db()
            time.sleep(30)
