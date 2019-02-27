from repos.repos.movie_repository import MovieRepository
import jsonpickle
import os


class JsonMovieRepository(MovieRepository):

    def __init__(self):

        self._path = 'storage/movies.json'

        super().__init__()

        if os.stat(self._path).st_size != 0:
            with open(self._path, 'r') as f:
                db = jsonpickle.decode(f.read(), keys=True)
                self._movies = {int(k): v for k, v in db['objects'].items()}
                self._counter = db['counter']


    def __del__(self):

        with open(self._path, 'w') as f:
            db = {
                'objects': self._movies,
                'counter': self._counter
            }
            f.write(jsonpickle.encode(db))
