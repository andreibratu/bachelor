class Observer:
    """Abstract class implementation of Observer side of the pattern."""

    def update(self, message):
        raise NotImplementedError
