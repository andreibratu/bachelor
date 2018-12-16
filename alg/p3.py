"""
Input: non-zero natural number n
Output:
    1. The number of bases of the vector space Z class 2 of dim(2) over Z class
    2. The vectors of each such basis
Andrei Bratu
bratuandrei0@gmail.com
912
2018
"""

from itertools import product, permutations  # Combinatorics library
from numpy.linalg import det  # Linear algeabra library for determinant

n = int(input('Please input the dimension: '))

vectors = list(product([0, 1], repeat=n))  # Generate all vectors of dim(n)
solutions = []

for c in permutations(vectors, n):  # Generate all n-length lists of vectors
    c = [list(v) for v in c]   # Create a matrix from the list
    if det(c) % 2 != 0:  # Check if the base is linearly independent
        solutions.append(c)

print(len(solutions))
for s in solutions:
    print(s)
