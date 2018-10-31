fromt entity.movie import Movie

class MovieDao:
    """Object that manages and accepts queries for the Movie entities."""

    movies = {}


    def create_movie(title: str, description: str, genre: str):
        """Create new movie."""

        m = Movie(title=title, description=description, genre=genre)
        MovieDao.movies[m.movie_id] = m


    def find_movie_id(id: int) -> Movie:
        """Return movie by id.

        Args:
            id (int): The id of the queried movie.
        Returns:
            The movie object.
        Raises:
            KeyError: No movie with given id exists.
        """

        try:
            return MovieDao.movies[id]
        except KeyError:
            raise KeyError('Invalid movie index {}'.format(id))


    def delete_movie_id(id: int):
        """Delete movie by id.

        Raises:
            KeyError: Given movie does not exist.
        """
        # TODO CHECK FOR UPDATE VS DELETE
        try:
            del MovieDao.movies[id]
        except KeyError:
            raise KeyError('Invalid client index {}'.format(id))
