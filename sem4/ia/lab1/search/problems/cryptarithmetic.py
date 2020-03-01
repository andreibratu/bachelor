import operator
import string
from random import sample
from typing import List, Dict

Char = str


def __get_random_mapping(letters: List[Char]) -> Dict[Char, Char]:
    """
    Assign random base16 digits to the list of letters.
    :param letters: Letters involved in the puzzle
    :return: Mapping from letter to digit.
    """
    digits = [str(i) for i in range(10)] + list(x for x in string.ascii_uppercase[:6])
    return {k: v for k, v in zip(letters, sample(digits, len(letters)))}


def __validate_hex_start(num: str) -> bool:
    """
    Check if hex number does not start with 0. The hex prefix `0x` must be skipped.
    :param num: Number in hexadecimal.
    :return: True if first digit is not 0.
    """
    assert len(num) > 2, "Number cannot be empty!"
    return num[2] != '0'


def solve(op_one: str, op_two: str, op: str, result: str, attempts: int = 100) -> Dict:
    """
    Solve a crypt-arithmetic puzzle between numbers in base16 using RS algorithm.
    :param op_one: First number.
    :param op_two: Second number.
    :param op: Arithmetic operation.
    :param result: The aimed result.
    :param attempts: Attempts before giving up.
    :return: A mapping between letters and base16 digits.
    """

    letters = list(set(op_one) | set(op_two) | set(result))
    op_dict = {'+': operator.add, '-': operator.sub, '*': operator.mul, '/': operator.floordiv}

    assert len(letters) <= 16, "More letters than base16 digits!"
    assert op in op_dict, "Unsupported operation!"

    mapping, ok = None, False

    while attempts != 0 and not ok:
        attempts -= 1
        mapping = __get_random_mapping(letters)
        hexes = [op_one, op_two, result]
        hexes = [''.join(mapping[x] for x in y) for y in hexes]
        if not all(__validate_hex_start(x) for x in hexes):
            continue
        numbers = [int(x, 16) for x in hexes]
        op_func = op_dict[op]
        if op_func(numbers[0], numbers[1]) == numbers[2]:
            ok = True
            break

    if not ok and attempts == 0:
        mapping = None

    return mapping
