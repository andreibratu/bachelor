from client_dao import ClientDao
from movie_dao import MovieDao

class CommandUI:
    """Object that handles user input."""

    args = []
    client_dao = ClientDao()
    movie_dao = MovieDao()

    def loop(self):
        """The input loop of the application."""

        while True:
            try:
                CommandUI.args = input('> ').split(' ')

                args = CommandUI.args

                if len(args) == 0:
                    continue

                try:
                    dao = {
                        'client': CommandUI.client_dao,
                        'movie': CommandUI.movie_dao,
                    }[args[0]]

                    getattr(dao, args[1])(*args[2:])

                except Exception as e:
                    print(e)
                    continue

            except EOFError:
                print('\nGoodbye')
                break
