from repositories.rental_repository import RentalRepository
from repositories.client_repository import ClientRepository
from repositories.movie_repository import MovieRepository
from entities.rental_entity import Rental
from entities.client_entity import Client
from helper import str_to_dt

from typing import List

class RentalController:
    """Object that implements Rental features."""


    def __init__(self):
        self.rental_repository = RentalRepository()
        self.client_repository = ClientRepository()
        self.movie_repository = MovieRepository()


    def rent(self, movie_id: str, client_id: str,
               rented_date: str, due_date: str):
       """Implement the movie rental behaviour.

       Args:
            client_id (str): The id of the renting client.
            movie_id (str): The id of the rented movie.
            rent_date (datetime): The date at which the movie has been rented.
            due_date (datetime): The date at which the rental is due.
       """

       try:
          movie_id = int(movie_id)
          client_id = int(client_id)

       except ValueError as e:
          raise ValueError('Could not parse given ids')

       try:
           movie = self.movie_repository.get(movie_id)
           client = self.client_repository.get(client_id)

           rented = self.__rented_movies(client)

           if rented == []:
               rental = Rental(movie=movie,
                               client=client,
                               rented_date=str_to_dt(rented_date),
                               due_date=str_to_dt(due_date)
                               )

               self.rental_repository.insert(rental)

           else:
               raise ValueError(
                    "Client '{}' has not returned movie '{}'".format(
                    client.name,
                    rented[0].movie.title)
               )

       except Exception as e:
           raise e


    def resolve(self, r_id: str, r_date: str):
      """Marks a movie as being returned.

      Args:
           r_id (str): The rental to be resolved.
           r_date (str): The date at which the movie has been returned.
      """

      r = self.rental_repository.get(id)
      r.returned_date = str_to_dt(r_date)
      self.movie_repository.insert(r)


    def display(self):
        print(self.rental_repository.find_all())


    def __rented_movies(self, c: Client) -> List[Rental]:
       return [r for r in self.rental_repository.find_all() if r.client.id \
            == c.id and r.returned_date == None]
