from typing import List, Tuple
from collections import Counter

from repos.abstract_repos.iterable_repository import IterableRepository

from entities.rental_entity import Rental
from entities.movie_entity import Movie


class RentalRepository(IterableRepository):
    """Object that manages Rental entities."""


    def __init__(self):
        IterableRepository.__init__(self)
        self._movie_stats_days = Counter()
        self._movie_stats_times = Counter()


    def insert(self, r: Rental) -> id:
        """Insert rental.

         If added for the first time, an id will be assigned.
         """

        super().insert(r)
        self.update_stats_times(r.movie, 1)

        return r.id


    def __setitem__(self, key, r: Rental) -> int:
        super().__setitem__(key, r)
        self.update_stats_days(r.movie, self.calc_rental_days(r))


    def get_stats_days(self) -> List[Tuple[Movie, int]]:
        """Return rental stats by number days rented."""

        return list(self._movie_stats_days.items())


    def get_stats_times(self) -> List[Tuple[Movie, int]]:
        """Return rental stats by number times rented."""

        return list(self._movie_stats_times.items())


    def calc_rental_days(self, r: Rental) -> int:
        """Calculate how many days a rental was made for."""

        return (r.returned_date - r.rented_date).days


    def update_stats_times(self, movie: Movie, times: int):
        """Method used to update times stats for a movie.

        A method approach was used in order to allow the undo/ redo observer
        to modify stats values.
        """

        self._movie_stats_times[movie] += times


    def update_stats_days(self, movie: Movie, days: int):
        """Method used to update times stats for a movie.

        A method approach was used in order to allow the undo/ redo observer
        to modify stats values.
        """

        self._movie_stats_days[movie] += days
