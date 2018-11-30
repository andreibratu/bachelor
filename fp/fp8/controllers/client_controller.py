from copy import copy

from abstract.observable import Observable

from entities.client_entity import Client

from repos.repos.client_repository import ClientRepository

from helper.helper import abstract_search, print_list


class ClientController(Observable):
    """object that implements Client related features."""


    def __init__(self, client_repository: ClientRepository):
        Observable.__init__(self)
        self.__client_repository = client_repository


    def display(self):
        """Print all clients."""

        print_list(self.__client_repository.get_all())


    def create(self, name: str):
        """Create new client."""

        c = Client(name=name)
        id = self.__client_repository.insert(c)

        change = {
            'undo': {'ref': self.__client_repository, 'o': id, 'op': 'delete'},
            'redo': {'ref': self.__client_repository, 'o': c, 'op': 'insert'}
        }
        self.notify([change])


    def delete(self, id: int):
        """Delete client by id."""

        try:
            id = int(id)

            client = self.__client_repository.get(id)
            change = {
                'undo': {
                    'ref': self.__client_repository,
                    'o': client,
                    'op': 'insert'},
                'redo': {
                    'ref': self.__client_repository,
                    'o': id,
                    'op': 'delete'}
            }

            self.__client_repository.delete(id)
            self.notify([change])

        except KeyError:
            raise KeyError('Invalid client index {}'.format(id))


    def update(self, id: int, name: str):
        """Update client by id."""

        try:
            id = int(id)

            c = self.__client_repository.get(id)
            before_change = copy(c)
            c.update(name=name)
            after_change = copy(c)

            change = {
                'undo': {
                    'ref': self.__client_repository,
                    'o': before_change,
                    'op': 'insert'},
                'redo': {
                    'ref': self.__client_repository,
                    'o': after_change,
                    'op': 'insert'}
            }

            self.__client_repository.insert(c)
            self.notify([change])

        except KeyError:
            raise KeyError('Invalid client index {}'.format(id))


    def search(self, query: str):
        """Return clients that match query."""

        print(abstract_search(
            self.__client_repository.get_all(),
            query)
        )
