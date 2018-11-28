from repositories.client_repository import ClientRepository
from repositories.movie_repository import MovieRepository
from repositories.rental_repository import RentalRepository

from controllers.client_controller import ClientController
from controllers.movie_controller import MovieController
from controllers.rental_controller import RentalController
from controllers.history_controller import HistoryController

from helper.helper import generate_movie_from_scraped_page, generate_name

from ui import CommandUI


client_repository = ClientRepository()
movie_repository = MovieRepository()
rental_repository = RentalRepository()
history_controller = HistoryController()

client_controller = ClientController(client_repository=client_repository)
movie_controller = MovieController(movie_repository=movie_repository)
rental_controller = RentalController(
    client_repository=client_repository,
    movie_repository=movie_repository,
    rental_repository=rental_repository
)

for n in generate_name():
    client_controller.create(name=n)

for (t, g, d) in generate_movie_from_scraped_page():
    movie_controller.create(title=t, genre=g, description=d)

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
