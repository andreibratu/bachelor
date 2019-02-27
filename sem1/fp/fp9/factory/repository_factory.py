import json

from repos.repos.client_repository import ClientRepository
from repos.repos.movie_repository import MovieRepository
from repos.repos.rental_repository import RentalRepository

from repos.file_repos.file_client_repository import FileClientRepository
from repos.file_repos.file_movie_repository import FileMovieRepository
from repos.file_repos.file_rental_repository import FileRentalRepository

from repos.sql_repos.sql_client_repository import SqlClientRepository
from repos.sql_repos.sql_movie_repository import SqlMovieRepository
from repos.sql_repos.sql_rental_repository import SqlRentalRepository


class RepositoryFactory:

    def __init__(self):

        with open('settings.json', 'r') as f:

            mode = json.loads(f.read())['repository']

            try:
                self._objects = {
                    'pickle': {
                        'client': FileClientRepository,
                        'movie': FileMovieRepository,
                        'rental': FileRentalRepository
                    },
                    'json': {
                        'client': FileClientRepository,
                        'movie': FileMovieRepository,
                        'rental': FileRentalRepository
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
