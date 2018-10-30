"""
Given a set of n numbers, calculate how many partitions can be created on
the set.

The solution is documented below method by method. Here be dragons.

Andrei Bratu
bratuandrei0@gmail.com
912
2018
"""

from itertools import product

n = int(input('Kindly input the size of your set: '))
partitions_bitmask = [] # Holds all valid partitions in bitmask form.
partitions = [] # Holds all valid partitions in human readable form.
ans = [] # Holds the answer as partition-graph tuples


def backtracking(i, p):
    """Calculate all possible partitions using backtracking.

    Let us define a group as one of the subset of a partition.
    In order to ease the implementation, each group is represented
    as a bitmask - an integer in base 10 whose i-th bit is set
    only if the i-th element of the given set belongs in that group.

    At each iteration we assign each number i to all possible groups
    (A partition has a maximum of n groups). After assigning all numbers
    we check if the partition has already been found. If not, we add it.

    Apologies for this programming black magic, but it has treameandously
    helped me implementing this method.

    Args:
        i (int): The i-th number we attempt to move in a group.
        p (List): The current partition that is being built using backtracking
    """

    if i == n:
        p = sorted([x for x in p if x != 0])
        if p not in partitions_bitmask:
            partitions_bitmask.append(p)
        return

    for k in range(0, n):
        p[k] = p[k] | (1<<i)
        backtracking(i+1, list(p))
        p[k] = p[k] & ~(1<<i)


def bitmask_to_human():
    """Convert the bitmask partitions to human partitons.

    The process is the inverse of the one described above.
    """

    for partition in partitions_bitmask:
        readable = []
        for mask in partition:
            group = []
            for i in range(0, n):
                if mask & (1<<i):
                    group.append(i)
            readable.append(group)
        partitions.append(readable)


def build_graph():
    """Build the relation graph for each partition."""

    for partition in partitions:
        graph = []
        for group in partition:
            # itertools.product method returns the
            # Carthesin product of two sets
            graph += [x for x in product(group, group)]
        ans.append((partition, graph))


backtracking(0, [0 for _ in range(0, n)])
bitmask_to_human()
build_graph()


# Prepare file
filename = 'result{}.txt'.format(n)
f = open(filename, 'a') # Open file to write results

# Write how many valid partitions were found
f.write('Valid partitons: ' + str(len(ans)))
f.write('\n')

# Write first 10 valid partitions
for i in range(0, min(10, len(ans))):
    f.write(str(ans[i]))
    f.write('\n')
