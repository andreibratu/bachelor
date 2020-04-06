from typing import List
from collections import Counter

Dataset = List[List]


def class_counts(rows: Dataset) -> Counter:
    """Counts the number of each type of class in a dataset."""
    return Counter([row[-1] for row in rows])


class Leaf:

    def __init__(self, rows):
        self.predictions = class_counts(rows)