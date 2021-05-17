from services.FaceRecognition import FaceRecognition
from services.NetworkService import NetworkService
from services.CameraService import CameraService

from services.GPIOManager import GPIOManager
from services.UsersManager import UsersManager


class Engine:
    __instance = None

    def __init__(self):
        self.network_service: NetworkService = NetworkService(self)
        self.gpio_manager: GPIOManager = GPIOManager()
        self.camera_service: CameraService = CameraService()
        self.face_recognition: FaceRecognition = FaceRecognition(self)
        self.user_manager: UsersManager = UsersManager()

    def initialize(self):
        self.gpio_manager.setup()
        self.network_service.initialize()

    @staticmethod
    def get_instance():
        if Engine.__instance is None:
            Engine.__instance = Engine()

        return Engine.__instance
