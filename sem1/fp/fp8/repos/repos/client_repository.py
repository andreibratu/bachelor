from typing import List

from entities.client_entity import Client


class ClientRepository:
    """Object that manages Client entities."""


    def __init__(self):
        self._clients = {}
        self._counter = 1


    def insert(self, c: Client) -> int:
        """Insert client."""

        c.id = self._counter
        self._counter += 1
        self._clients[c.id] = c

        return c.id


    def update(self, c: Client) -> int:
        """Update client."""

        self._clients[c.id] = c
        return c.id


    def get(self, id: int) -> Client:
        """Return client by id."""

        return self._clients[id]


    def get_all(self) -> List[Client]:
        """Return all clients."""

        return list(self._clients.values())


    def delete(self, id: int):
        """Delete client by id."""

        del self._clients[id]
