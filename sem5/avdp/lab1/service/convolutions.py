from copy import deepcopy
from domain.types import Matrix


def identity(init: Matrix) -> Matrix:
    return deepcopy(init)


def average_2d(init: Matrix, convSize: int) -> Matrix:
    h, w = len(init), len(init[0])
    result = []

    for up_left_h in range(0, h, convSize):
        new_row = []
        for up_left_w in range(0, w, convSize):
            down_right_h = up_left_h + convSize - 1
            down_right_w = up_left_w + convSize - 1
            s = 0.0
            for i in range(up_left_h, down_right_h + 1):
                for j in range(up_left_w, down_right_w + 1):
                    # If outside assume 0 padding
                    s += 0 if (i >= h or j >= w) else init[i][j]
            new_row.append(s / (convSize ** 2))
        result.append(new_row)
    return result


def up_sample(init: Matrix, factor: int) -> Matrix:
    h, w = len(init), len(init[0])
    result = []

    for i in range(h):
        newRows = [[] for _ in range(factor)]
        for j in range(w):
            for row in newRows:
                for k in range(factor):
                    row.append(init[i][j])

    return result
