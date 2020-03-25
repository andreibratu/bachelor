import numpy as np

State = np.array


def build_empty_state(n: int) -> State:
    return np.array([[-1] * n] * n)
