from typing import List, TypeVar
from copy import deepcopy


T = TypeVar('T')


class Iterator:


    def __init__(self, list: List[T]):
        self.__c = list
        self.__idx = 0


    def first(self):
        self.idx = 0


    def valid(self) -> bool:
        return this.idx < len(self.c)


    def getCurrent(self) -> T:
        if self.valid():
            return self.c[idx]
        else:
            raise Exception


    def next(self):
        self.idx++
