class Client:
    """Class that describes the Client entity."""

    def __init__(self, name: str, id: int = None):
        if id is not None:
            self.id = id
        self.name = name

    def __str__(self):
        return ' -- '.join((
            str(self.id),
            self.name)
        )

    def update(self, name):
        self.name = name

    __repr__ = __str__
