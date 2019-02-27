import pickle
import jsonpickle


class FileManager:
    """Helper class that wraps file modules to provide a common interface."""

    def __init__(self, type: str):
        self.type = type
        if type == 'pickle':
            self.dump = lambda o, f: pickle.dump(o, f)
            self.load = pickle.load
            self.read_mode = 'rb'
            self.write_mode = 'wb'
        if type == 'json':
            self.read_mode = 'r'
            self.write_mode = 'w'
            self.load = lambda f: jsonpickle.decode(f.read(), keys=True)
            self.dump = lambda o, f: f.write(jsonpickle.encode(o))
