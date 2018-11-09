from repositories.client_repository import ClientRepository
from entities.client_entity import Client
from helper import abstract_search


class ClientController:
    """Object that implements Client related features."""


    def __init__(self):
        self.client_repository = ClientRepository()


    def create(self, name: str):
        """Create new client."""

        c = Client(name=name)
        self.client_repository.insert(c)


    def display(self):
        """Print all __clients in the db."""

        print(self.client_repository.get_all())


    def search(self, query: str):
        """Return clients that match query."""

        print(abstract_search(
            self.client_repository.get_all(),
            query
            )
        )
