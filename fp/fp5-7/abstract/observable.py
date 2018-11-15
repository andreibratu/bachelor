class Observable:
    """Abstract class implementation of Observable side of the pattern."""

    def subscribe(self):
        raise NotImplementedError

    def notify(self):
        raise NotImplementedError
