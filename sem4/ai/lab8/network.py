import numpy as np


class NeuralNetwork:

    def __init__(self, inputSize, hiddenSize, outputSize, activation, derivative):
        self.inputSize = inputSize
        self.hiddenSize = hiddenSize
        self.outputSize = outputSize
        self.activation = activation
        self.derivative = derivative

        self.weights1 = np.random.randn(inputSize, hiddenSize)
        self.weights2 = np.random.randn(hiddenSize, outputSize)

        self.z = None

    def forward(self, X):
        self.z = self.activation(X @ self.weights1)
        output = self.z @ self.weights2
        return output

    def backward(self, X, y, y_hat):
        """
        We do not have an activation function after the last layer
        since this is a regression task rather then a classification one;
        thus the derivative used in calculating output_delta is the
        derivative of the identity function i.e. 1
        """
        output_error = y - y_hat
        output_delta = output_error * np.ones(y_hat.shape)

        # Z error: how much our hidden layer weights contribute to output error
        z_error = output_delta @ self.weights2.T
        print(z_error.shape, self.z.shape)
        z_delta = z_error * self.derivative(self.z)

        # Ameliorate weights
        self.weights1 -= X.T @ z_delta
        self.weights2 -= self.z.T @ output_delta

    def train(self, X, y):
        output = self.forward(X)
        self.backward(X, y, output)

    def predict(self, X):
        return self.forward(X)