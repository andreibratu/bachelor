from copy import copy

from observer.observable import Observable

from entities.movie_entity import Movie

from repos.repos.movie_repository import MovieRepository

from helper.helper import abstract_search, print_list


class MovieController(Observable):
    """object that implements Movie related features."""


    def __init__(self, movie_repository: MovieRepository):
        Observable.__init__(self)
        self._movie_repository = movie_repository


    def display(self):
        """Print all entities."""

        print_list(self._movie_repository[:])


    def create(self, title: str, description: str, genre: str):
        """Create and insert new entity."""

        m = Movie(title=title, description=description, genre=genre)
        id = self._movie_repository.insert(m)
        m.id = m

        change = {
            'undo': {'ref': self._movie_repository.__delitem__, 'o': [id]},
            'redo': {'ref': self._movie_repository.insert, 'o': [copy(m)]}
        }
        self.notify([change])


    def delete(self, id: int):
        """Delete movie by id."""

        try:
            id = int(id)

            m = self._movie_repository[id]

            del self._movie_repository[id]

            change = {
                'undo': {'ref': self._movie_repository.insert, 'o': [copy(m)]},
                'redo': {'ref': self._movie_repository.__delitem__, 'o': [id]}
            }

            self.notify([change])

        except KeyError:
            raise KeyError('Invalid movie index {}'.format(id))


    def update(self, id: int, title: str, description: str, genre: str):
        """Update movie by id."""

        try:
            m = self._movie_repository[id]

            m_before_change = copy(m)
            m.update(
                title=title,
                genre=genre,
                description=description,
            )
            m_after_change = copy(m)

            change = {
                'undo': {
                    'ref': self._movie_repository.update,
                    'o': [m_before_change],
                },
                'redo': {
                    'ref': self._movie_repository.update,
                    'o': [m_after_change],
                }
            }

            self._movie_repository[m.id] = m
            self.notify([change])

        except KeyError:
            raise KeyError('Invalid movie index {}'.format(id))


    def search(self, query: str):
        """Return movies that match query."""

        print(abstract_search(self._movie_repository[:], query))
