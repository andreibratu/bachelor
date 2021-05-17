from random import random
from utils.ImageHelper import process_image
from models.attempt import Attempt
from paths import Paths

import tensorflow as tf


class FaceRecognition:
    def __init__(self, engine):
        self._model = tf.keras.models.load_model('best_model')
        self._engine = engine
        # print(self._model.summary())

    def euclid(self, x1, x2, y1, y2):
        return (x1 - x2) ** 2 + (y1 - y2) ** 2


    def analyse_distances(self, v1, v2):
        sum = 0
        maximum = -99999
        minimum = 99999
        for i in range(len(v1)):
            if i % 2 == 0:
                distance = self.euclid(v1[i], v2[i], v1[i + 1], v2[i + 1])
                maximum = max(maximum, distance)
                minimum = min(minimum, distance)
                sum += distance
        mean = sum / (len(v1) // 2)
        return mean, maximum, minimum
    
    def is_recognized(self, known_data, snapped_data): 
        mean, maximum, minimum = self.analyse_distances(known_data, snapped_data)
        print("\n\nVALUE OBTAINED: \n\n", 48 * minimum)
        return 48 * minimum < 0.05
    
    def predict(self, image_path):
        image_data = process_image(image_path)
        if image_data is None:
            return []
        return self._model.predict(image_data)[0]

    def print_debug_data(self, points):
        print("POINTS", points.shape, points)
        s = ''
        for i in range(len(points)):
            if i % 2 == 0:
                s += " (" + str(points[i]) + ", " + str(points[i + 1]) + "), "
        print("\nPOINTS FORMATTED\n", s)

    def recognize(self, attempt: Attempt):
        image_data = process_image(Paths.image_path)
        if image_data is None:
            return False
        points = self._model.predict(image_data)[0]
        self.print_debug_data(points)
        users = self._engine.user_manager.get_users()
        for user in users: 
            if self.is_recognized(user.coordinates, points):
                attempt.user_id = user.id
                return True
        return False
        # return random() >= 0.5 

