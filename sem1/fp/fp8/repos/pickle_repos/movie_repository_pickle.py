from repos.repos.movie_repository import MovieRepository
import pickle
import os


class PickleMovieRepository(MovieRepository):
    """Binary storage implementation of the MovieRepository."""

    def __init__(self):

        self._path = 'storage/movies.txt'

        super().__init__()

        if os.stat(self._path).st_size != 0:
            with open(self._path, 'rb') as f:
                db = pickle.load(f)
                self._movies = {int(k): v for k, v in db['objects'].items()}
                self._counter = db['counter']


    def __del__(self):

        with open(self._path, 'wb') as f:
            db = {
                'objects': self._movies,
                'counter': self._counter
            }
            pickle.dump(db, f)
