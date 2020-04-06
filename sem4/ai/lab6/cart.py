from typing import List, Tuple

from decision_tree import DecisionTree
from leaf import class_counts, Leaf
from question import Question

Dataset = List[List]


def gini(rows: Dataset) -> float:
    """Calculate the Gini Impurity for given group."""
    counts = class_counts(rows)
    impurity = 1
    for label in counts:
        prob_of_lbl = counts[label] / float(len(rows))
        impurity -= prob_of_lbl**2
    return impurity


def info_gain(left: Dataset, right: Dataset, current_uncertainty: float) -> float:
    """
    Calculate the information gain obtained from
    splitting the dataset into `left` and `right`.
    """
    p = float(len(left)) / (len(left) + len(right))
    return current_uncertainty - p * gini(left) - (1 - p) * gini(right)


def find_best_split(rows: Dataset):
    """Find the best question to ask by iterating over every
    feature / value and calculating the information gain."""
    best_gain, best_question = 0, None
    current_uncertainty = gini(rows)
    n_features = len(rows[0]) - 1  # number of feature columns

    for col in range(n_features):
        values = set([row[col] for row in rows])
        for val in values:
            question = Question(col, val)
            true_rows, false_rows = partition(rows, question)
            # Skip this split if it doesn't divide the dataset
            if len(true_rows) == 0 or len(false_rows) == 0:
                continue
            # Calculate the information gain from this split
            gain = info_gain(true_rows, false_rows, current_uncertainty)
            if gain > best_gain:
                best_gain, best_question = gain, question

    return best_gain, best_question


def partition(rows: Dataset, question: Question) -> Tuple[Dataset, Dataset]:
    """Partition a dataset based on a given question."""
    true_rows = [row for row in rows if question.match(row)]
    false_rows = [row for row in rows if not question.match(row)]
    return true_rows, false_rows


def build_tree(rows: Dataset):
    """
    Recursively build a DecisionTree for given dataset.
    The dataset is continuously split until no further
    information gains can be obtained.
    """
    gain, question = find_best_split(rows)

    if gain == 0:
        # No further splits are possible
        return Leaf(rows)

    true_rows, false_rows = partition(rows, question)
    true_branch = build_tree(true_rows)
    false_branch = build_tree(false_rows)

    return DecisionTree(question, true_branch, false_branch)
