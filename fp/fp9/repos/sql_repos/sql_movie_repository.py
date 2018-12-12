from typing import List
from pony.orm import db_session, desc

from entities.movie_entity import Movie


class SqlMovieRepository:
    """SQL backed implementation of Client entity."""


    def __init__(self, db, movie_manager):
        self._db = db
        self._movie_manager = movie_manager
        with db_session:
            try:
                self._counter = \
                    self._movie_manager.select().order_by(
                        desc(self._movie_manager.id))[:][0].id + 1
            except IndexError:
                self._counter = 1


    @db_session
    def insert(self, m: Movie) -> int:
        """Insert movie."""

        if not hasattr(m, 'id'):
            m.id = self._counter
            self._counter += 1
        m = self._movie_manager(
            id=m.id,
            title=m.title,
            description=m.description,
            genre=m.genre)
        return m.id


    @db_session
    def update(self, m: Movie) -> int:
        """Update movie."""

        self._movie_manager[m.id](
            title=m.title,
            description=m.description,
            genre=m.genre
        )
        return m.id


    @db_session
    def get(self, id: int) -> Movie:
        """Return movie by id."""

        e = self._movie_manager[id]
        return Movie(
            id=e.id,
            title=e.title,
            description=e.description,
            genre=e.genre)


    @db_session
    def get_all(self) -> List[Movie]:
        """Return all movies."""

        entities = self._movie_manager.select()[:]
        return [self.get(m.id) for m in entities]


    @db_session
    def delete(self, id: int):
        """Delete movie by id."""

        self._movie_manager[id].delete()
