from collections import defaultdict
from itertools import permutations, product
from typing import Tuple, Dict, List, Generator, TypeVar

T = TypeVar('T')
V = TypeVar('V')


class Graph:

    """Generic undirected and weighted graph."""

    def __init__(self):
        self._graph = defaultdict(dict)

    def __getitem__(self, key: Tuple[T, T]) -> V:
        n1, n2 = key
        return self._graph[n1][n2]

    def __setitem__(self, key: Tuple[T, T], value: V):
        n1, n2 = key
        self._graph[n1][n2] = value

    def add_edge(self, node1: T, node2: T):
        self._graph[node1][node2] = 0
        self._graph[node1][node1] = 0

    def get_nodes(self) -> List[T]:
        return [k for k in self._graph.keys()]

    def get_neighbours(self, node: T) -> Generator[T, None, None]:
        for neighbour in self._graph[node].keys():
            yield neighbour


def generate_aco_graph(n: int) -> Graph:
    """
    Generate graph with permutations as nodes.
    :param n: Size of permutations
    :return: Graph object holding Permutations as nodes
    """
    graph = Graph()
    perms = permutations(range(n))
    for n1, n2 in product(perms, repeat=2):
        graph.add_edge(n1, n2)
    return graph
