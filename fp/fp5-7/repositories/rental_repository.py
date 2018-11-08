from entities.rental_entity import Rental
from entities.client_entity import Client
from helper import str_to_dt, pretty_date
from typing import List


class RentalRepository:
    """Object that manages Rental entities."""


    __rentals = {}
    __count = 0


    def insert(self, r: Rental):
        """Inserts a Rental object into the DAO."""

        if not hasattr(r, 'id'):
            r.id = RentalRepository.__count
            RentalRepository.__count += 1

        RentalRepository.__rentals[r.id] = r


    def get(id: int):
        """"Return Rental entity with given id."""

        return RentalRepository.__rentals[id]


    def find_all(self) -> List[Rental]:
        return list(RentalRepository.__rentals.values())
