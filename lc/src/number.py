from typing import List, Tuple, NewType

from helper import from_base10_to_any, from_any_base_to_base10
from helper import convert_base2_base4, convert_base4_base2
from helper import convert_base2_base8, convert_base8_base2
from helper import convert_base16_base2, convert_base2_base16
from helper import char_to_digit, digit_to_char

Number = NewType('Number', int)


class Number:
    """Class that implements number representation."""


    def __init__(self, val, base):
        """Class constructor.

        val (str): The digits of the number.
        base (int): Arbitrary base, smaller or equal to 16.
        """

        self.val = val.upper()
        self.base = base


    @staticmethod
    def get_representation(val: str) -> List[int]:
        """Return the number as a list of integers for calculations.

        The list is represented reversed, in order to facilitate calculations.
        """

        return [char_to_digit[x] for x in val][::-1]


    @staticmethod
    def get_value(repr: List[int]) -> str:
        """Return the value defined by given representation.

        The number has to be reversed in order to reflect the actual value.
        """

        return ''.join([digit_to_char[d] for d in repr])[::-1]


    def __add__(self, other):
        """Define the behaviour of the '+' operator on Number type."""

        if self.base != other.base:
            raise ValueError()

        base = self.base
        self_repr = Number.get_representation(self.val)
        other_repr = Number.get_representation(other.val)
        carry = 0

        # Bordering the smaller number with zeroes
        while len(self_repr) > len(other_repr):
            other_repr.append(0)

        while len(other_repr) > len(self_repr):
            self_repr.append(0)


        for i in range(0, len(self_repr)):
            self_repr[i] += other_repr[i] + carry
            carry = self_repr[i] // base
            self_repr[i] %= base

        if carry != 0:
            self_repr.append(carry)

        sum = Number.get_value(self_repr)
        return Number(sum, base)


    def __sub__(self, other):
        """Define the behaviour of the '-' operator on Number type.

        Raises:
            ValueError: Number objects have different bases.
        """

        if self.base != other.base:
            raise ValueError()

        base = self.base
        self_repr = Number.get_representation(self.val)
        other_repr = Number.get_representation(other.val)
        carry = 0

        # Other number is smaller, border with 0
        while len(other_repr) < len(self_repr):
            other_repr.append(0)

        for i in range(0, len(self_repr)):
            self_repr[i] = self_repr[i] - (other_repr[i] + carry)
            if self_repr[i] < 0:
                carry = 1
            else:
                carry = 0
            if carry != 0:
                self_repr[i] += base

        # Remove redundant zeroes
        while self_repr[-1] == 0:
            self_repr.pop()

        # Empty list -> other_repr was equal with self_repr
        if self_repr == []:
            self_repr = [0]

        diff = Number.get_value(self_repr)
        return Number(diff, base)


    def __mul__(self, other) -> Number:
        """Define the behaviour of the '*' operator on Number type.

        Raises:
            ValueError: Other Number object does not have a one digit value.
        """

        base = self.base
        self_repr = Number.get_representation(self.val)
        other_repr = Number.get_representation(other.val)

        if len(other_repr) != 1:
            raise ValueError(other_repr)

        digit = other_repr[0]
        carry = 0

        for i in range(0, len(self_repr)):
            self_repr[i] = self_repr[i] * digit + carry
            carry = self_repr[i] // base
            self_repr[i] %= base

        while carry != 0:
            self_repr.append(carry % base)
            carry //= base

        if self_repr == [0] * len(self_repr):
            self_repr = [0]

        prod = Number.get_value(self_repr)
        return Number(prod, base)


    def __truediv__(self, other) -> Tuple[Number, Number]:
        """Define the behaviour of the '/' operator on Number type.

        Raises:
            ValueError: Other Number object has more than one digit, or is 0.
        """

        base = self.base
        self_repr = Number.get_representation(self.val)
        other_repr = Number.get_representation(other.val)

        if len(other_repr) > 1 or other_repr == [0]:
            raise ValueError('Divisor has more than one digit in div base')

        digit = other_repr[0]
        remainder = 0

        for i in range(len(self_repr) - 1, -1, -1):
            remainder = base * remainder + self_repr[i]
            self_repr[i] = remainder // digit
            remainder %= digit

        while self_repr[-1] == 0 and len(self_repr) > 1:
            self_repr.pop()

        div = Number.get_value(self_repr)
        div = Number(div, base)
        remainder = [remainder]
        remainder = Number.get_value(remainder)
        remainder = Number(remainder, base)
        return (div, remainder)


    def _base10_to_any_base(self: Number, base: int) -> Number:
        """Convert self to another base, using base 10 as intermediary."""

        number = self.val
        repr = from_base10_to_any(number, base)
        repr.reverse()
        number = Number.get_value(repr)
        return Number(number, base)


    def _to_base10(self: Number) -> Number:
        """Convert Number object value to base10, using substitution."""

        number = Number.get_representation(self.val)
        repr = from_any_base_to_base10(number, self.base)
        repr.reverse()
        number = Number.get_value(repr)
        number = Number(number, 10)
        return number


    def to_any_base(self: Number, q: int) -> Number:
        """Convert Number object value to any base.

        Args:
            q (int): The base to which to convert
        Returns:
            Number instance with base q.
        """

        return self._to_base10()._base10_to_any_base(q)


    def fast_2_4(self) -> Number:
        """Fast convert between representation in base2 and base4.

        Returns:
            Number instance in the other pair base.
        """

        curr_base = self.base

        if curr_base == 2:
            new_number = convert_base2_base4(self.val)
            new_base = 4

        elif curr_base == 4:
            new_number = convert_base4_base2(self.val)
            new_base = 2

        num = Number(new_number, new_base)
        return num


    def fast_2_8(self) -> Number:
        """Fast convert between representation in base2 and base8.

        Returns:
            Number instance in the other pair base
        """

        curr_base = self.base

        if curr_base == 2:
            new_number = convert_base2_base8(self.val)
            new_base = 8

        elif curr_base == 8:
            new_number = convert_base8_base2(self.val)
            new_base = 2

        num = Number(new_number, new_base)
        return num


    def fast_2_16(self):
        """Fast convert between representation in base2 and base16.

        Returns:
            Number instance in the other pair base
        """

        curr_base = self.base

        if curr_base == 2:
            new_number = convert_base2_base16(self.val)
            new_base = 16
        elif curr_base == 16:
            new_number = convert_base16_base2(self.val)
            new_base = 2

        num = Number(new_number, new_base)
        return num


    def __ge__(self, other: Number):
        """Define the behaviour of the '>=' operator on Number type."""

        return int(self._to_base10().val) >= int(other._to_base10().val)


    def __gt__(self, other: Number):
        """Define the behaviour of the '>' operator on Number type."""

        return int(self._to_base10().val) > int(other._to_base10().val)
