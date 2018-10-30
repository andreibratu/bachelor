# Andrei Bratu
# Consider a given natural number n. Determine the product p of all
# the proper factors of n.

from functools import reduce
from typing import List


def findProperFactors(x: int) -> List[int]:
    """Find the proper factors of a given number.

    The proper factors of a number are all its divisors but 1 and itself.
    Thus, prime numbers have no proper factors.

    Args:
        x (int): The number to be tested.
    Returns:
        The list of proper divisors.
    """

    return [i for i in range(2,x) if x%i == 0]


# Tests
assert findProperFactors(6) == [2,3]
assert findProperFactors(1) == []
assert findProperFactors(7) == []


n = int(input('Kindly input a number: '))
if n<0:
    print('Please input a natural number')
else:
    divs = findProperFactors(n)
    if divs == []:
        print('Given number has no proper factors') # Is prime or 1.
    else:
        # Reduce pattern is used to calculate the product of divisors.
        p = reduce(lambda acc, x: acc*x, divs, 1)
        print('The product is', p)
