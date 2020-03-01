from copy import deepcopy
from random import shuffle
from typing import Optional, List, Tuple

import numpy as np

_ROWS = 5
_COLS = 6
_ATTEMPTS = 0
Figure = List[Tuple[int, int]]


def _in_board(row: int, col: int) -> bool:
    return 0 <= row < _ROWS and 0 <= col < _COLS


def _apply_move(board: np.ndarray, row: int, col: int, move: Figure) -> Optional[np.ndarray]:
    c_board = deepcopy(board)
    val = np.amax(board.flatten()) + 1
    for dy, dx in move:
        yy, xx = row + dy, col + dx
        if _in_board(yy, xx) and c_board[yy, xx] == 0:
            c_board[yy, xx] = val
            continue
        return None
    return c_board


def solve(attempts: int = 1000) -> Optional[np.ndarray]:
    global _ATTEMPTS
    _ATTEMPTS = attempts

    board = np.ndarray([[0] * _COLS] * _ROWS)
    moves = [
        [(0, 0), (0, 1), (0, 2), (0, 3)],
        [(0, 0), (1, 0), (1, 1), (1, 2), (0, 2)],
        [(0, 0), (1, 0), (1, 1), (1, 2)],
        [(0, 0), (0, 1), (0, 2), (1, 2)],
        [(0, 0), (0, 1), (-1, 1), (0, 2)]
    ]
    empty = [(i, j) for i in range(_ROWS) for j in range(_COLS)]

    def step(in_board: np.ndarray, in_empty: List[Tuple[int, int]], in_moves: List[Figure]) -> Optional[np.ndarray]:

        global _ATTEMPTS
        if _ATTEMPTS < 0:
            return None

        if len(in_empty) == 0:
            return in_board

        copy_empty = deepcopy(in_empty)
        shuffle(copy_empty)
        for (row, col) in copy_empty:
            copy_board = deepcopy(in_board)
            for move in in_moves:
                board_after_move = _apply_move(copy_board, row, col, move)
                if board_after_move is None:
                    continue
                if _ATTEMPTS == 0:
                    break
                sol = step(board_after_move, [x for x in in_empty if (row, col) != x], in_moves)
                if sol is not None:
                    _ATTEMPTS -= 1
                    return sol

        _ATTEMPTS -= 1
        return None

    return step(board, empty, moves)
