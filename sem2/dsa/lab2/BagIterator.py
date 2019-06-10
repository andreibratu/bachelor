class BagIterator:

    #creates an iterator for the Bag b, set to the first element of the bag, or invalid if the Bag is empty
    def __init__(self, b):
        self.bag = b
        self.idx = 0
        self.counter = 0

    # returns True if the iterator is valid
    # O(1)
    def valid(self):
        return self.idx < len(self.bag.elements)

    # returns the current element from the iterator.
    # throws ValueError if the iterator is not valid
    # O(1)
    def getCurrent(self):
        if not self.valid():
            raise ValueError
        return self.bag.elements[self.idx]

    # moves the iterator to the next element
    #throws ValueError if the iterator is not valid
    # O(1)
    def next(self):
        if not self.valid():
            raise ValueError
        self.counter += 1
        if self.counter == self.bag.occurrences[self.idx]:
            self.idx += 1
            self.counter = 0

    # sets the iterator to the first element from the Bag
    # O(1)
    def first(self):
        self.idx = 0
        self.counter = 0
