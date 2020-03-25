from typing import Optional, Dict

import numpy as np

from problems import sudoku, geometric
from problems import cryptarithmetic

Char = str


def _to_hex(word: str, mapping: Dict[Char, Char]) -> str:
    """
    Return hex representation of a word.
    :param word: Word to be translated
    :param mapping: Mapping to be used in translation.
    :return: Translated hex number.
    """
    return ''.join(mapping[c] for c in word)


class ProblemService:

    @staticmethod
    def solve_sudoku(size: int, attempts: int = 1000) -> Optional[np.array]:
        return sudoku.solve(size, attempts=attempts)

    @staticmethod
    def solve_crypt(op_one: str, op_two: str, op: str, result: str, attempts: int) -> Optional[str]:
        solution = cryptarithmetic.solve(op_one, op_two, op, result, attempts)
        if solution is None:
            return None
        return _to_hex(op_one, solution) + \
               f' {op} ' + _to_hex(op_two, solution) + \
               ' = ' + _to_hex(result, solution)

    @staticmethod
    def solve_geometric(attempts: int) -> Optional[np.array]:
        solution = geometric.solve(attempts)
        return solution
