import cv2
import numpy as np
from PIL import Image

face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')


def process_image(img_path: str) -> np.ndarray:
    # Return a processed image plus its name from path

    # Read image from path
    img = cv2.imread(img_path)
    img = cv2.cvtColor(img, cv2.COLOR_RGB2GRAY)
    img = cv2.equalizeHist(img)

    # Use CV to get rectangle containing the face
    rects = face_cascade.detectMultiScale(img)
    if len(rects) == 0:
        return None
    x1, y1, w, h = rects[0]
    x2 = x1 + w - 1
    y2 = y1 + h - 1

    # # Crop the face, process, and return it
    face_rect = img[y1:y2, x1:x2]
    face_rect = img
    face_rect = cv2.resize(face_rect, dsize=(
        96, 96), interpolation=cv2.INTER_CUBIC)
    arr = face_rect / 255
    arr = np.reshape(arr, (-1, 96, 96, 1))
    return arr