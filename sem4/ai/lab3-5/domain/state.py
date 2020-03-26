from copy import deepcopy
from itertools import product
from random import seed, choice
from typing import List, Generator, Tuple
import numpy as np

State = List[List[int]]
EMPTY = -1


def build_random_state(n: int) -> State:
    seed()
    state = []

    for _ in range(2*n):
        perm = np.random.permutation(n) + 1
        state.append(perm.tolist())

    return state


def get_row(state: State, idx: int) -> Tuple[List[int], List[int]]:
    n = len(state) // 2
    return state[idx], state[idx+n]


def get_column(state: State, idx: int) -> Tuple[List[int], List[int]]:
    n = len(state) // 2
    col_s = [state[i][idx] for i in range(n)]
    col_t = [state[i+n][idx] for i in range(n)]
    return col_s, col_t


def get_values(state: State) -> Generator[Tuple[int, int], None, None]:
    n = len(state) // 2
    for i, j in product(range(n), range(n)):
        yield state[i][j], state[i+n][j]


def get_pos(state: State, i: int, j: int) -> Tuple[int, int]:
    n = len(state) // 2
    return state[i][j], state[i+n][j]


def set_pos(state: State, i: int, j: int, val: Tuple[int, int]) -> State:
    n, cpy = len(state) // 2, deepcopy(state)
    cpy[i][j], cpy[i+n][j] = val
    return cpy