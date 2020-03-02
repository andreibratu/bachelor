from copy import deepcopy
from random import shuffle
from typing import Optional, List, Tuple

import numpy as np
from scipy.ndimage import label

_ROWS = 5
_COLS = 6
_ATTEMPTS = 0
Figure = List[Tuple[int, int]]


def _in_board(row: int, col: int) -> bool:
    """
    Check if a given position is in matrix.
    :param row: Row of the position.
    :param col: Column of the position.
    :return: True if the position is inside the matrix.
    """
    return 0 <= row < _ROWS and 0 <= col < _COLS


def _apply_move(board: np.array, row: int, col: int, move: Figure) -> Optional[np.array]:
    """
    Calculate the new board moving a new figure on it. Figures are represented as lists
    of tuples, which represent the offset relative to the leftmost space occupied by the figure.
    :param board: The board before applying the Figure.
    :param row: Row of initial position.
    :param col: Column of initial position.
    :param move: The Figure that must be moved on the board
    :return: The board after the move, or {None} if the move is illegal.
    """
    c_board = deepcopy(board)
    val = np.amax(board.flatten()) + 1
    for dy, dx in move:
        yy, xx = row + dy, col + dx
        if _in_board(yy, xx) and c_board[yy, xx] == 0:
            c_board[yy, xx] = val
            continue
        return None
    return c_board


def __valid(board: np.array) -> bool:
    """
    Invalidate board states with un-fillable blank spaces. Find all connected components of
    unfilled spaces and invalidate the board if any of the components is smaller than 4.
    :param board: The board state.
    :return: True if the board is valid, else False.
    """
    # Inverse the array - mark empty spaces with ones and everything else with zero
    inv_arr = np.vectorize(lambda v: 0 if v != 0 else 1)(board)
    # Apply connected components algorithm on the board
    structure = np.array([[0, 1, 0], [1, 1, 1], [0, 1, 0]], dtype=np.int)
    labeled, comp_count = label(inv_arr, structure)
    # Check if any whitespace component is smaller than 4 - thus cannot be covered
    for i in range(1, comp_count + 1):
        if len(labeled[labeled == i]) < 4:
            return False
    return True


def solve(attempts: int = 1000) -> Optional[np.array]:
    """
    Find an arrangement for fitting the above board using RS algorithm.
    :param attempts: Number of attempts before giving up.
    :return: The solution or {None} if one could not be found.
    """
    global _ATTEMPTS
    _ATTEMPTS = attempts

    board = np.array([[0] * _COLS] * _ROWS)
    moves = [
        [(0, 0), (0, 1), (0, 2), (0, 3)],
        [(0, 0), (1, 0), (1, 1), (1, 2), (0, 2)],
        [(0, 0), (1, 0), (1, 1), (1, 2)],
        [(0, 0), (0, 1), (0, 2), (1, 2)],
        [(0, 0), (0, 1), (-1, 1), (0, 2)]
    ]
    empty = [(i, j) for i in range(_ROWS) for j in range(_COLS)]

    def step(in_board: np.array, in_empty: List[Tuple[int, int]], in_moves: List[Figure]) -> Optional[np.array]:
        """
        Fit the board with Figure pieces using a recursive backtracking approach.
        :param in_board: Current state of the board.
        :param in_empty: List of empty squares.
        :param in_moves: List of Figure moves available.
        :return:
            Fitted board, where each piece has a unique numeric ID associated, or {None}
            if a solution could not be found.
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
            for move in in_moves:
                board_after_move = _apply_move(copy_board, row, col, move)
                if board_after_move is None or not __valid(board_after_move):
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
