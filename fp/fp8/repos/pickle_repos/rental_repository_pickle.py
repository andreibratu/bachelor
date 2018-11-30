from repos.repos.rental_repository import RentalRepository
import pickle
import os


class PickleRentalRepository(RentalRepository):

    def __init__(self):

        self._path = 'storage/rentals.txt'

        super().__init__()

        if os.stat(self._path).st_size != 0:
            with open(self._path, 'rb') as f:
                db = pickle.load(f)
                self._rentals = db['objects']
                self._counter = db['counter']
                self._movie_stats_days = db['stats_days']
                self._movie_stats_times = db['stats_times']


    def __del__(self):

        with open(self._path, 'wb') as f:
            db = {
                'objects': self._rentals,
                'counter': self._counter,
                'stats_days': self._movie_stats_days,
                'stats_times': self._movie_stats_times
            }
            pickle.dump(db, f)
