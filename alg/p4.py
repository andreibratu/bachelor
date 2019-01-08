"""
Project 4
Input: non-zero natural numbers k and n with k ≤ n
Output:
    1. the number of k-dim subspaces of the vector space Z class 2 of dim(2)
    2. A basis of each such subspace

Andrei Bratu
bratuandrei0@gmail.com
912
"""

from itertools import product, combinations
from numpy import sum, transpose, array


def is_base(base):
    """Given a list of vectors, check if it is a base.

    The method generates all linear combinations of vectors but the trivial
    ones (the vector itself) and checks weher the combination is a member
    of the base.
    """

    for c in product([0, 1], repeat=k):

        if c.count(1) == 1:
            # Trivial combination
            continue

        # Sum the vectors from the linear combination
        v = [c[i] * array(base[i]) for i in range(k)]
        v = [x % 2 for x in transpose(sum(v, axis=0))]

        if v in base:
            return False

    return True


def generate_vectors_base(base):
    """Generate all linear combinations of a subspace."""

    for c in product([0, 1], repeat=k):
        v = [c[i] * array(base[i]) for i in range(k)]
        v = [x % 2 for x in transpose(sum(v, axis=0))]

        yield v


def independent_bases(base_a, base_b):
    """
    Determine if two k-dim subspaces, given by their bases, are independent.

    If two subspaces differ by at least one vector they are independent.
    """

    subspace_a = [v for v in generate_vectors_base(base_a)]
    subspace_b = [v for v in generate_vectors_base(base_b)]

    count = 0
    for v in subspace_a:
        if v in subspace_b:
            count += 1

    return count != len(subspace_a)


k = int(input('Please input the dimension of the subspace: '))
n = int(input('Please input the dimension of the vector space: '))

vectors = list(product([0, 1], repeat=n))  # Generate all vectors of dim(n)
vectors.remove(tuple([0 for _ in range(n)]))
solution = []

# Generate all bases of dim(k)
for c in combinations(vectors, k):
    c = [list(v) for v in c]
    if is_base(c):
        is_independent = True
        # Compare current base with those already found for collisions
        for base in solution:
            if not independent_bases(base, c):
                is_independent = False
                break
        if is_independent:
            solution.append(c)

# Write results to file
with open(f'output_k{k}_n{n}.txt', 'w') as f:
    f.write(f'k={k} n={n} ans={len(solution)}\n')
    for base in solution:
        f.write(str(base))
        f.write('\n')
