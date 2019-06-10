from typing import List, TypeVar
from functools import filter
from Vertex import Vertex
from Iterator import Iterator

T = TypeVar('T')

class Graph:

    def __init__(self):
        self.__vertices = []
        self.__edges = {}


    def __find_vertex(label: T) -> Vertex:
        """Find vertex with given label.

        Raises:
            IndexError: No such vertex exists
        """
        return filter(lambda v: v.label == label, self.__vertices)[0]


    def add_vertex(self, label: T) -> bool:
        try:
            v = self.__find_vertex(label)
            return False
        except IndexError:
            self.vertices.append(Vertex(label))
            return True


    def remove_vertex(self, label: T) -> bool:
        try:
            v = self.__find_vertex(label)
            idx = self.__vertices.index(v)
            it = self.get_graph_iterator()
            while(it.valid()):
                v = it.getCurrent()
                v.remove_inbound(label)
                v.remove_outbound(label)
            return True
        except IndexError:
            return False


    def add_edge(self, out: T, in: T) -> bool:
        if self.is_edge(out, in):
            return False

        try:
            v_out = self.__find_vertex(out)
            v_in = self.__find_vertex(in)
            self.__edges[(out, in)] = 0
            v_out.add_outbound(in)
            v_in.add_inbound(out)
            return True
        except IndexError:
            return False


    def remove_edge(self, out: T, in: T) -> bool:
        if not self.is_edge(out, in):
            return False

        try:
            v_out = self.__find_vertex(out)
            v_in = self.__find_vertex(in)

            del self.__edges[(out, in)]

            v_out.remove_outbound(in)
            v_in.remove_inbound(out)

            return True


    def size(self) -> int:
        return len(self.__vertices)


    def get_edge_property(self, out: T, in: T) -> int:
        if not self.is_edge(out, in):
            raise Exception

        return self.__edges[(out, in)]


    def set_edge_property(self, out: T, in: T):
        if not self.is_edge(out, in):
            raise Exception

        self.__edges[(out, in)] = val
