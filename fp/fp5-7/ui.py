from controllers.client_controller import ClientController
from controllers.movie_controller import MovieController
from controllers.rental_controller import RentalController
import shlex

class CommandUI:
    """Object that handles user input."""

    args = []
    client_controller = ClientController()
    movie_controller = MovieController()
    rental_controller = RentalController()


    def loop(self):
        """The input loop of the application."""

        while True:
            try:
                # https://docs.python.org/2/library/shlex.html
                CommandUI.args = shlex.split(input('> '))

                args = CommandUI.args

                if len(args) == 0:
                    continue

                try:
                    dao = {
                        'client': CommandUI.client_controller,
                        'movie': CommandUI.movie_controller,
                        'rental': CommandUI.rental_controller
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
