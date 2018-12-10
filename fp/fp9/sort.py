# Kudos: Mohit Kumra from https://www.geeksforgeeks.org/shellsort/

from typing import List, Callable


def shell_sort(arr: List, cmp: Callable):
    """Implementation of shell sort agorithm.

    Args:
        arr:
    """

    # Start with a big gap, then reduce the gap
    n = len(arr)
    gap = n // 2

    # Do a gapped insertion sort for this gap size.
    # The first gap elements a[0..gap-1] are already in gapped
    # order keep adding one more element until the entire array
    # is gap sorted
    try:
        while gap > 0:

            for i in range(gap, n):

                # add a[i] to the elements that have been gap sorted
                # save a[i] in temp and make a hole at position i
                temp = arr[i]

                # shift earlier gap-sorted elements up until the correct
                # location for a[i] is found
                j = i
                while j >= gap and not cmp(arr[j - gap], temp):
                    arr[j] = arr[j - gap]
                    j -= gap

                # put temp (the original a[i]) in its correct location
                arr[j] = temp
            gap //= 2
    except TypeError:
        raise TypeError('Comparison callable should expect 2 args')
