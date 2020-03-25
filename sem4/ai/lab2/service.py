import codecs
import json
from itertools import product
from operator import itemgetter
from copy import deepcopy
from os import path
from typing import Callable, Dict, Tuple, Optional

import numpy as np

from problem import Problem
from state import build_empty_state, State


class ProblemService:

    def __init__(self):
        self._n = None
        self._zero_state = None
        self._instance = Problem()
        self._cache = self.__load_cache() if path.exists('cache.json') else {}

    @staticmethod
    def __load_cache() -> Dict[int, Optional[State]]:
        """
        Load cached solutions.
        :return: The cache.
        """
        text = codecs.open('cache.json', 'r', encoding='utf-8').read()
        py_dict = json.loads(text)
        loaded = {}
        for k, v in py_dict.items():
            if v is None:
                loaded[int(k)] = v
            else:
                loaded[int(k)] = np.array(v)
        return loaded

    def _dfs(self) -> Optional[State]:
        """
        Problem approach using uninformed depth-first search. Results are persisted in order
        to be used in the informed search approach.
        :return: A valid and complete state, or {None} if it does not exist.
        """
        assert self._zero_state is not None, "Please input board size (n)!"

        def dfs(state: State) -> Optional[State]:
            """
            Actual search function.
            :param state: Current state.
            :return: A valid and complete state, or {None} if it does not exist.
            """
            if Problem.is_final(state):
                return state

            for next_state in Problem.expand(state):
                result = dfs(next_state)
                if result is not None:
                    return result

            return None

        answer = dfs(deepcopy(self._zero_state))
        self._cache[self._n] = answer
        return answer

    def _gbfs(self) -> Optional[State]:
        """
        Problem approach using a greedy best-first search. The target state required for
        the heuristic will be loaded from object's cache, or calculated beforehand.
        :return: A valid and complete state, or {None} if it does not exist.
        """
        n = self._n
        if not self.is_cached(n):
            print("No cached solution - DFS will be used to find the target..")
        else:
            print('Cached solution will be used as target..')
        target = self._cache[n] if self.is_cached(n) else self._dfs()

        def equal(a: State, b: State) -> bool:
            """
            Check if two States are equal element-wise.
            :param a: First State.
            :param b: Second state.
            :return: True if equal, else False.
            """
            for i, j in product(*([[c for c in range(n)]] * 2)):
                if a[i, j] != b[i, j]:
                    return False
            return True

        def gbfs(state: State) -> Optional[State]:
            """
            Actual search function.
            :param state: Current state.
            :return: A valid and complete state, or {None} if it does not exist.
            """
            if equal(state, target):
                return state

            next_states = list(state for state in Problem.expand(state))
            next_states = [(Problem.heuristic(state, target), state) for state in next_states]
            next_states.sort(key=itemgetter(0))

            for (cost, state) in next_states:
                if cost == float('inf'):
                    continue
                result = gbfs(state)
                if result is not None:
                    return result

            return None

        answer = gbfs(deepcopy(self._zero_state)) if target is not None else None
        self._cache[self._n] = answer
        return answer

    def set_value_n(self, n: int):
        """
        Set the current size of the board.
        :param n: The size parameter
        """
        self._n = n
        self._zero_state = build_empty_state(n)

    def is_cached(self, n: int) -> bool:
        """
        Check if a solution for size n has been cached before.
        :param n: Queried size.
        :return: True if cached, else False.
        """
        return n in self._cache

    def get_approaches(self) -> Dict[Tuple[int, str], Callable]:
        """
        Return all problem approaches available.
        :return: A dictionary consisting of identification key, and reference to the search method.
        """
        return {
            (1, 'Depth First Search'): self._dfs,
            (2, 'Greedy Breadth First Search'): self._gbfs
        }

    def __del__(self):
        """
        Persist the cache before deleting the object.
        """
        to_save = {}
        for k, v in self._cache.items():
            if v is None:
                to_save[k] = v
            else:
                to_save[k] = v.tolist()
        json.dump(
            to_save,
            codecs.open('cache.json', 'w', encoding='utf-8'),
            separators=(',', ':'),
            sort_keys=True,
            indent=4)
