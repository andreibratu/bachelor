# Andrei Bratu
# Generate the largest perfect number smallest than a given natural number n.
# If such a number does not exist, a message should be displayed. A number is
# perfect if it is equal to the sum of its divisors, except itself.
# E.g. 6 is a perfect number (6=1+2+3).

from math import sqrt
from functools import reduce
from typing import List


def findPerfectDivs(x: int) -> List[int]:
    """Return the divisors of given number that are smaller than given number.

    Args:
        x (int): The number.
    Returns:
        The list of divs smaller than the number itself.
    """

    return [i for i in range(1,x) if x%i == 0]


def isPerfect(x: int) -> bool:
    """Check if given number is perfect.

    The method uses a lambda function to sum over the divs returned by the
    findPerfectDivs method. The reduce functional pattern is used in order to
    sum the perfect divisors of the number.

    Args:
        x (int): The number to be checked.
    Returns:
        True if the number is perfect, False if not.
    """

    return x == reduce(lambda accum, next: accum+next, findPerfectDivs(x), 0)


def isPrime(x: int) -> bool:
    """Check if given number is prime.

    The square root primality test is used. Since any divisor d1 of x implies
    the existence of d2 such as x = d1 * d2, it is sufficient to check for
    divisors only until sqrt(x), since it is impossible to find divisors after
    sqrt(x) without having found its smaller co-divisor already.

    Args:
        x (int): The number to be tested.
    Returns:
        True if the given number is fine.
    """
    if x == 1:
        return False
    if x == 2:
        return True
    if x%2 == 0:
        return False
    r = int(sqrt(x))
    for i in range(2, r+1):
        if x%i == 0:
            return False
    return True


def findPerfectImproved(n: int) -> int:
    """Find the largest perfect number smaller than n.

    Euclid-Euler theorem states that if 2**p-1 is prime then
    2^(p-1)*(2^p-1) is a perfect number. Thus, using a primality test,
    worst case complexity is reduced from O(N^2) to O(logN*sqrtN). There are
    no known odd perfect numbers. Since there are only 50 known numbers,
    it would be optimal to use a lookup table.

    Args:
        n (int): The upper bound.
    Returns:
        The largest perfect number smaller than n, or -1 if it does not exist.
    """

    p = 0
    found = -1
    while True:
        if isPrime(2**p-1):
            aux = 2**(p-1)*(2**p-1)
            if aux < n:
                found = aux
            else:
                break
        p += 1
    return found


# Tests
assert isPerfect(6)
assert not isPerfect(1)
assert isPrime(37)
assert isPrime(2)
assert isPrime(47)
assert findPerfectImproved(7) == 6
assert findPerfectImproved(3) == -1
assert findPerfectImproved(78) == 28
assert findPerfectImproved(13456) == 8128


# Program below uses the less efficient algorithm in O(N^2)
while True:
    n = int(input('Kindly input a number: '))
    if n == 0:
        break
    found = -1
    for i in range(1, n):
        if isPerfect(i):
            found = i
    if found == -1:
        print('No perfect number smaller than n exists..')
    else:
        print('The largest perfect number smaller than n is', found)
