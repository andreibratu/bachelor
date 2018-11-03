from movie_entity import Movie
from typing import List
from abstract_dao import AbstractDao

class MovieDao(AbstractDao):
    """Object that manages and accepts queries for the Movie entities."""

    def create(self, title: str, description: str, genre: str):
        """Create new movie."""

        m = Movie(title=title, description=description, genre=genre)
        MovieDao.objects[m.movie_id] = m


    def find_id(id: int) -> Movie:
        """Return movie by id.

        Args:
            id (int): The id of the queried movie.
        Returns:
            The movie object.
        Raises:
            KeyError: No movie with given id exists.
        """

        try:
            return MovieDao.objects[id]
        except KeyError:
            raise KeyError('Invalid movie index {}'.format(id))


    def delete_id(self, id: int):
        """Delete movie by id.

        Raises:
            KeyError: Given movie does not exist.
        """

        try:
            del MovieDao.objects[id]
        except KeyError:
            raise KeyError('Invalid movie index {}'.format(id))


    def update_movie(self, id: int, title: str, description: str, genre: str):
        """Update movie by id.

        Args:
            id (int): The idx of the movie to modify.
            title (str): The update title.
            description (str): The update description.
            genre (str): The update genre.
        Raises:
            KeyError: Given movie does not exist.
        """

        try:
            MovieDao.objects[id].update(
                title=title,
                description=description,
                genre=genre
            )
        except KeyError:
            raise KeyError('Invalid movie index {}'.format(id))

    def find_movie_title(self, title: str) -> Movie:
        """Find a movie by its title.

        Args:
            title (str): The title of the movie.
        Returns:
            The movie.
        """

        try:
            return [m for m in MovieDao.objects.values() if m.title == title][0]
        except IndexError:
            raise IndexError('No movie was found')
