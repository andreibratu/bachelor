from typing import List


class Production:
    """Class to describe a production rule for a grammar."""

    def __init__(self, left_term: str, right_term: List[str]):
        self.left_term = left_term
        self.right_term = right_term

    def __str__(self):
        right_str = "[" + ", ".join(self.right_term) + "]"
        return f"{self.left_term} -> {right_str}"

    __repr__ = __str__

    def __eq__(self, other):
        return (
            self.right_term == other.right_term
            and self.left_term == other.left_term
        )
