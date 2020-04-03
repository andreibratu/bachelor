from PyQt5.QtCore import QThread, pyqtSignal


class ValidationWorker(QThread):

    """Worker responsible with the validation task."""

    fitness_update = pyqtSignal(list, list)

    def __init__(self, data_points: int, evaluations: int):
        QThread.__init__(self)
        self.func = None
        self.args = None
        self.evaluations = evaluations
        self.running = False
        self.data_points = data_points
        self.results = []

    def set_task(self, func, args):
        self.func = func
        self.args = args

    def run(self):
        self.running = True
        args = list(self.args)
        for i in range(self.evaluations):
            result = self.func(*args)
            self.results.append(result[1])
        self.running = False
        # self.x = [idx for idx in range(len(self.results))][-self.data_points:]
        # self.y = self.results[-self.data_points:]
