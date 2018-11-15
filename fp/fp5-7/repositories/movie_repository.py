from typing import List

from entities.movie_entity import Movie


class MovieRepository:
    """Object that manages Movie entities."""


    def __init__(self):
        self.__movies = {}
        self.__count = 0


    def insert(self, m: Movie):
        """Insert a movie.

        If the object is inserted for the first time, the repo
        will assign an id.
        """

        if not hasattr(m, 'id'):
            m.id = self.__count
            self.__count += 1

        self.__movies[m.id] = m


    def get(self, id: str) -> Movie:
        """Get movie by id."""

        return self.__movies[id]


    def get_all(self) -> List[Movie]:
        """Return all entities."""

        return list(self.__movies.values())


    def delete(self, id: int):
        """Delete movie by id."""

        del self.__movies[id]
