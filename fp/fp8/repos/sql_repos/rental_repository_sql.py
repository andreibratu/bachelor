from collections import Counter
from typing import List

from pony.orm import db_session, desc

from entities.rental_entity import Rental
from entities.client_entity import Client
from entities.movie_entity import Movie

from repos.repos.rental_repository import RentalRepository


class SqlRentalRepository(RentalRepository):
    """Object that manages Rental entities."""

    def __init__(self, db, client_manager, movie_manager, rental_manager):
        self._db = db
        self._client_manager = client_manager
        self._movie_manager = movie_manager
        self._rental_manager = rental_manager
        self._movie_stats_days = Counter()
        self._movie_stats_times = Counter()
        with db_session:
            try:
                self._counter = \
                    self._rental_manager.select().order_by(
                        desc(self._rental_manager.id))[:][0].id + 1
            except IndexError:
                self._counter = 1


    def insert(self, r: Rental) -> int:
        """Insert new Rental or update existing one."""

        with db_session:
            if not hasattr(r, 'id'):
                r.id = self._counter
                self._counter += 1
            r = self._rental_manager(
                id=self._counter,
                movie=self._movie_manager[r.movie.id],
                client=self._client_manager[r.client.id],
                rented_date=r.rented_date,
                due_date=r.due_date,
                returned_date=r.returned_date
            )
            self.update_stats_times(r.movie, 1)
            return r.id


    @db_session
    def update(self, r: Rental) -> int:
        """Update rental."""

        self._rental_manager[r.id].set(returned_date=r.returned_date)
        self.update_stats_days(r.movie, self.calc_rental_days(r))
        return r.id


    @db_session
    def get(self, id: int) -> Rental:
        """Get rental entity by id."""

        r = self._rental_manager[id]
        m = self._movie_manager[r.movie.id]
        c = self._client_manager[r.client.id]
        return Rental(
            id=r.id,
            movie=Movie(
                id=m.id,
                title=m.title,
                description=m.description,
                genre=m.genre),
            client=Client(
                id=c.id,
                name=c.name
            ),
            rented_date=r.rented_date,
            due_date=r.due_date,
            returned_date=r.returned_date
        )


    @db_session
    def get_all(self) -> List[Rental]:
        """Return all rental entities."""

        entities = self._rental_manager.select()[:]
        return [self.get(r.id) for r in entities]


    @db_session
    def delete(self, id: int):
        """Delete rental by id."""

        self._rental_manager[id].delete()
