import time
import uuid

from models.attempt import Attempt
from services.CameraService import CameraService
from services.Engine import Engine
from services.FaceRecognition import FaceRecognition
from services.GPIOManager import GPIOManager
from services.NetworkService import NetworkService


def action(_):
    print("\nSnapping photo!")
    camera_service.take_photo()

    attempt = create_attempt()
    allowed = face_recognition.recognize(attempt)
    network_service.add_attempt(attempt)

    print('✓ Allowed' if allowed else '✗ Not allowed')
    gpio_manager.turn_on_led(allowed)
    time.sleep(5)
    gpio_manager.turn_off_leds()
    time.sleep(1)


def create_attempt():
    image_id = network_service.upload_photo()
    attempt = Attempt()
    attempt.photo_url = image_id
    return attempt


if __name__ == '__main__':
    engine = Engine.get_instance()
    engine.initialize()
    gpio_manager = engine.gpio_manager
    camera_service = engine.camera_service
    network_service = engine.network_service
    face_recognition = engine.face_recognition
    gpio_manager.add_callback(action)
    try:
        print("Listening...")
        while True:
            pass
    except KeyboardInterrupt:
        GPIOManager.cleanup()
