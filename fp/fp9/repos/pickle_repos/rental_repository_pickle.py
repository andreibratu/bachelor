from repos.abstract_repos.pickle_repository import PickleRepository
from repos.repos.rental_repository import RentalRepository


class PickleRentalRepository(RentalRepository, PickleRepository):

    def __init__(self):
        PickleRepository.__init__(
            self,
            path='storage/rentals.txt',
            extra_args=['_movie_stats_days', '_movie_stats_times']
        )
        RentalRepository.__init__(self)
