from copy import deepcopy
from random import choice, random
from typing import List, Tuple

from aco.graph import Graph

Permutation = Tuple[int]
Path = List[Permutation]


class Ant:

    def __init__(self, n: int, alpha: float, beta: float, trace_param: float, q: float, graph: Graph):
        self.n = n
        self.path = [choice(graph.get_nodes())]
        self.alpha = alpha
        self.beta = beta
        self.graph = graph
        self.q = q
        self.trace_param = trace_param

    @staticmethod
    def collisions(path: List[Permutation]) -> int:
        """
        Return how many duplicates are in a path, summed column-wise.
        :param path: Path of the ant.
        :return: Number of duplicates.
        """
        duplicates, n = 0, len(path[0])
        for i in range(n):
            column = [path[j][i] for j in range(len(path))]
            duplicates += len(column) - len(set(column))
        return duplicates

    def next_moves(self, current_state: Path) -> List[Path]:
        """
        Generate all valid next paths for a currently incomplete path.
        :param current_state: The path to be completed.
        :return: All valid next states for the path.
        """
        if len(current_state) == self.n:
            return []

        last_node_path = current_state[-1]
        possible_paths = []
        for neighbour in self.graph.get_neighbours(last_node_path):
            copy_path = deepcopy(current_state)
            copy_path.append(neighbour)
            possible_paths.append(copy_path)
        good_possibilities = [path for path in possible_paths if self.collisions(path) == 0]
        return good_possibilities

    def heuristic(self, trace: float, next_state: Path) -> float:
        """"
        Calculate the fitness of a possible next state proportionally with number
        of pheromones and to how many valid states it leads to.
        :param next_state: The next possible state for a path.
        :param trace: Amount of pheromone on the edge between current state and next state.
        :return:
        """
        ln = len(self.next_moves(next_state))
        return trace**self.alpha * ln**self.beta

    def done(self) -> bool:
        """Check if the path build by ant is complete."""
        return len(self.path) == self.n

    def iterate(self):
        """Iterate ant by one step."""
        assert not self.done()
        next_states = self.next_moves(self.path)

        sorter = lambda next_path: self.heuristic(
            self.graph[self.path[-1], next_path[-1]],
            next_path
        )
        next_states.sort(key=sorter, reverse=True)

        chosen_state = next_states[0] if random() < self.q else choice(next_states)
        last_curr_path = self.path[-1]
        last_next_path = chosen_state[-1]
        self.graph[last_curr_path, last_next_path] += self.trace_param
        self.path = chosen_state
