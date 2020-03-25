from service import ProblemService
from ui import UserInterface

service = ProblemService()
ui = UserInterface(service)

if __name__ == '__main__':
    ui.loop()