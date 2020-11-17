from math import sqrt, cos, pi
from collections import Callable

from domain.types import Matrix

alpha = lambda val: (1 / sqrt(2)) if val == 0 else 1


def forward_dct(g: Matrix) -> Matrix:
    """Apply forward discrete cosine transform to matrix of floats."""
    assert len(g) == 8 and len(g[0]) == 8
    G = [[0 for _ in range(8)] for _ in range(8)]

    # Subtracting 128 from every Y/Cb/Cr value
    for u in range(8):
        for v in range(8):
            g[u][v] -= 128

    for u in range(8):
        for v in range(8):
            double_sum = 0
            for x in range(8):
                for y in range(8):
                    double_sum += g[x][y] * \
                                  cos(((2 * x + 1) * u * pi) / 16) * \
                                  cos(((2 * y + 1) * v * pi) / 16)
            G[u][v] = (0.25 * alpha(u) * alpha(v) * double_sum)
            assert not isinstance(G[u][v], complex)

    return G


def inverse_dct(F: Matrix) -> Matrix:
    assert len(F) == 8 and len(F[0]) == 8
    f = [[0 for _ in range(8)] for _ in range(8)]

    for x in range(8):
        for y in range(8):
            double_sum = 0
            for u in range(8):
                for v in range(8):
                    double_sum += alpha(u) * alpha(v) * F[u][v] * \
                                  cos(((2 * x + 1) * u * pi) / 16) * \
                                  cos(((2 * y + 1) * v * pi) / 16)
            f[x][y] = 0.25 * double_sum
            assert not isinstance(f[x][y], complex)

    #  Add 128 back
    for i in range(8):
        for j in range(8):
            f[i][j] += 128

    return f


def component_wise(a: Matrix, b: Matrix, func: Callable) -> Matrix:
    """Apply binary function over elements of two matrices."""
    assert len(a) == len(b) and len(a[0]) == len(b[0])
    result = [[0 for _ in range(len(a))] for _ in range(len(a[0]))]
    for i in range(8):
        for j in range(8):
            result[i][j] = func(a[i][j], b[i][j])
    return result


component_wise_division = lambda a, b: component_wise(a, b, lambda i, j: i // j)


component_wise_multiplication = lambda a, b: component_wise(a, b, lambda i, j: i * j)
