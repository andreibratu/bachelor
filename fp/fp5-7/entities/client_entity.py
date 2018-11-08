class Client:
    """Class that describes the Client entity."""

    id_counter = 0

    def __init__(self, name: str):
        self.name = name
        self.__rentals = []
        self.id = Client.id_counter
        Client.id_counter += 1

    def __str__(self):
        return '-'.join((str(self.id), self.name))

    def update(self, name):
        self.name = name

    __repr__ = __str__
