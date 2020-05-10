from typing import Callable

import numpy as np


class NeuralNetwork:

    def __init__(
            self,
            inputSize: int,
            hiddenSize: int,
            outputSize: int,
            activation: Callable,
            derivative: Callable,
            l_rate: float = 0.0001
    ):
        self.inputSize = inputSize
        self.hiddenSize = hiddenSize
        self.outputSize = outputSize
        self.activation = activation
        self.derivative = derivative
        self.l_rate = l_rate

        self.weights1 = np.random.rand(inputSize, hiddenSize)
        self.weights2 = np.random.rand(hiddenSize, outputSize)

        self.generation = 0

        self.z = None

    def forward(self, X):
        self.z = self.activation(np.dot(X, self.weights1))
        output = self.activation(np.dot(self.z, self.weights2))
        return output

    def backward(self, X, y, y_hat):
        d_weights2 = np.dot(self.z.T, (2 * (y - y_hat) * self.derivative(y_hat)))

        d_weights1 = np.dot(X.T, (np.dot(2 * (y - y_hat) * self.derivative(y_hat),
                                                  self.weights2.T) * self.derivative(self.z)))

        self.weights1 += (1 / X.shape[0]) * self.l_rate * d_weights1
        self.weights2 += (1 / X.shape[0]) * self.l_rate * d_weights2
        print(f'LOSS EPOCH {self.generation+1}', sum((y - y_hat) ** 2))
        self.generation += 1

    def train(self, X, y):
        output = self.forward(X)
        self.backward(X, y, output)

    def predict(self, X):
        return self.forward(X)
