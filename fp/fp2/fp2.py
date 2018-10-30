from math import sqrt
from typing import List, Callable


class Complex:
    """Class that describes a complex number."""

    def __init__(self, real, imag):
        self.real = real
        self.imag = imag
        self.modulus = sqrt(self.real**2 + self.imag**2)

    def __add__(self, other):
        return Complex(self.real + other.real, self.imag + other.imag)

    def __sub__(self, other):
        return Complex(self.real - other.real, self.imag - other.imag)

    def __eq__(self, other):
        return self.real == other.real and self.imag == other.imag

    def __str__(self):
        if self.real == 0:
            if self.imag >= 0:
                return '{}i'.format(self.imag)
            else:
                return '-{}i'.format(self.imag)

        if self.imag == 0:
            return str(self.real)

        sign = ''
        if self.imag >= 0:
            sign = '+'
        else:
            sign = '-'

        return '{}{}{}i'.format(self.real, sign, abs(self.imag))

    __repr__ = __str__ # __reprs__ is called to print objects inside lists.


def findSequenceByProperty(q: List[Complex], f: Callable) -> List[Complex]:
    """Return the longest subsequence of a given list that respects a property.

    Args:
        q (List[Complex]): The initial list.
        f (Callable): The property that all elements of subsq must respect.
                         Callable must have signature List[Complex] -> bool.
    Returns:
        The subsq of maximal length.
    """

    best_len = 0
    ans = []
    for i in range(0, len(q)-1):
        for j in range(i+1, len(q)):
            subsq = q[i:j+1]
            if f(subsq) and len(subsq) > best_len:
                best_len = len(subsq)
                ans = subsq

    return ans


def increasingModulus(a: List[Complex]) -> bool:
    """Check if a list of complex numbers have increasing modulus.

    Args:
        a (List): List of complex numbers
    Returns:
        True if the list respects the property.
    """

    for i in range(1,len(a)):
        if not a[i].modulus > a[i-1].modulus:
            return False
    return True


def realMountain(a: List[Complex]) -> bool:
    """Check if real part of numbers form a mountain.

    A mountain seq contains values that first increase, then decrease.

    Args:
        a (List): List of complex numbers.
    Returns:
        True if the list respects the property.
    """

    reals = [x.real for x in a]
    top = 0
    for i in range(1, len(reals)):
        if reals[i] > reals[i-1]:
            continue
        else:
            top = i-1
            break
    if top == len(reals)-1:
        # Strictly increasing
        return False
    if top == 0:
        # No increasing part
        return False
    for i in range(top+1, len(reals)):
        # Top is not unique
        if not reals[i] < reals[i-1]:
            return False
    return True


# Constants
PROP1 = 'the numbers have strictly increasing modulus'
PROP2 = \
'the real part of the numbers forms of a mountain'
GREETING = \
'''
=======
This is the really hip menu-based interface for the assignment. Please select
one of the options below:
    1. Append a number to the list.
    2. Print the entire list of numbers.
    3. Print the longest sequence where {}.
    4. Print the longest sequence where {}.
    5. Exit the application.
=======
'''.format(PROP1, PROP2)
INVALID_INPUT_ERROR = 'Kindly RTFM..'
GOODBYE_MESSAGE = 'Have a lovely day!'
APPEND, PRINT, P1, P2, EXIT = (1, 2, 3, 4, 5)
l = []


# Tests
assert increasingModulus([Complex(1, 0), Complex(6, 4), Complex(9, 9)]) == True
assert increasingModulus([Complex(4,-1), Complex(-2, 0)]) == False
assert realMountain(
    [Complex(2,-1), Complex(6, 3), Complex(3, -1), Complex(1, 4)]
) == True
assert realMountain([Complex(-3, 2), Complex(6, 1), Complex(7, 2)]) == False
assert realMountain([Complex(4, 1), Complex(2, 3)]) == False
assert realMountain([Complex(1, 2)]) == False


while True:
    print(GREETING)
    try:
        option = int(input('Kindly input your option: '))

        if not 1 <= option <= 5:
            print(INVALID_INPUT_ERROR)
            continue

        if option == APPEND:
            try:
                r = float(input('The real part: '))
                i = float(input('The imaginary part: '))
                l.append(Complex(r, i))
            except ValueError:
                print(INVALID_INPUT_ERROR)

        if option == PRINT:
            print(l)

        if option == P1:
            ans = findSequenceByProperty(l, increasingModulus)
            print(ans)

        if option == P2:
            ans = findSequenceByProperty(l, realMountain)
            print(ans)

        if option == EXIT:
            print(GOODBYE_MESSAGE)
            break

    except ValueError:
        print(INVALID_INPUT_ERROR)
        continue
