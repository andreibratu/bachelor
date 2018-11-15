import shlex

from controllers.client_controller import ClientController
from controllers.movie_controller import MovieController
from controllers.rental_controller import RentalController


class CommandUI:
    """Object that handles user input."""


    def __init__(self, client_controller: ClientController,
                 movie_controller: MovieController,
                 rental_controller: RentalController):
        self.__client_controller = client_controller
        self.__movie_controller = movie_controller
        self.__rental_controller = rental_controller


    def loop(self):
        """The input loop of the application."""

        while True:
            try:
                # https://docs.python.org/2/library/shlex.html
                args = shlex.split(input('> '))

                if len(args) == 0:
                    continue

                try:
                    dao = {
                        'client': self.__client_controller,
                        'movie': self.__movie_controller,
                        'rental': self.__rental_controller
                    }[args[0]]

                    if len(args[2:]) > 0:
                        getattr(dao, args[1])(*args[2:])
                    else:
                        getattr(dao, args[1])()

                    continue

                except Exception as e:
                    print(e)
                    continue

            except (EOFError, KeyboardInterrupt):
                print('exit')
                print('Goodbye')
                break
