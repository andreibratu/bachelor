import numpy as np


class LinearRegression:

    def __init__(self):
        self.coefficients = []

    @staticmethod
    def _reshape_x(X: np.ndarray):
        # Reshape input into a matrix
        return X.reshape(-1, 1)

    @staticmethod
    def _add_bias(X: np.ndarray):
        # Add bias term at the start of the input
        ones = np.ones(shape=X.shape[0]).reshape(-1, 1)
        return np.concatenate((ones, X), 1)

    def fit(self, X: np.ndarray, y: np.ndarray):
        """Fit dataset using Least Squares approach."""
        if len(X.shape) == 1:
            X = self._reshape_x(X)

        X = self._add_bias(X)
        self.coefficients = np.linalg.inv(X.transpose().dot(X)).dot(X.transpose()).dot(y)

    def predict(self, row: np.ndarray) -> float:
        """Predict the y of a single data point."""
        b0 = self.coefficients[0]  # The bias term, has no correspondent in X
        other_betas = np.array(self.coefficients[1:])
        assert row.shape == other_betas.shape
        prediction = np.sum(np.multiply(row, other_betas)) + b0
        return prediction
