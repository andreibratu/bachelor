# Andrei Bratu
# Generate the largest prime number smaller than a given natural number n.
# If such a number does not exist, a message should be displayed.

from math import sqrt


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


# Tests
assert isPrime(37)
assert isPrime(2)
assert isPrime(47)
assert not isPrime(81)
assert not isPrime(6)


n = int(input("Kindly input a number: "))
if n<0:
    print('Please input a natural number')
else:
    found = -1
    for i in range(2, n):
        if isPrime(i):
            found = i
    if found == -1:
        print('No prime number smaller than n exists..')
    else:
        print('Largest prime number smaller than n is', found)
