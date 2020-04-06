from math import floor
from random import shuffle
from typing import Tuple
import numpy as np

from cart import Dataset, build_tree
from decision_tree import classify


def read_dataset(file_path: str) -> Dataset:
    ds = []
    with open(file_path, 'r') as f:
        for line in f.readlines():
            row = line.split(',')
            label = row.pop(0)
            row = [int(val) for val in row]
            row.append(label)

            ds.append(row)
    return ds


def split_train_test(ds: Dataset, p: float = 0.8) -> Tuple[Dataset, Dataset]:
    """
    Split dataset into training and test by given proportion.
    If p=1, train and test both refer to the initial dataset.
    """
    if p == 1:
        return dataset, dataset
    ds_len = len(ds)
    train_split = floor(p * ds_len)
    shuffle(ds)
    return ds[:train_split], ds[train_split:]


if __name__ == '__main__':
    dataset = read_dataset('dataset.data')
    """
    Using the entire dataset to train will yield
    perfect accuracy. Splitting the dataset will 
    the usual p=0.8 value gives us an accuracy in 
    the range of 0.6-0.85
    """
    runs, p, accuracy = 1000, 1, []

    for _ in range(runs):
        train, test = split_train_test(dataset, p)
        tree = build_tree(train)

        # Check how many labels match
        correct, total = 0, 0
        for row in test:
            prediction = classify(row, tree)
            actual = row[-1]
            correct += 1 if prediction == actual else 0
            total += 1

        accuracy.append(correct/total)

    print(f'Mean accuracy over {runs} runs, p={p}: {np.mean(accuracy)}')
    print(f'Max accuracy: {np.max(accuracy)}')
    print(f'Min accuracy: {np.min(accuracy)}')
