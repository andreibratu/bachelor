from typing import List
from datetime import datetime
from copy import copy

from abstract.observable import Observable

from entities.rental_entity import Rental
from entities.client_entity import Client

from repositories.rental_repository import RentalRepository
from repositories.client_repository import ClientRepository
from repositories.movie_repository import MovieRepository

from exceptions.conflict_error import ConflictError

from helper.helper import str_to_dt, print_list


class RentalController(Observable):
    """Object that implements Rental features."""


    def __init__(self, rental_repository: RentalRepository,
                 client_repository: ClientRepository,
                 movie_repository: MovieRepository):
        Observable.__init__(self)
        self.__rental_repository = rental_repository
        self.__client_repository = client_repository
        self.__movie_repository = movie_repository


    def rent(self, movie_id: str, client_id: str,
             rented_date: str, due_date: str):
        """Implement the movie rental behaviour.

        Raises:
            KeyError: No entity with given id exists.
            ConflictError: Client already has a rental on roll.
        """

        movie_id = int(movie_id)
        client_id = int(client_id)

        try:
            movie = self.__movie_repository.get(movie_id)

        except KeyError:
            raise KeyError('Invalid movie id: {}'.format(movie_id))

        try:
            client = self.__client_repository.get(client_id)

        except KeyError:
            raise KeyError('Invalid client id: {}'.format(client_id))


        current_rental = self.__client_rented_movies(client)

        if current_rental != []:
            raise ConflictError(
                "Client '{}' has not returned movie '{}'".format(
                    client.name,
                    current_rental[0].movie.title)
            )

        else:
            change_movie = {
                'undo': {
                    'ref': self.__movie_repository,
                    'o': movie,
                    'op': 'insert'},
                'redo': {
                    'ref': self.__movie_repository,
                    'o': movie_id,
                    'op': 'delete'},
            }

            self.__movie_repository.delete(movie_id)

            rental = Rental(
                movie=movie,
                client=client,
                rented_date=str_to_dt(rented_date),
                due_date=str_to_dt(due_date))
            id = self.__rental_repository.insert(rental)

            change_times = {
                'undo': {
                    'ref': self.__rental_repository,
                    'o': -1,
                    'op': 'update_stats_times'},
                'redo': {
                    'ref': self.__rental_repository,
                    'o': 1,
                    'op': 'update_stats_times'}
            }

            change_rental = {
                'undo': {
                    'ref': self.__rental_repository,
                    'o': id,
                    'op': 'delete'},
                'redo': {
                    'ref': self.__rental_repository,
                    'o': rental,
                    'op': 'insert'}
            }

            self.notify([change_movie, change_rental, change_times])


    def resolve(self, rental_id: str, return_date: str):
        """Return a movie."""

        rental_id = int(rental_id)

        r = self.__rental_repository.get(rental_id)

        rental_before_return_change = copy(r)
        r.returned_date = str_to_dt(return_date)
        rental_after_return_change = copy(r)

        self.__movie_repository.insert(r.movie)

        change_movie_return = {
            'undo': {
                'ref': self.__rental_repository,
                'o': r.movie.id,
                'op': 'delete'
            },
            'redo': {
                'ref': self.__rental_repository,
                'o': copy(r.movie),
                'op': 'insert'
            }
        }

        change_rental = {
            'undo': {
                'ref': self.__rental_repository,
                'o': rental_before_return_change,
                'op': 'insert'},
            'redo': {
                'ref': self.__rental_repository,
                'o': rental_after_return_change,
                'op': 'insert'}
        }

        self.__rental_repository.insert(r)

        days_rented = self.__rental_repository.calc_rental_days(r)

        change_days = {
            'undo': {
                'ref': self.__rental_repository,
                'o': -days_rented,
                'op': 'update_stats_days'},
            'redo': {
                'ref': self.__rental_repository,
                'o': days_rented,
                'op': 'update_stats_days'}
        }

        self.notify([change_rental, change_days, change_movie_return])


    def display(self):
        """Print all Rental entities."""

        print_list(self.__rental_repository.get_all())


    def stats(self, query: str):
        """Print statistics related to the Rental entities."""

        stats = []

        if query in ('days', 'times'):
            stats = {
                'days': self.__rental_repository.get_stats_days(),
                'times': self.__rental_repository.get_stats_times()
            }[query]

            stats.sort(key=lambda tup: tup[1], reverse=True)

        elif query in ('late', 'current'):
            stats = {
                'current': [
                    r for r in self.__rental_repository.get_all()
                    if r.returned_date is None],
                'late': [
                    r for r in self.__rental_repository.get_all()
                    if r.due_date < datetime.now()
                ]
            }[query]

            stats.sort(key=lambda r: r.due_date, reverse=True)

        else:
            raise ValueError('Invalid arg for stats command')

        print_list(stats)


    def __client_rented_movies(self, c: Client) -> List[Rental]:
        """Return list of movies currently rented by a client."""

        return [r for r in self.__rental_repository.get_all()
                if r.client.id == c.id and r.returned_date is None]
