from entity.client import Client
from typing import List


class ClientDao:
    """Object that manages and accepts queries for the Client entities."""

    clients = {}


    def create_client(name: str):
        """Create new client."""

        c = Client(name=name)
        ClientDao.clients[c.client_id] = c


    def find_client_id(id: int) -> Client:
        """Return a client by id.

        Args:
            id (int): The id of the queried client.
        Returns:
            The client object.
        Raises:
            KeyError: No client with given id exists.
        """

        try:
            return ClientDao.clients[id]
        except KeyError:
            raise KeyError('Invalid client index {}'.format(id))


    def delete_client_id(id: int):
        """Delete client by id.

        Raises:
            KeyError: Given user does not exist.
        """

        try:
            del ClientDao.clients[id]
        except KeyError:
            raise KeyError('Invalid client index {}'.format(id))


    def update_client(id: int, name: str):
        """Update existing client using its id.

        Args:
            id (int): The idx of the user to be modified.
            name (str): The new name of the user.
        Raises:
            KeyError: Given client does not exist.
        """
        # TODO CHECK FOR UPDATE VS DELETE
        try:
            del ClientDao.clients[id]
        except KeyError:
            raise KeyError('Invalid client index {}'.format(id))


    def find_client_name(name: str):
        """Find client by name."""

        try:
            client = [c for c in ClientDao.clients.values() if c.name == name]
            return client[0]
        except IndexError:
            raise ValueError('Could not find a client with given name')


    def list_clients() -> List[Client]:
        """Return all clients stored in the DAO.

        Returns:
            A list containing all clients
        """

        return ClientDao.clients.values()
