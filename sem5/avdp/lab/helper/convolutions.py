from copy import deepcopy
from domain.types import Matrix


def identity(init: Matrix) -> Matrix:
    """Return copy of initial matrix."""
    return deepcopy(init)


def average_2d(matrix: Matrix) -> Matrix:
    """Reduce each convSize by convSize area from init Matrix into one square by averaging.
    """
    n = 8
    result = [[0 for _ in range(n // 2)] for _ in range(n // 2)]

    for i in range(0, n, 2):
        for j in range(0, n, 2):
            avg = (matrix[i][j] + matrix[i][j+1] + matrix[i+1][j] + matrix[i+1][j+1]) / 4
            result[i // 2][j // 2] = avg
    return result


def up_sample(init: Matrix) -> Matrix:
    n = 4
    result = [[0 for _ in range(2 * n)] for _ in range(2 * n)]

    for i in range(0, 2 * n, 2):
        for j in range(0, 2 * n, 2):
            result[i][j] = init[i // 2][j // 2]
            result[i][j + 1] = init[i // 2][j // 2]
            result[i + 1][j] = init[i // 2][j // 2]
            result[i + 1][j + 1] = init[i // 2][j // 2]

    return result
