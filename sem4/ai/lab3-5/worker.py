from PyQt5.QtCore import QThread, pyqtSignal


class Worker(QThread):
    """
    Run arbitrary `func` method on a separate thread
    """

    # All signals should be declared as class variables
    metrics = pyqtSignal(float, float, int)

    def __init__(self):
        QThread.__init__(self)
        self.result = None
        self.func = None
        self.args = None

    def set_task(self, func, args):
        """Set the method to by run in parallel, and its call arguments."""
        self.func = func
        self.args = args

    def run(self):
        """Inject logging signal and call the method with args."""
        args = list(self.args) + [self.metrics]
        result = self.func(*args)
        self.result = result
