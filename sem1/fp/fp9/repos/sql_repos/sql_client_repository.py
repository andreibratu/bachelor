from typing import List
from pony.orm import db_session, desc

from entities.client_entity import Client


class SqlClientRepository:
    """SQL backed implementation of Client entity."""


    def __init__(self, db, client_manager):
        self._db = db
        self._client_manager = client_manager
        with db_session:
            try:
                self._counter = \
                    self._client_manager.select().order_by(
                        desc(self._client_manager.id))[:][0].id + 1
            except IndexError:
                self._counter = 1


    @db_session
    def insert(self, c: Client) -> int:
        """Insert client."""

        if not hasattr(c, 'id'):
            c.id = self._counter
            self._counter += 1
        c = self._client_manager(id=c.id, name=c.name)
        return c.id


    @db_session
    def update(self, c: Client) -> int:
        """Update client."""

        with db_session:
            self._client_manager[c.id].set(name=c.name)


    @db_session
    def get(self, id: int) -> Client:
        """Return client by id."""

        entity = self._client_manager[id]
        return Client(id=entity.id, name=entity.name)


    @db_session
    def get_all(self) -> List[Client]:
        """Return all clients."""

        entities = self._client_manager.select()[:]
        return [self.get(c.id) for c in entities]


    @db_session
    def delete(self, id: int):
        """Delete client by id."""

        self._client_manager[id].delete()
