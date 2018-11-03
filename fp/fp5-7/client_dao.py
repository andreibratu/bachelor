from client_entity import Client
from typing import List
from abstract_dao import AbstractDao

class ClientDao(AbstractDao):
    """Object that manages and accepts queries for the Client entities."""

    def create(self, name: str):
        """Create new client."""

        c = Client(name=name)
        ClientDao.objects[c.client_id] = c


    def find_id(self, id: int) -> Client:
        """Return a client by id.

        Args:
            id (int): The id of the queried client.
        Returns:
            The client object.
        Raises:
            KeyError: No client with given id exists.
        """

        try:
            return ClientDao.objects[id]
        except KeyError:
            raise KeyError('Invalid client index {}'.format(id))


    def delete_id(self, id: int):
        """Delete client by id.

        Raises:
            KeyError: Given user does not exist.
        """

        try:
            del ClientDao.objects[id]
        except KeyError:
            raise KeyError('Invalid client index {}'.format(id))


    def update(self, id: int, name: str):
        """Update existing client using its id.

        Args:
            id (int): The idx of the user to modify.
            name (str): The update name.
        Raises:
            KeyError: Given client does not exist.
        """

        try:
            ClientDao.objects[id].update(name=name)
        except KeyError:
            raise KeyError('Invalid client index {}'.format(id))


    def find_client_name(self, name: str):
        """Find client by name."""

        try:
            client = [c for c in ClientDao.objects.values() if c.name == name]
            return client[0]
        except IndexError:
            raise ValueError('Could not find a client with given name')
