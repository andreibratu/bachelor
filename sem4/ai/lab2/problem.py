from collections import Counter
from copy import deepcopy
from itertools import product
from typing import Generator

from state import State


class Problem:
    values = [0, 1]

    @staticmethod
    def is_valid(state: State) -> bool:
        """
        Check if a partial state satisfies the Problem conditions:
            1. A single '1' value on each row.
            2. A single '1' value on each column.
            3. For any two positions (i1, j1) and (i2, j2) s.t.
               abs(i1-i2)-abs(j1-j2) = 0, the two positions do not
               contain a '1' at the same time.
        :param state: State to be evaluated.
        :return: True if conditions hold, else False.
        """
        n = len(state)
        for i in range(n):
            row_i = Counter(state[i, :])
            col_i = Counter(state[:, i])
            if row_i[1] > 1 or col_i[1] > 1:
                return False
            if row_i[-1] == 0 and row_i[1] != 1:
                return False
            if col_i[-1] == 0 and row_i[1] != 1:
                return False
        index_range = [i for i in range(n)]
        for i1, j1, i2, j2 in product(*([index_range] * 4)):
            if i1 == i2 and j1 == j2:
                continue
            if abs(i1 - i2) - abs(j1 - j2) == 0:
                if state[i1, j1] == 1 and state[i2, j2] == 1:
                    return False
        return True

    @staticmethod
    def is_final(state: State) -> bool:
        """
        Check if state is valid and complete.
        :param state: State to be checked.
        :return: True if valid and complete, else False.
        """
        return Problem.is_valid(state) and Counter(state.flatten())[-1] == 0

    @staticmethod
    def expand(state: State) -> Generator[State, None, None]:
        """
        Generate all possible expansions from given state.
        Expansions are identified by finding the first empty
        column on every row, and filling it with a value from
        {Problem.values}. Invalid expansion states are discarded.
        :param state: Current state.
        :return: List of valid expansion states, or empty list if board is filled.
        """
        n = len(state)
        for i in range(n):
            for j in range(n):
                if state[i, j] in Problem.values:
                    continue
                else:
                    for v in Problem.values:
                        new_state = deepcopy(state)
                        new_state[i, j] = v
                        if Problem.is_valid(new_state):
                            yield new_state
                    break

    @staticmethod
    def heuristic(current_state: State, target_state: State) -> float:
        """
        Calculate the distance between two given states. Used in greedy search approach.
        It is assumed that the two states are of equal rank, and that {target_state} is
        a valid and complete state of the problem.
        :param current_state: Partial state.
        :param target_state: The goal state.
        :return:
            Number of empty positions left to be completed, or INF if {target_state} is
            unreachable from {current_state}
        """
        assert len(current_state) == len(target_state), 'Different row number!'
        assert len(current_state[0, :]) == len(target_state[0, :]), 'Different column number!'
        assert Problem.is_final(target_state), 'Target state must be final!'

        cost, n = 0, len(current_state)

        # Check if state and target_stare place values of '1' on different positions of the same row/ column
        # This automatically invalidates {current_state}
        # The check is done by 'merging' {current_state} and {target_state} into {copy_state}
        copy_state = deepcopy(current_state)
        # Merging
        for i, j in product(*([[_ for _ in range(n)]] * 2)):
            if copy_state[i, j] == -1 and target_state[i, j] != -1:
                copy_state[i, j] = target_state[i, j]
        # Checking
        for i in range(n):
            if Counter(copy_state[i, :])[1] != 1:
                return float('inf')
            if Counter(copy_state[:, i])[1] != 1:
                return float('inf')

        # Cost is given by number of empty spaces in {state} that have to be filled.
        for i, j in product(*([[_ for _ in range(n)]] * 2)):
            if current_state[i, j] == -1:
                cost += 1

        return cost
