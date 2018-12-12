from repos.abstract_repos.json_repository import JsonRepository
from repos.repos.rental_repository import RentalRepository


class JsonRentalRepository(RentalRepository, JsonRepository):

    def __init__(self):
        JsonRepository.__init__(
            self,
            path='storage/rentals.json',
            extra_args=['_movie_stats_days', '_movie_stats_times']
        )
        RentalRepository.__init__(self)
