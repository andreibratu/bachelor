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

from repos.sql_repos.client_repository_sql import SqlClientRepository
from repos.sql_repos.movie_repository_sql import SqlMovieRepository
from repos.sql_repos.rental_repository_sql import SqlRentalRepository


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
                    },
                    'sql': {
                        'client': SqlClientRepository,
                        'movie': SqlMovieRepository,
                        'rental': SqlRentalRepository
                    }
                }[mode]

            except KeyError:
                raise ValueError('Invalid repository setting')


    def build(self, repository_type, args):
        """Return instance of repository, depending on the current settings.

        Args:
            repository_type (Object): The repository (Client, Movie, Rental)
            args (Dict): Constructor args to be passed to repo __init__
        """

        if args is None:
            return self._objects[repository_type]()

        return self._objects[repository_type](**args)
