from copy import copy

from observer.observable import Observable

from entities.movie_entity import Movie

from repos.repos.movie_repository import MovieRepository

from helper.helper import abstract_search, print_list


class MovieController(Observable):
    """object that implements Movie related features."""


    def __init__(self, movie_repository: MovieRepository):
        Observable.__init__(self)
        self.__movie_repository = movie_repository


    def display(self):
        """Print all entities."""

        print_list(self.__movie_repository.get_all())


    def create(self, title: str, description: str, genre: str):
        """Create and insert new entity."""

        m = Movie(title=title, description=description, genre=genre)
        id = self.__movie_repository.insert(m)
        m.id = m

        change = {
            'undo': {
                'ref': self.__movie_repository.delete,
                'o': [id],
            },
            'redo': {
                'ref': self.__movie_repository.insert,
                'o': [copy(m)],
            }
        }
        self.notify([change])


    def delete(self, id: int):
        """Delete movie by id."""

        try:
            id = int(id)

            m = self.__movie_repository.get(id)

            self.__movie_repository.delete(id)

            change = {
                'undo': {
                    'ref': self.__movie_repository.insert,
                    'o': [copy(m)],
                },
                'redo': {
                    'ref': self.__movie_repository.delete,
                    'o': [id],
                }
            }

            self.notify([change])

        except KeyError:
            raise KeyError('Invalid movie index {}'.format(id))


    def update(self, id: int, title: str, description: str, genre: str):
        """Update movie by id."""

        try:
            m = self.__movie_repository.get(id)

            m_before_change = copy(m)
            m.update(
                title=title,
                genre=genre,
                description=description,
            )
            m_after_change = copy(m)

            change = {
                'undo': {
                    'ref': self.__movie_repository.update,
                    'o': [m_before_change],
                },
                'redo': {
                    'ref': self.__movie_repository.update,
                    'o': [m_after_change],
                }
            }

            self.__movie_repository.update(m)
            self.notify([change])

        except KeyError:
            raise KeyError('Invalid movie index {}'.format(id))


    def search(self, query: str):
        """Return movies that match query."""

        print(abstract_search(
            self.__movie_repository.get_all(),
            query)
        )
