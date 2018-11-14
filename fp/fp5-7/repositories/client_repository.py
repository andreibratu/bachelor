from entities.client_entity import Client
from typing import List


class ClientRepository:
    """Object that manages Client entities."""

    __clients = {}
    __counter = 0


    def insert(self, c: Client):
        """Insert client into repository."""

        if not hasattr(c, 'id'):
            c.id = ClientRepository.counter
            ClientRepository.counter += 1

        ClientRepository.__clients[c.id] = c


    def get(self, id: int) -> Client:
        """Return a client by id."""

        return ClientRepository.__clients[id]


    def delete(self, id: int):
        """Delete client by id."""

        del ClientRepository.__clients[id]


    def get_all(self) -> List:
        """Return all client entities."""

        return list(ClientRepository.__clients.values())
