from controller import HomeworkController
from repo import HomeworkRepository
from ui import UI
from tests import run_tests


run_tests()

repo = HomeworkRepository()
controller = HomeworkController(hw_repo=repo)
ui = UI(hw_controller=controller)

ui.loop()
