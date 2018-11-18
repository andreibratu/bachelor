class Client:
    """Class that describes the Client entity."""

    def __init__(self, name: str):
        self.name = name

    def __str__(self):
        return self.name

    def update(self, name):
        self.name = name

    __repr__ = __str__
