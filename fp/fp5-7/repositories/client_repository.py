from entities.client_entity import Client
from abstract.observable import Observable
from typing import List


class ClientRepository(Observable):
    """Object that manages Client entities."""


    def __init__(self):
        self.__clients = {}
        self.__counter = 0
        self.__observers = []


    def insert(self, c: Client):
        """Insert client into repository."""

        if not hasattr(c, 'id'):
            c.id = self.__counter
            self.__counter += 1

        self.__clients[c.id] = c


    def get(self, id: int) -> Client:
        """Return a client by id."""

        return self.__clients[id]


    def delete(self, id: int):
        """Delete client by id."""

        del self.__clients[id]


    def get_all(self) -> List:
        """Return all client entities."""

        return list(self.__clients.values())
