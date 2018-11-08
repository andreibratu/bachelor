from entities.movie_entity import Movie
from typing import List


class MovieRepository:
    """Object that manages and accepts queries for the Movie entities."""


    __movies = {}
    __count = 0


    def insert(self, m: Movie):
        """Insert a movie.

        If the object is inserted for the first time, the repo
        will assign an id.

        Args:
            m (Movie): Movie to be inserted.
        """

        if not hasattr(m, 'id'):
            m.id = MovieRepository.__count
            MovieRepository.__count += 1

        MovieRepository.__movies[m.id] = m


    def get(self, id: str) -> Movie:
        """Get movie by id."""

        return MovieRepository.__movies[id]


    def find_all(self) -> List[Movie]:
        """Return all entities."""

        return list(MovieRepository.__movies.values())


    def delete(self, id: int):
        """Delete movie by id."""

        del self.__movies[id]
