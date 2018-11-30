from factory.repository_factory import RepositoryFactory
from factory.ui_factory import UIFactory

from controllers.client_controller import ClientController
from controllers.movie_controller import MovieController
from controllers.rental_controller import RentalController
from controllers.history_controller import HistoryController


repository_factory = RepositoryFactory()
ui_factory = UIFactory()

client_repository = repository_factory.build('client')
movie_repository = repository_factory.build('movie')
rental_repository = repository_factory.build('inmemory')

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
    history_controller=history_controller
)

ui.loop()
