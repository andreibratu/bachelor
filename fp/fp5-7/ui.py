import shlex

from controllers.client_controller import ClientController
from controllers.movie_controller import MovieController
from controllers.rental_controller import RentalController
from controllers.history_controller import HistoryController


class CommandUI:
    """Object that handles user input."""


    def __init__(self, client_controller: ClientController,
                 movie_controller: MovieController,
                 rental_controller: RentalController,
                 history_controller: HistoryController):
        self.__client_controller = client_controller
        self.__movie_controller = movie_controller
        self.__rental_controller = rental_controller
        self.__history_controller = history_controller


    def loop(self):
        """The input loop of the application."""

        while True:
            try:
                # https://docs.python.org/2/library/shlex.html
                args = shlex.split(input('> '))

                if len(args) == 0:
                    continue

                try:
                    controller = {
                        'client': self.__client_controller,
                        'movie': self.__movie_controller,
                        'rental': self.__rental_controller,
                        'history': self.__history_controller,
                    }[args[0]]

                    if len(args[2:]) > 0:
                        getattr(controller, args[1])(*args[2:])
                    else:
                        getattr(controller, args[1])()

                    continue

                except Exception as e:
                    print(e)
                    continue

            except (EOFError, KeyboardInterrupt):
                print('exit')
                print('Goodbye')
                break
