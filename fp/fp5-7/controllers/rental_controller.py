from typing import List
from datetime import datetime

from helper import str_to_dt, print_list

from entities.rental_entity import Rental
from entities.client_entity import Client

from repositories.rental_repository import RentalRepository
from repositories.client_repository import ClientRepository
from repositories.movie_repository import MovieRepository

from exceptions.conflict_error import ConflictError


class RentalController:
    """Object that implements Rental features."""


    def __init__(self, rental_repository: RentalRepository,
                 client_repository: ClientRepository,
                 movie_repository: MovieRepository):
        self.__rental_repository = rental_repository
        self.__client_repository = client_repository
        self.__movie_repository = movie_repository


    def rent(self, movie_id: str, client_id: str,
             rented_date: str, due_date: str):
        """Implement the movie rental behaviour.

        Raises:
            ValueError: Ids could not be parsed.
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
            self.__movie_repository.delete(movie_id)
            rental = Rental(
                movie=movie,
                client=client,
                rented_date=str_to_dt(rented_date),
                due_date=str_to_dt(due_date))

            self.__rental_repository.insert(rental)


    def resolve(self, rental_id: str, return_date: str):
        """Return a movie."""

        rental_id = int(rental_id)

        r = self.__rental_repository.get(rental_id)
        r.returned_date = str_to_dt(return_date)

        self.__rental_repository.insert(r)
        self.__movie_repository.insert(r.movie)


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
