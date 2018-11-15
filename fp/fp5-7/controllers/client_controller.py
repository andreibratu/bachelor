from repositories.client_repository import ClientRepository
from entities.client_entity import Client
from helper import abstract_search, print_list


class ClientController:
    """Object that implements Client related features."""

    def __init__(self, client_repository: ClientRepository):
        self.__client_repository = client_repository


    def create(self, name: str):
        """Create new client."""

        c = Client(name=name)
        self.__client_repository.insert(c)


    def display(self):
        """Print all __clients in the db."""

        print_list(self.__client_repository.get_all())


    def search(self, query: str):
        """Return clients that match query."""

        print(abstract_search(
            self.__client_repository.get_all(),
            query)
        )
