from typing import List, Tuple
from collections import Counter

from entities.rental_entity import Rental
from entities.movie_entity import Movie


class RentalRepository:
    """Object that manages Rental entities."""


    def __init__(self):
        self.__rentals = {}
        self.__movie_stats_days = Counter()
        self.__movie_stats_times = Counter()
        self.__count = 0


    def insert(self, r: Rental):
        """Inserts a Rental object into the DAO."""

        if not hasattr(r, 'id'):
            r.id = self.__count
            self.__count += 1
            self.__movie_stats_times[r.movie] += 1

        else:
            self.__movie_stats_days[r.movie] += \
                self.__calc_rental_days(r)

        self.__rentals[r.id] = r


    def get(self, id: int):
        """"Return Rental entity with given id."""

        return self.__rentals[id]


    def get_all(self) -> List[Rental]:
        """Return all Rental entities."""

        return list(self.__rentals.values())


    def get_stats_days(self) -> List[Tuple[Movie, int]]:
        """Return rental stats by number days rented."""

        return list(self.__movie_stats_days.items())


    def get_stats_times(self) -> List[Tuple[Movie, int]]:
        """Return rental stats by number times rented."""

        return list(self.__movie_stats_times.items())


    def __calc_rental_days(self, r: Rental) -> int:
        """Calculate how many days a rental was made for."""

        assert r.returned_date is not None

        return (r.returned_date - r.rented_date).days
