class IterableRepository:
    """Abstract implementation of an iterable repository."""


    def __init__(self):
        self._objects = {}
        self._counter = 1


    def insert(self, o) -> int:
        """Insert an object."""

        o.id = self._counter
        self._counter += 1
        self._objects[o.id] = o

        return o.id


    def __getitem__(self, key):

        if isinstance(key, slice):
            return list(self._objects.values())[key.start:key.stop:key.step]

        return self._objects[key]


    def __setitem__(self, key, o):
        self._objects[key] = o


    def __delitem__(self, key):
        del self._objects[key]


    def __iter__(self):
        self._idx = 1
        return self


    def __next__(self):
        if self._idx < len(self._objects):
            result = self._objects[self._idx]
            self._idx += 1
            return result
        else:
            raise StopIteration
