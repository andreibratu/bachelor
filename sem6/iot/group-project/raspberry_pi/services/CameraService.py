from picamera import PiCamera

from paths import Paths


class CameraService:
    def __init__(self):
        self._camera = PiCamera()

    def take_photo(self):
        self._camera.resolution = (1920, 1920)
        self._camera.framerate = 15
        self._camera.start_preview()
        self._camera.capture(Paths.image_path)
        self._camera.stop_preview()
