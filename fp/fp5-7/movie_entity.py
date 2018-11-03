class Movie:
    """Class that describes the Movie entity."""

    movie_id_counter = 0

    def __init__(self, title: str, description: str, genre: str):
        self.title = title
        self.description = description
        self.genre = genre
        self.movie_id = Movie.movie_id_counter
        Movie.movie_id_counter += 1

    def __str__(self):
        return '-'.join((str(self.movie_id), self.title))

    __repr__ = __str__
