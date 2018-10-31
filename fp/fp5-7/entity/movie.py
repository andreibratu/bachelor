class Movie:
    """Class that describes the Movie entity."""

    movie_id_counter = 0

    def __self__(self, title: str, description: str, genre: str):
        self.title = title
        self.description = description
        self.genre = genre
        self.movie_id = Movie.movie_id_counter
        Movie.movie_id_count += 1

    def __str__(self):
        return self.title

    __repr__ = __str__
