from typing import List
import os


class FileRepository:
    """Abstract implementation of a file-based repository."""


    def __init__(self, path: str, file_manager, extra_args: List = None):
        self._path = path
        self._file_manager = file_manager
        self._args = ['_objects', '_counter']

        if extra_args is not None:
            self._args += extra_args

        if os.stat(self._path).st_size != 0:
            with open(self._path, self._file_manager.read_mode) as f:
                db = self._file_manager.load(f)
                for arg in self._args:
                    if arg == '_objects':
                        self._objects = {
                            int(k): v for k, v in db['_objects'].items()
                        }
                    else:
                        setattr(self, arg, db[arg])


    def __del__(self):
        with open(self._path, self._file_manager.write_mode) as f:
            db = {arg: getattr(self, arg) for arg in self._args}
            self._file_manager.dump(db, f)
