from datetime import datetime
from copy import copy

from observer.observable import Observable

from entities.rental_entity import Rental
from entities.client_entity import Client

from repos.repos.rental_repository import RentalRepository
from repos.repos.client_repository import ClientRepository
from repos.repos.movie_repository import MovieRepository

from exceptions.conflict_error import ConflictError

from helper.helper import str_to_dt, print_list


class RentalController(Observable):
    """Object that implements Rental features."""


    def __init__(self, rental_repository: RentalRepository,
                 client_repository: ClientRepository,
                 movie_repository: MovieRepository):
        Observable.__init__(self)
        self._rental_repository = rental_repository
        self._client_repository = client_repository
        self._movie_repository = movie_repository


    def rent(self, movie_id: str, client_id: str,
             rented_date: str, due_date: str):
        """Implement the movie rental behaviour.

        Raises:
            KeyError: No entity with given id exists.
            ConflictError: Client already has a rental or movie already rented.
        """

        movie_id = int(movie_id)
        client_id = int(client_id)

        try:
            movie = self._movie_repository.get(movie_id)

        except KeyError:
            raise KeyError('Invalid movie id: {}'.format(movie_id))

        try:
            client = self._client_repository.get(client_id)

        except KeyError:
            raise KeyError('Invalid client id: {}'.format(client_id))


        # Check if movie is not already rented
        for c in self._client_repository.get_all():
            curr_rental = self._client_curr_rental(c)
            if curr_rental is not None and movie.id == curr_rental.movie.id:
                raise ConflictError(
                    "Movie '{}' is already rented by '{}'".format(
                        movie.title,
                        c.name
                    )
                )

        # Check if client has no rented movies
        current_rental = self._client_curr_rental(client)
        if curr_rental is not None:
            raise ConflictError(
                "Client '{}' has not returned movie '{}'".format(
                    client.name,
                    current_rental.movie.title)
            )

        rental = Rental(
            movie=movie,
            client=client,
            rented_date=str_to_dt(rented_date),
            due_date=str_to_dt(due_date))
        id = self._rental_repository.insert(rental)

        change_times = {
            'undo': {
                'ref': self._rental_repository.update_stats_times,
                'o': [movie, -1],
            },
            'redo': {
                'ref': self._rental_repository.update_stats_times,
                'o': [movie, 1],
            }
        }

        change_rental = {
            'undo': {
                'ref': self._rental_repository.delete,
                'o': [id]
            },
            'redo': {
                'ref': self._rental_repository.insert,
                'o': [rental],
            }
        }

        self.notify([change_rental, change_times])


    def resolve(self, rental_id: str, return_date: str):
        """Return a movie."""

        rental_id = int(rental_id)

        r = self._rental_repository.get(rental_id)

        rental_before_return_change = copy(r)
        r.returned_date = str_to_dt(return_date)
        rental_after_return_change = copy(r)

        change_rental = {
            'undo': {
                'ref': self._rental_repository.update,
                'o': [rental_before_return_change],
            },
            'redo': {
                'ref': self._rental_repository.update,
                'o': [rental_after_return_change],
            }
        }

        self._rental_repository.update(r)

        days_rented = self._rental_repository.calc_rental_days(r)

        change_days = {
            'undo': {
                'ref': self._rental_repository.update_stats_days,
                'o': [copy(r.movie), -days_rented],
            },
            'redo': {
                'ref': self._rental_repository.update_stats_days,
                'o': [copy(r.movie), days_rented],
            }
        }

        self.notify([change_rental, change_days])


    def display(self):
        """Print all Rental entities."""

        print_list(self._rental_repository.get_all())


    def stats(self, query: str):
        """Print statistics related to the Rental entities."""

        stats = []

        if query in ('days', 'times'):
            stats = {
                'days': self._rental_repository.get_stats_days(),
                'times': self._rental_repository.get_stats_times()
            }[query]

            stats.sort(key=lambda tup: tup[1], reverse=True)

        elif query in ('late', 'current'):
            stats = {
                'current': [
                    r for r in self._rental_repository.get_all()
                    if r.returned_date is None
                ],
                'late': [
                    r for r in self._rental_repository.get_all()
                    if r.due_date < datetime.now()
                ]
            }[query]

            stats.sort(key=lambda r: r.due_date, reverse=True)

        else:
            raise ValueError('Invalid arg for stats command')

        print_list(stats)


    def _client_curr_rental(self, c: Client) -> Rental:
        """Return the current rental of a client."""

        try:
            return [r for r in self._rental_repository.get_all()
                    if r.client.id == c.id and r.returned_date is None][0]
        except IndexError:
            return None
