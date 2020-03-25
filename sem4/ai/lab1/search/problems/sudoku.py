from collections import Counter
from copy import deepcopy
from math import sqrt
from random import randint, shuffle
from typing import List, Tuple, Optional

import numpy as np

_EMPTY = -1
_ATTEMPTS = 0


def __unique_or_empty(arr: np.array) -> bool:
    """
    Check if a given array contains only unique values. Exception is {code _EMPTY} value, which
    can appear multiple times.
    :param arr: Linear array to be checked. Matrices should be flattened before.
    :return: True if condition is satisfied.
    """
    for k, v in Counter(arr).most_common():
        if v not in [0, 1] and k != _EMPTY:
            return False
    return True


def __is_valid(board):
    """
    Check if each row, column, and sub-square of a Sudoku board contains either unique values or empty ones.
    :param board: Sudoku board to be checked.
    :return: True if the Sudoku board is in a valid state, else False.
    """

    size = board.shape[0]
    root = int(sqrt(size))

    # Check each row and column
    for i in range(size):
        row = board[:, i]
        col = board[i, :]
        if not __unique_or_empty(row) or not __unique_or_empty(col):
            return False

        # Check all sub-squares
        for row in range(0, size, root):
            for col in range(0, size, root):
                square = board[row:row+root, col:col+root]
                if not __unique_or_empty(square.flatten()):
                    return False

        return True


def solve(size: int, board: np.array = None, attempts: int = 10000) -> np.array:
    """
    Use RS algorithm to find a solution to a {size x size} Sudoku board.

    :param size: Size of the Sudoku board
    :param board: Pre-filled Sudoku board. If {None}, the algorithm will start from an empty board.
    :param attempts: Attempts before giving up.
    :return: A solution to the Sudoku board.
    """

    def step(in_board: np.array, in_empty: List[Tuple[int, int]]) -> Optional[np.array]:
        """
        Randomly fill an empty Sudoku box. Use recursive backtracking to fill up the board.
        :param in_board: Current board state.
        :param in_empty: Empty positions in current board state.
        :return: (True, solution) if a solution was found, else (False, None).
        """

        global _ATTEMPTS
        if _ATTEMPTS < 0:
            return None

        if len(in_empty) == 0:
            return in_board

        copy_empty = deepcopy(in_empty)
        shuffle(copy_empty)
        for (row, col) in copy_empty:
            copy_board = deepcopy(in_board)
            rand_val = randint(1, size)
            copy_board[row, col] = rand_val
            if __is_valid(copy_board):
                _ATTEMPTS -= 1
                result = step(copy_board, [x for x in copy_empty if (row, col) != x])
                if result is not None:
                    return result
                else:
                    _ATTEMPTS -= 1

        _ATTEMPTS -= 1
        return None

    global _ATTEMPTS
    _ATTEMPTS = attempts

    root = int(sqrt(size))
    assert size % root == 0, "Size of board must be a square number!"
    if board is not None:
        assert board.shape[0] == board.shape[1] and board.shape[0] == size, "Size of board must equal {size} param!"

    if board is None:
        board = np.array([[_EMPTY] * size] * size)
    empty_positions = [(i, j) for i in range(size) for j in range(size)]

    return step(board, empty_positions)
