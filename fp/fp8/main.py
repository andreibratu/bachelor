from repos.json_repos.client_repository_json import JsonClientRepository
from repos.json_repos.movie_repository_json import JsonMovieRepository
from repos.json_repos.rental_repository_json import JsonRentalRepository

from controllers.client_controller import ClientController
from controllers.movie_controller import MovieController
from controllers.rental_controller import RentalController
from controllers.history_controller import HistoryController

from ui import CommandUI


client_repository = JsonClientRepository()
movie_repository = JsonMovieRepository()
rental_repository = JsonRentalRepository()

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

ui = CommandUI(
    client_controller=client_controller,
    movie_controller=movie_controller,
    rental_controller=rental_controller,
    history_controller=history_controller
)
ui.loop()
