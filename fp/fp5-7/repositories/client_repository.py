from typing import List

from entities.client_entity import Client


class ClientRepository:
    """object that manages Client entities."""


    def __init__(self):
        self.__clients = {}
        self.__counter = 0


    def insert(self, c: Client) -> int:
        """Insert client.

        If added for the first time, an id will be assigned.
        """

        if not hasattr(c, 'id'):
            c.id = self.__counter
            self.__counter += 1

        self.__clients[c.id] = c

        return c.id


    def get(self, id: int) -> Client:
        """Return client by id."""

        return self.__clients[id]


    def get_all(self) -> List[Client]:
        """Return all clients."""

        return list(self.__clients.values())


    def delete(self, id: int):
        """Delete client by id."""

        del self.__clients[id]
