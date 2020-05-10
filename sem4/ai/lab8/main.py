from typing import List, Tuple

import numpy as np

from functions import d_relu, mse, relu, linear, d_linear
from network import NeuralNetwork


def remodel_dataset(rows: List[List]) -> Tuple[np.ndarray, np.ndarray]:
    """Transform read input into numpy arrays."""
    X = [[1] + line[:-1] for line in rows]
    y = [line[-1] for line in rows]
    return np.array(X), np.array(y)


def process_dataset(filename: str) -> List[List]:
    """Read, parse and prepare dataset."""
    with open(filename, 'r') as f:
        lines = f.readlines()[4:]
        lines = [line.split() for line in lines]
        # Split will leave some blank arrays in
        lines = [line for line in lines if len(line) != 0]
        return [[float(x) for x in line] for line in lines]


if __name__ == '__main__':
    dataset = process_dataset('bdate2.txt')
    X, y = remodel_dataset(dataset)
    print(X.shape, y.shape)
    y = y.reshape(-1, 1)
    model = NeuralNetwork(X.shape[1], 20, 1, relu, d_relu)
    for _ in range(10):
        model.train(X, y)
    y_hat = model.predict(X)
    print(f'MSE: {mse(y, y_hat)}')

