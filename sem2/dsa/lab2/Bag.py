# Problema 2

from functools import reduce
from BagIterator import BagIterator


class Bag:

    # creates a new, empty Bag
    # O(1)
    def __init__(self):
        self.elements = []
        self.occurrences = []

    # adds a new element to the Bag
    # O(N) for iterating in order to check existence in Bag
    def add(self, e):
        try:
            idx = self.elements.index(e)
            self.occurrences[idx] += 1
        except ValueError:
            # Element not yet in array
            self.elements.append(e)
            self.occurrences.append(1)

    # removes one occurrence of an element from a Bag
    # returns True if an element was actually removed
    # (the Bag contained the element e), or False if nothing was removed
    # O(n) for finding element in Bag
    def remove(self, e):
        try:
            idx = self.elements.index(e)
            self.occurrences[idx] -= 1
            if self.occurrences[idx] == 0:
                # Remove record if no elements are left
                self.elements.pop(idx)
                self.occurrences.pop(idx)
            return True
        except ValueError:
            return False

    # searches for an element e in the Bag
    # returns True if the Bag contains the element, False otherwise
    # O(N)
    def search(self, e):
        try:
            _ = self.elements.index(e)
            return True
        except ValueError:
            return False

    # counts and returns the number of times the element e appears in the bag
    # O(N)
    def nrOccurrences(self, e):
        try:
            idx = self.elements.index(e)
            return self.occurrences[idx]
        except ValueError:
            return 0

    # returns the size of the Bag (the number of elements)
    # O(N)
    def size(self):
        if len(self.occurrences) != 0:
            return reduce(lambda acc, x: acc+x, self.occurrences)
        else:
            return 0

    # returns True if the Bag is empty, False otherwise
    # O(1)
    def isEmpty(self):
        return self.elements == []

    # returns a BagIterator for the Bag
    def iterator(self):
        return BagIterator(self)
