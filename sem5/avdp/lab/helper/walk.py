from math import sqrt
from typing import List, Dict, Tuple

from domain.types import Matrix

# The positions in walk are invariant to matrix values.
# Use dicts to memorise position of any coord
walk, reverse_walk = {}, {}


def _build_zig_zag_walk(size: int) -> Tuple[Dict[Tuple[int, int], int], Dict[int, Tuple[int, int]]]:
    """Precompute index -> position mapping and its reverse for matrices of given size."""
    global walk, reverse_walk
    rows, columns = size, size
    solution = [[] for _ in range(rows + columns - 1)]
    walk, reverse_walk = {}, {}
    for i in range(rows):
        for j in range(columns):
            idx_sum = i + j
            if idx_sum % 2 == 0:
                # Add at start of list
                solution[idx_sum].insert(0, (i, j))
            else:
                # Add at end of the list
                solution[idx_sum].append((i, j))
    flat_sol = [elem for sublist in solution for elem in sublist]
    for pos, indices_pair in enumerate(flat_sol):
        walk[indices_pair] = pos
        reverse_walk[pos] = indices_pair


def zig_zag_walk(matrix: Matrix) -> List[float]:
    global walk
    h, w = len(matrix), len(matrix[0])
    assert h == w
    result = [0 for _ in range(h * w)]
    if len(walk) != h * w:
        # Recompute to match
        _build_zig_zag_walk(h)
    for i in range(h):
        for j in range(w):
            result[walk[(i, j)]] = matrix[i][j]
    return result


def reverse_zig_zag_walk(walk_arr: List[float]) -> Matrix:
    global reverse_walk
    matrix_size = int(sqrt(len(walk_arr)))
    assert matrix_size ** 2 == len(walk_arr)
    if len(reverse_walk) != matrix_size ** 2:
        # Recompute to match
        _build_zig_zag_walk(matrix_size)
    result = [[0 for _ in range(matrix_size)] for _ in range(matrix_size)]
    for pos, val in enumerate(walk_arr):
        i, j = reverse_walk[pos]
        result[i][j] = val
    return result


assert zig_zag_walk([[1, 2, 3], [4, 5, 6], [7, 8, 9]]) == [1, 2, 4, 7, 5, 3, 6, 8, 9]
assert reverse_zig_zag_walk([1, 2, 4, 7, 5, 3, 6, 8, 9]) == [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
_build_zig_zag_walk(8)
