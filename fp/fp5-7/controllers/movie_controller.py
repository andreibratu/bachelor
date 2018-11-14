from repositories.movie_repository import MovieRepository
from entities.movie_entity import Movie
from helper import abstract_search, print_list


class MovieController:
    """Object that implements Movie related features."""


    def __init__(self):
        self.movie_repository = MovieRepository()


    def display(self):
        """Print all entities."""

        print_list(self.movie_repository.get_all())


    def create(self, title: str, description: str, genre: str):
        """Create and insert new entity."""

        m = Movie(title=title, description=description, genre=genre)
        self.movie_repository.insert(m)


    def delete(self, id: int):
        """Delete movie by id.

        Raises:
            KeyError: Given movie does not exist.
            ValueError: id is not parsable to int.
        """

        try:
            id = int(id)
            self.movie_repository.delete(id)

        except KeyError:
            raise KeyError('Invalid movie index {}'.format(id))

        except ValueError:
            raise ValueError('Could not parse given id {}'.format(id))


    def update(self, id: int, title: str, description: str, genre: str):
        """Update movie by id.

        Raises:
            KeyError: Given movie does not exist.
        """

        try:
            m = self.movie_repository.get(id)
            m.update(
                title=title,
                description=description,
                genre=genre
            )
            self.movie_repository.insert(m)

        except KeyError:
            raise KeyError('Invalid movie index {}'.format(id))


    def search(self, query: str):
        """Return movies that match query."""

        print(abstract_search(
            self.movie_repository.get_all(),
            query)
        )
