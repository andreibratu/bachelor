from typing import List


base2_base4_dict = {'00': '0', '01': '1', '10': '2', '11': '3'}
base_4_base2_dict = {v: k for (k, v) in base2_base4_dict.items()}
base2_base8_dict = {
    '000': '0', '001': '1', '010': '2', '011': '3',
    '100': '4', '101': '5', '110': '6', '111': '7'
}
base8_base2_dict = {v: k for (k, v) in base2_base8_dict.items()}
base2_base_16_dict = {
    '0000': '0', '0001': '1', '0010': '2', '0011': '3',
    '0100': '4', '0101': '5', '0110': '6', '0111': '7',
    '1000': '8', '1001': '9', '1010': 'A', '1011': 'B',
    '1100': 'C', '1101': 'D', '1110': 'E', '1111': 'F'
}
base16_base2_dict = {v: k for (k, v) in base2_base_16_dict.items()}
char_to_digit = {
    '0': 0, '1': 1, '2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7,
    '8': 8, '9': 9, 'A': 10, 'B': 11, 'C': 12, 'D': 13, 'E': 14,
    'F': 15
}
digit_to_char = {v: k for k, v in char_to_digit.items()}


def from_base10_to_any(number: str, q: int) -> List[int]:
    """Convert base10 number to a base q by succesive divisions.

    Args:
        number (str): Number in decimal.
        q (int): Base to convert to.
    Returns:
        The number representation in base q.
    """

    number = int(number)
    repr = []
    while number != 0:
        repr += [number % q]
        number //= q

    repr.reverse()
    return repr


def from_any_base_to_base10(number_repr: List[int], q: int) -> List[int]:
    """Convert number from any base to base10.

    Args:
        number (List): Number representation in base q.
        q (int): The base of the representation.
    Returns:
        Number representation in base10.
    """

    base_10 = 0
    power = 1
    for i in range(0, len(number_repr)):
        base_10 += number_repr[i] * power
        power *= q

    repr = []
    while base_10:
        repr += [base_10 % 10]
        base_10 //= 10

    repr.reverse()
    return repr


def convert_base2_base4(digits: str) -> str:
    """Rapid convert base2 to base4"""


    result = ''

    if len(digits) % 2 == 0:
        for i in range(0, len(digits) - 1, 2):
            key = digits[i: i + 2]
            result += str(base2_base4_dict[key])

    else:
        digits = '0' + digits
        for i in range(0, len(digits) - 1, 2):
            key = digits[i: i + 2]
            result += str(base2_base4_dict[key])

    return result


def convert_base4_base2(digits: str) -> str:
    """Rapid convert base4 to base2."""

    return ''.join([base_4_base2_dict[c] for c in digits])


def convert_base2_base8(digits: str) -> str:
    """Rapid convert base2 to base8."""

    result = ''

    if len(digits) % 3 == 0:
        for i in range(0, len(digits) - 2, 3):
            key = digits[i: i + 3]
            result += base2_base8_dict[key]

    else:
        zeroes = 3 - len(digits) % 3
        digits = '0' * zeroes + digits
        for i in range(0, len(digits) - 2, 3):
            key = digits[i: i + 3]
            result += base2_base8_dict[key]

    return result


def convert_base8_base2(digits: str) -> str:
    """Rapid convert base8 to base2."""

    return ''.join([base8_base2_dict[c] for c in digits])


def convert_base2_base16(digits):
    """Rapid convert base2 to base16."""

    result = ''

    if len(digits) % 4 == 0:
        for i in range(0, len(digits) - 3, 4):
            key = digits[i: i + 4]
            result += base2_base_16_dict[key]

    else:
        zeroes = 4 - len(digits) % 4
        digits = '0' * zeroes + digits
        for i in range(0, len(digits) - 3, 4):
            key = digits[i: i + 4]
            result += base2_base_16_dict[key]

    return result


def convert_base16_base2(digits: str) -> str:
    """Rapid convert from base16 to base2."""

    return ''.join([base16_base2_dict[c] for c in digits])
