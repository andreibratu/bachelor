from copy import copy

from observer.observable import Observable

from entities.client_entity import Client

from repos.repos.client_repository import ClientRepository

from helper.helper import abstract_search, print_list


class ClientController(Observable):
    """object that implements Client related features."""


    def __init__(self, client_repository: ClientRepository):
        Observable.__init__(self)
        self._client_repository = client_repository


    def display(self):
        """Print all clients."""

        print_list(self._client_repository[:])


    def create(self, name: str):
        """Create new client."""

        c = Client(name=name)
        id = self._client_repository.insert(c)
        c.id = id

        change = {
            'undo': {'ref': self._client_repository.__delitem__, 'o': [id]},
            'redo': {'ref': self._client_repository.insert, 'o': [copy(c)]}
        }
        self.notify([change])


    def delete(self, id: int):
        """Delete client by id."""

        try:
            id = int(id)

            client = self._client_repository[id]
            change = {
                'undo': {
                    'ref': self._client_repository.insert,
                    'o': [copy(client)],
                },
                'redo': {
                    'ref': self._client_repository.__delitem__,
                    'o': [id],
                }
            }

            del self._client_repository[id]
            self.notify([change])

        except KeyError:
            raise KeyError('Invalid client index {}'.format(id))


    def update(self, id: int, name: str):
        """Update client by id."""

        try:
            id = int(id)

            c = self._client_repository[id]
            before_change = copy(c)
            c.update(name=name)
            after_change = copy(c)

            change = {
                'undo': {
                    'ref': self._client_repository.__setitem__,
                    'o': [before_change],
                },
                'redo': {
                    'ref': self._client_repository.__setitem__,
                    'o': [after_change],
                }
            }

            self._client_repository[c.id] = c
            self.notify([change])

        except KeyError:
            raise KeyError('Invalid client index {}'.format(id))


    def search(self, query: str):
        """Return clients that match query."""

        print(abstract_search(self._client_repository[:], query))
