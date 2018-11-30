import json

from repos.repos.client_repository import ClientRepository
from repos.repos.movie_repository import MovieRepository
from repos.repos.rental_repository import RentalRepository

from repos.pickle_repos.client_repository_pickle import PickleClientRepository
from repos.pickle_repos.movie_repository_pickle import PickleMovieRepository
from repos.pickle_repos.rental_repository_pickle import PickleRentalRepository

from repos.json_repos.client_repository_json import JsonClientRepository
from repos.json_repos.movie_repository_json import JsonMovieRepository
from repos.json_repos.rental_repository_json import JsonRentalRepository


class RepositoryFactory:

    def __init__(self):

        with open('settings.json', 'r') as f:

            mode = json.loads(f.read())['repository']

            try:
                self._objects = {
                    'pickle': {
                        'client': PickleClientRepository,
                        'movie': PickleMovieRepository,
                        'rental': PickleRentalRepository
                    },
                    'json': {
                        'client': JsonClientRepository,
                        'movie': JsonMovieRepository,
                        'rental': JsonRentalRepository
                    },
                    'inmemory': {
                        'client': ClientRepository,
                        'movie': MovieRepository,
                        'rental': RentalRepository
                    }
                }[mode]

            except KeyError:
                raise ValueError('Invalid repository setting')


    def build(self, repository_type):
        """Return instance of repository, depending on the current settings.

        Args:
            repository_type (Object): The repository (Client, Movie, Rental)
        """
        return self._objects[repository_type]()
