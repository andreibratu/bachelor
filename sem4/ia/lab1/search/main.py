from controller.controller import CommandLineController
from service.problem_service import ProblemService

if __name__ == '__main__':
    service = ProblemService()
    controller = CommandLineController(service)
    controller.loop()