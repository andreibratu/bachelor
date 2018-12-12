from entities.file_manager import FileManager

from helper.helper import build_db, get_settings

from factory.repository_factory import RepositoryFactory
from factory.ui_factory import UIFactory

from controllers.client_controller import ClientController
from controllers.movie_controller import MovieController
from controllers.history_controller import HistoryController
from controllers.rental_controller import RentalController


settings = get_settings()

client_args, movie_args, rental_args = (None, None, None)

if settings['repository'] == 'sql':
    db, client_manager, movie_manager, rental_manager = build_db()
    client_args = {'db': db, 'client_manager': client_manager}
    movie_args = {'db': db, 'movie_manager': movie_manager}
    rental_args = {
        'db': db,
        'client_manager': client_manager,
        'movie_manager': movie_manager,
        'rental_manager': rental_manager
    }

if settings['repository'] in ('json', 'pickle'):
    client_args, movie_args, rental_args = tuple(
        {'file_manager': FileManager(type=settings['repository'])}
        for _ in range(3)
    )

repository_factory = RepositoryFactory()
ui_factory = UIFactory()

client_repository = repository_factory.build('client', client_args)
movie_repository = repository_factory.build('movie', movie_args)
rental_repository = repository_factory.build('rental', rental_args)

history_controller = HistoryController()
client_controller = ClientController(client_repository=client_repository)
movie_controller = MovieController(movie_repository=movie_repository)
rental_controller = RentalController(
    client_repository=client_repository,
    movie_repository=movie_repository,
    rental_repository=rental_repository
)

movie_controller.subscribe(history_controller)
client_controller.subscribe(history_controller)
rental_controller.subscribe(history_controller)

ui = ui_factory.build(
    client_controller=client_controller,
    movie_controller=movie_controller,
    rental_controller=rental_controller,
    history_controller=history_controller,
    settings=settings
)

ui.loop()
