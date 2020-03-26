from PyQt5.QtCore import QThread, pyqtSignal


class Worker(QThread):

    """Worker responsible with computing the optimization task."""

    def __init__(self):
        QThread.__init__(self)
        self.result = None
        self.func = None
        self.args = None
        self.running = False

    def set_task(self, func, args):
        """Set the method to by run in parallel, and its call arguments."""
        self.func = func
        self.args = args

    def run(self):
        """Inject logging signal and call the method with args."""
        self.running = True
        self.result = self.func(*self.args)
        self.running = False
