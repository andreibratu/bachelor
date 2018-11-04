from datetime import datetime
from movie_entity import movie

class Rental:
    """Class that describes the Rental entity."""

    rental_id_counter = 0


    def __init__(self, movie: Movie, rented_date: datetime,
                 due_date: datetime, returned_date: datetime=None):
         self.movie = movie

         self.rented_date = rented_date
         self.due_date = due_date
         self.returned_date = returned_date

         self.rental_id = Rental.rental_id_counter
         Rental.rental_id_counter += 1


     def __str__(self):
         return '-'.join((str(movie), str(rented_date), str(due_date)))
