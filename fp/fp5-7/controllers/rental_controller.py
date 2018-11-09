from typing import List
from datetime import datetime

from helper import str_to_dt

from entities.rental_entity import Rental
from entities.client_entity import Client

from repositories.rental_repository import RentalRepository
from repositories.client_repository import ClientRepository
from repositories.movie_repository import MovieRepository

from exceptions.conflict_error import ConflictError
from exceptions.arguement_error import ArguementError


class RentalController:
    """Object that implements Rental features."""


    def __init__(self):
        self.rental_repository = RentalRepository()
        self.client_repository = ClientRepository()
        self.movie_repository = MovieRepository()


    def rent(self, movie_id: str, client_id: str,
               rented_date: str, due_date: str):
    """Implement the movie rental behaviour.

    Raises:
        ValueError: Ids could not be parsed.
        KeyError: No entity with given id exists.
        ConflictError: Client already has a rental on roll.
    """

       try:
          movie_id = int(movie_id)
          client_id = int(client_id)

       except ValueError:
          raise ValueError('Could not parse given ids')

       try:
           movie = self.movie_repository.get(movie_id)

       except KeyError:
           raise KeyError('Invalid movie id: {}'.format(movie_id))

       try:
           client = self.client_repository.get(client_id)

       except KeyError:
           raise KeyError('Invalid client id: {}'.format(client_id))

       if self.__client_rented_movies(client) == []:
           self.movie_repository.delete(movie_id)
           rental = Rental(
                movie=movie,
                client=client,
                rented_date=str_to_dt(rented_date),
                due_date=str_to_dt(due_date)
           )

           self.rental_repository.insert(rental)

       else:
           raise ConflictError(
                "Client '{}' has not returned movie '{}'".format(
                client.name,
                rented[0].movie.title)
           )


    def resolve(self, rental_id: str, return_date: str):
      """Return a movie."""

      rental_id = int(rental_id)

      r = self.rental_repository.get(rental_id)
      r.returned_date = str_to_dt(return_date)

      self.rental_repository.insert(r)
      self.movie_repository.insert(r.movie)


    def display(self):
        """Print all Rental entities."""

        print_list(self.rental_repository.get_all())


    def stats(self, query: str):
        """Print statistics related to the Rental entities."""

        stats = []

        if query in ('days', 'times'):
            stats = {
                'days': self.rental_repository.get_stats_days(),
                'times': self.rental_repository.get_stats_times()
            }[query]

            stats.sort(key=lambda tup: tup[1], reverse=True)

        elif query in ('late', 'current'):
            stats = {
                'current': [
                    r for r in self.rental_repository.get_all()
                    if r.returned_date == None],
                'late': [
                    r for r in self.rental_repository.get_all()
                    if r.due_date < datetime.now()
                ]
            }[query]

            stats.sort(key=lambda r: r.due_date, reverse=True)

        else:
            raise ValueError('Invalid arg for stats command')

        print_list(stats)


    def __client_rented_movies(self, c: Client) -> List[Rental]:
        """Return list of movies currently rented by a client."""

        return [r for r in self.rental_repository.get_all() if r.client.id \
            == c.id and r.returned_date == None]
