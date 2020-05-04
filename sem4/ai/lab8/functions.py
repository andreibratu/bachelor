import numpy as np


def relu(X):
    return np.maximum(0, X)


def d_relu(X):
    dz = np.array(X, copy=True)
    dz[X <= 0] = 0
    dz[X > 0] = 1
    return dz


def mse(y_hat: np.ndarray, y: np.ndarray) -> float:
    """Calculate MSE for predictions."""
    return (np.square(y - y_hat)).mean()
