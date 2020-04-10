from typing import List, Tuple

import numpy as np

from linear_regression import LinearRegression


def remodel_dataset(rows: List[List]) -> Tuple[np.ndarray, np.ndarray]:
    """Transform read input into numpy arrays."""
    X = [line[:-1] for line in rows]
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


def mse(y_hat: np.ndarray, y: np.ndarray) -> float:
    """Calculate MSE for predictions."""
    return (np.square(y - y_hat)).mean()


if __name__ == '__main__':
    dataset = process_dataset('bdate2.txt')
    X, y = remodel_dataset(dataset)
    model = LinearRegression()
    model.fit(X, y)
    y_pred = [model.predict(row) for row in X]
    print(f'MSE: {mse(y_pred, y)}')
