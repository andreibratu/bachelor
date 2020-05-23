import math
from math import sin, cos
from random import random, randint
from typing import List, Tuple


class Chromosome:

    def __init__(self, maximum_depth: int, terminals: List[str], functions: List[str], constants: List[int]):
        self._constants = constants
        self._maximum_depth = maximum_depth
        self._terminals = terminals
        self._functions = functions
        self._representation = [0 for _ in range(2 ** (self._maximum_depth + 1) - 1)]
        self._fitness = 0
        self._accuracy = 0
        self._size = 0
        self.grow_expression()
        # Keep only the actual representation - list comprehension preserves order
        self._representation = [x for x in self._representation if x != 0]

    def get_terminal_at_index(self, pos: int) -> str:
        """Translate from signed integer node convention to terminal."""
        return self._terminals[self._representation[pos] - 1]

    def get_func_at_index(self, pos: int) -> str:
        """Translate from signed integer node convention to normal-named operator."""
        return self._functions[-self._representation[pos] - 1]

    def grow_expression(self, pos=0, depth=0):
        """
        Recursively build a tree layer by layer of depth.
        The growing can be stopped early if all generated nodes are terminal.
        """
        if pos == 0 or depth < self._maximum_depth:
            if pos != 0 and random() < 0.4:
                # Assign the current node a positive value, marking it as terminal value
                # First node cannot be terminal
                self._representation[pos] = randint(1, len(self._terminals))
                self._size = pos + 1
                return pos + 1
            else:
                # Assign current node a negative value, marking it as a mathematical node function
                self._representation[pos] = -randint(1, len(self._functions))
                if self._functions[-self._representation[pos] - 1] in ['sin', 'cos']:
                    # Sin and cos are unary functions
                    childEndIndex = self.grow_expression(pos + 1, depth + 1)
                    return childEndIndex
                else:
                    # Binary functions
                    firstChildEndIndex = self.grow_expression(pos + 1, depth + 1)
                    secondChildEndIndex = self.grow_expression(firstChildEndIndex, depth + 1)
                    return secondChildEndIndex
        else:
            # Maximum depth reached, only terminal nodes allowed
            self._representation[pos] = randint(1, len(self._terminals))
            self._size = pos + 1
            return pos + 1

    def evaluate_expression(self, pos: int, data_row: List[float]) -> Tuple[float, int]:
        """
        Recursively evaluate a subtree of the chromosome.
        :param pos: Start node of the subtree
        :param data_row: Data row used to replace terminal nodes with values used in evaluation.
        :return: Tuple containing the subtree evaluation and the last index representation included in the subtree
        """
        pos = min(pos, len(self._representation) - 1)
        if self._representation[pos] > 0:
            # Terminal node
            return data_row[self._representation[pos] - 1], pos
        elif self._representation[pos] < 0:
            # Function
            node_fct = self.get_func_at_index(pos)
            if node_fct == '+':
                auxFirst = self.evaluate_expression(pos + 1, data_row)
                auxSecond = self.evaluate_expression(auxFirst[1] + 1, data_row)
                return auxFirst[0] + auxSecond[0], auxSecond[1]
            elif node_fct == '-':
                auxFirst = self.evaluate_expression(pos + 1, data_row)
                auxSecond = self.evaluate_expression(auxFirst[1] + 1, data_row)
                return auxFirst[0] - auxSecond[0], auxSecond[1]
            elif node_fct == '*':
                auxFirst = self.evaluate_expression(pos + 1, data_row)
                auxSecond = self.evaluate_expression(auxFirst[1] + 1, data_row)
                return auxFirst[0] * auxSecond[0], auxSecond[1]
            elif node_fct == 'sin':
                aux = self.evaluate_expression(pos + 1, data_row)
                return sin(aux[0]), aux[1]
            elif node_fct == 'cos':
                aux = self.evaluate_expression(pos + 1, data_row)
                return cos(aux[0]), aux[1]

    def compute_fitness(self, dataset: List[List[float]], labels: List[int]):
        """
        Calculate chromosome fitness and accuracy using the entire dataset.
        :param dataset:  The dataset
        :param labels:      Labels for each row
        :return:            The fitness of the individual and obtained accuracy
        """
        def calculate_output_class(data_row: List[float]) -> int:
            output = self.evaluate_expression(0, data_row)[0]
            # If output is smaller than 0 ceil it in the first interval
            if output < 2:
                return 1
            if output < 4:
                return 2
            if output < 6:
                return 3
            if output < 8:
                return 4
            # If output is larger than 10 floor it in the last interval
            return 5

        total_error = 0.0
        correct, total = 0, 0
        n_examples = len(dataset)
        for idx in range(n_examples):
            error = abs(labels[idx] - calculate_output_class(data_row=dataset[idx]))
            total_error += error
            if error == 0:
                correct += 1
            total += 1
        accuracy = correct / total
        self._fitness = total_error
        self._accuracy = accuracy

    def traverse(self, pos):
        """Return the start index of the next tree branch from the same level."""
        if self._representation[pos] > 0:  # terminal
            return min(pos + 1, len(self._representation) - 1)
        else:
            return self.traverse(self.traverse(pos + 1))

    def __getitem__(self, key):
        """
        Helper magic function that allows operations such as chromosome[idx] or chromosome[idx1:idx2]
        :param key: Integer or slice object.
        :return: Corresponding value/ slice of the chromosome representation.
        """
        # Underlying list can accept slice object directly, code below is redundant
        # if isinstance(key, slice):
        #     indices = range(*key.indices(len(self._representation)))
        #     return [self._representation[i] for i in indices]
        return self._representation[key]

    def __setitem__(self, key, value):
        # Analogue operation to __getitem__
        self._representation[key] = value

    @property
    def representation(self):
        return self._representation

    @representation.setter
    def representation(self, value):
        self._representation = value

    @property
    def size(self):
        return self._size

    @size.setter
    def size(self, value):
        self._size = value

    @property
    def fitness(self):
        return self._fitness

    @property
    def accuracy(self):
        return self._accuracy

    def __str__(self):
        str_repr = ''
        for _, pos in enumerate(self._representation):
            if self._representation[pos] < 0:
                str_repr += self.get_func_at_index(pos) + ' '
            else:
                str_repr += self.get_terminal_at_index(pos) + ' '
        return str_repr

