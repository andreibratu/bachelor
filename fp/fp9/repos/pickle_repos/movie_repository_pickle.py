from repos.abstract_repos.pickle_repository import PickleRepository
from repos.repos.movie_repository import MovieRepository


class PickleMovieRepository(MovieRepository, PickleRepository):
    """Pickle implementation of the MovieRepository."""

    def __init__(self):
        MovieRepository.__init__(self)
        PickleRepository.__init__(self, path='storage/movies.txt')
