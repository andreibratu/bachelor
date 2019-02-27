from datetime import datetime
from entities.movie_entity import Movie
from entities.client_entity import Client
from helper.helper import pretty_date


class Rental:
    """Class that describes the Rental entity."""


    def __init__(self, movie: Movie, client: Client,
                 rented_date: datetime, due_date: datetime,
                 returned_date: datetime = None):
        self.movie = movie
        self.client = client

        self.rented_date = rented_date
        self.due_date = due_date
        self.returned_date = returned_date


    def __str__(self):
        returned_date = self.returned_date
        if self.returned_date is None:
            returned_date = 'To be returned'
        else:
            returned_date = pretty_date(self.returned_date)

        return ' -- '.join((
            str(self.id),
            str(self.movie.title),
            str(self.client.name),
            pretty_date(self.rented_date),
            pretty_date(self.due_date),
            returned_date)
        )


    __repr__ = __str__
