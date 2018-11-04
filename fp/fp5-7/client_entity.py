class Client:
    """Class that describes the Client entity."""

    client_id_counter = 0

    def __init__(self, name: str):
        self.name = name
        self.rentals = []
        self.client_id = Client.client_id_counter
        Client.client_id_counter += 1

    def __str__(self):
        return self.name

    def update(self, name):
        self.name = name

    __repr__ = __str__
