from repos.repos.rental_repository import RentalRepository
import jsonpickle
import os


class JsonRentalRepository(RentalRepository):

    def __init__(self):

        self._path = 'storage/rentals.json'

        super().__init__()

        if os.stat(self._path).st_size != 0:
            with open(self._path, 'r') as f:
                db = jsonpickle.decode(f.read(), keys=True)
                self._rentals = {int(k): v for k, v in db['objects'].items()}
                self._counter = db['counter']
                self._movie_stats_days = db['stats_days']
                self._movie_stats_times = db['stats_times']


    def __del__(self):

        with open(self._path, 'w') as f:
            db = {
                'objects': self._rentals,
                'counter': self._counter,
                'stats_days': self._movie_stats_days,
                'stats_times': self._movie_stats_times
            }
            f.write(jsonpickle.encode(db))
