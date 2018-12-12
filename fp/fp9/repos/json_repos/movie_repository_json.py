from repos.abstract_repos.json_repository import JsonRepository
from repos.repos.movie_repository import MovieRepository


class JsonMovieRepository(MovieRepository, JsonRepository):

    def __init__(self):
        MovieRepository.__init__(self)
        JsonRepository.__init__(self, path='storage/movies.json')
