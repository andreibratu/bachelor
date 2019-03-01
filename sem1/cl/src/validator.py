from number import Number
from exceptions import InvalidNumberException


class NumberValidator(object):
    """Class delegated with validating Number."""

    @staticmethod
    def validate(number: Number):
        """Validate user input when entering a Number."""

        allowed = "0123456789ABCDEF"
        char_to_digit = {
            '0': 0, '1': 1, '2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7,
            '8': 8, '9': 9, 'A': 10, 'B': 11, 'C': 12, 'D': 13, 'E': 14,
            'F': 15
        }
        errs = []

        if number.val == "":
            errs.append("Number value cannot be empty!")

        if number.base == "":
            errs.append("Base value cannot be empty!")

        if [char for char in number.val if char not in allowed] != []:
            errs.append("Invalid digits in the input value!")

        if number.val != "" and char_to_digit[max(number.val)] >= number.base:
            errs.append("Value contains digits larger or equal to the base!")

        if number.base <= 1 or number.base > 16:
            errs.append("Base of the number must be between 2 and 16!")


        if len(errs) > 0:
            raise InvalidNumberException(errs)
