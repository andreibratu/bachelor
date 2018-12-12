from typing import List
import jsonpickle

from repos.abstract_repos.file_repository import FileRepository


class JsonRepository(FileRepository):


    def __init__(self, path: str, extra_args: List = None):
        FileRepository.__init__(
            self,
            path=path,
            extra_args=extra_args,
            file_manager=jsonpickle
        )
