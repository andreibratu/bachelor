from typing import Dict
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
                 history_controller: HistoryController,
                 settings: Dict):
        self._client_controller = client_controller
        self._movie_controller = movie_controller
        self._rental_controller = rental_controller
        self._history_controller = history_controller
        self._settings = settings


    def loop(self):
        """The input loop of the application."""

        while True:
            try:
                # https://docs.python.org/2/library/shlex.html
                args = shlex.split(input('> '))

                if len(args) == 0:
                    continue

                if args[0] == 'exit':
                    print('Goodbye')
                    break

                try:
                    controller = {
                        'client': self._client_controller,
                        'movie': self._movie_controller,
                        'rental': self._rental_controller,
                        'history': self._history_controller,
                        'ZAWARUDO': self._history_controller
                    }[args[0]]

                    if len(args[2:]) > 0:
                        getattr(controller, args[1])(*args[2:])
                    else:
                        getattr(controller, args[1])()

                    continue

                except Exception as e:
                    if self._settings['debug']:
                        raise e
                    else:
                        print(e)
                        continue

            except (EOFError, KeyboardInterrupt):
                print('exit')
                print('Goodbye')
                break
