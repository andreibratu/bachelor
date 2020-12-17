from math import sqrt, cos, pi, floor, ceil

from domain.types import Matrix

alpha = lambda val: (1 / sqrt(2)) if val == 0 else 1


def forward_dct(g: Matrix) -> Matrix:
    """Apply forward discrete cosine transform to matrix of floats."""
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

    return G


def inverse_dct(F: Matrix) -> Matrix:
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

    #  Add 128 back
    for i in range(8):
        for j in range(8):
            f[i][j] += 128

    return f


def component_wise_division(a: Matrix, b: Matrix) -> Matrix:
    """Apply binary function over elements of two matrices."""
    result = [[0 for _ in range(8)] for _ in range(8)]
    for i in range(8):
        for j in range(8):
            result[i][j] = a[i][j] / b[i][j]
            if result[i][j] > 0:
                result[i][j] = floor(result[i][j])
            else:
                result[i][j] = ceil(result[i][j])
    return result

def component_wise_multiplication(a: Matrix, b: Matrix) -> Matrix:
    """Apply binary function over elements of two matrices."""
    result = [[0 for _ in range(8)] for _ in range(8)]
    for i in range(8):
        for j in range(8):
            result[i][j] = a[i][j] * b[i][j]
    return result
