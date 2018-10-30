"""
Given a set of n numbers, find how many associative laws can be defined on
the set.

This solution uses backtracking in order to generate all possible laws
on the set, keeping only the valid ones.

Since we can define (N^N)^N laws over a set of N numbers, computation
using this solution becomes unpheasible even for values larger than 5.

Andrei Bratu
bratuandrei0@gmail.com
912
2018
"""

import os # Needed for file I/O

n = int(input('Kindly input the size of the set '))
valid = []


def validate(law):
    """Given a law check if it is associative.

    The law is represented as a dictionary data structure with pairs as keys.
    Each pair (a, b) holds the associated a*b value
    """
    for i in range(0, n):
        for j in range(0, n):
            for k in range(0, n):
                # (i * j) * k = i * (j * k)
                a = law[(i, j)] # aux variable for i * j
                b = law[(j, k)] # aux variable for j * k
                if law[(a, k)] != law[(i, b)]:
                    return False
    return True


def backtracking(r, c, law):
    """Method that determines all laws that can be defined on n-sized set.

    The method uses the backtracking method to recursively generate all laws.
    A law is defined by its NxN table.

    r -> row
    c -> column
    law -> law currently being built
    """
    if r == n:
        # Filled all rows of the law table, time to validate
        if validate(law):
            valid.append(law)
        return
    if c == n:
        # Filled one row, moving to the next
        backtracking(r+1, 0, dict(law))
    if c < n:
        for k in range(0, n):
            # Attempt all possible values for current position (law[r][c])
            law[(r,c)] = k
            backtracking(r, c+1, dict(law))


backtracking(0, 0, {}) # Start looking for solutions

filename = 'result{}.txt'.format(n)
f = open(filename, 'a') # Open file to write results

# Write how many valid laws were found
f.write('Valid laws: ' + str(len(valid)))
f.write('\n')

# Print the first 10 associative laws
for i in range(0, len(valid)):
    sol = [[0]*n]*n # An NxN matrix
    for pair, val in valid[i].items():
        # Fill the law table with values
        r, c = pair
        sol[r][c] = val
    # Write law in file
    f.write(str(sol))
    f.write('\n')
