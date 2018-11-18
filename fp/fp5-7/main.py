from repositories.client_repository import ClientRepository
from repositories.movie_repository import MovieRepository
from repositories.rental_repository import RentalRepository

from controllers.client_controller import ClientController
from controllers.movie_controller import MovieController
from controllers.rental_controller import RentalController
from controllers.history_controller import HistoryController

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

client_controller.create('Mary')
client_controller.create('John')
movie_controller.create(
    title="Pulp fiction",
    description="The lives of two mob hitmen, a boxer, a gangster's wife, \
                 and a pair of diner bandits intertwine in four tales of \
                 violence and redemption.",
    genre='Action')
movie_controller.create(
    title="Dirty Dancing",
    description="Spending the summer at a Catskills resort with her family, \
                 Frances 'Baby Houseman falls in love with the camp's dance \
                 instructor, Johnny Castle.",
    genre="Romantic"
)
movie_controller.create(
    title="Blade Runner",
    description="In the 21st century, a corporation develops human clones to \
                 be used as slaves in colonies outside the Earth, identified \
                 as replicants. In 2019, a former police officer is hired to \
                 hunt down a fugitive group of clones living undercover \
                 in Los Angeles.",
    genre="SciFi"
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
