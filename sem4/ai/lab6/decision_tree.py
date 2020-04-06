from typing import List

from leaf import Leaf
from question import Question


class DecisionTree:

    def __init__(self, question: Question, true_branch: 'DecisionTree', false_branch: 'DecisionTree'):
        self.question = question
        self.true_branch = true_branch
        self.false_branch = false_branch


def classify(row: List, node: DecisionTree) -> str:
    """See the 'rules of recursion' above."""

    # Base case: we've reached a leaf
    if isinstance(node, Leaf):
        return node.predictions.most_common(1)[0][0]

    # Decide whether to follow the true-branch or the false-branch.
    # Compare the feature / value stored in the node,
    # to the example we're considering.
    if node.question.match(row):
        return classify(row, node.true_branch)
    else:
        return classify(row, node.false_branch)
