from datetime import datetime

class Rental:
    """Class that describes the Rental entity."""

    rental_id_counter = 0


    def __init__(self, movie_id: int, client_id: int,
                 rented_date: datetime, due_date: datetime,
                 returned_date: datetime=None, client_name: str,
                 movie_name: str):
         self.movie_id = movie_id
         self.movie_name = movie_name

         self.client_id = client_id
         self.client_name = client_name

         self.rented_date = rented_date
         self.due_date = due_date
         self.returned_date = returned_date

         self.rental_id = Rental.rental_id_counter
         Rental.rental_id_counter += 1


     def __str__(self):
         # TODO
