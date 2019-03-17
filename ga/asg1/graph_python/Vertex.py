from typing import TypeVar
from Iterator import Iterator


T = TypeVar('T')


class Vertex:

    def __init__(self, label: T):
        self.label = label
        self.__inbound = []
        self.__outbound = []


    def remove_inbound(self, label: T):
        try:
            idx = self.inbound.index(label)
            self.pop(idx)
        except ValueError:
            pass


    def remove_outbound(self, label: T):
        try:
            idx = self.outbound.index(label)
            self.pop(idx)
        except ValueError:
            pass


    def get_degree_in(self) -> int:
        return len(self.inbound)


    def get_degree_out(self) -> int:
        return len(self.outbound)


    def add_inbound(self, label: T) -> bool:
        try:
            idx = self.inbound.index(label)
            return False
        except ValueError:
            self.inbound.append(label)
            return True


    def add_outbound(self, label: T) -> bool:
        try:
            idx = self.outbound.index(label)
            return False
        except ValueError:
            self.outbound.append(label)
            return True


    def get_inbound_edges_iterator(self) -> Iterator:
        return Iterator(self.inbound)


    def get_outbound_edges_iterator(self) -> Iterator:
        return Iterator(self.outbound)
