class Logger:

    instance = None

    def __init__(self, path):
        self._file_handler = open(path, 'w+')

    @staticmethod
    def get_logger():
        if Logger.instance is None:
            Logger.instance = Logger('output.txt')
        return Logger.instance

    def log(self, message: str):
        print(message)
        self._file_handler.write(f'{message}\n')

    def __del__(self):
        self._file_handler.flush()
        self._file_handler.close()
