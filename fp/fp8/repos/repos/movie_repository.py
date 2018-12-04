from typing import List

from entities.movie_entity import Movie


class MovieRepository:
    """Object that manages Movie entities."""


    def __init__(self):
        self._movies = {}
        self._counter = 1


    def insert(self, m: Movie) -> int:
        """Insert movie."""

        m.id = self._counter
        self._counter += 1
        self._movies[m.id] = m

        return m.id


    def update(self, m: Movie) -> int:
        """Update movie."""

        self._movies[m.id] = m
        return m.id


    def get(self, id: int) -> Movie:
        """Get movie by id."""

        return self._movies[id]


    def get_all(self) -> List[Movie]:
        """Return all entities."""

        return list(self._movies.values())


    def delete(self, id: int):
        """Delete movie by id."""

        del self._movies[id]
