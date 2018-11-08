from ui import CommandUI
from controllers.client_controller import ClientController
from controllers.movie_controller import MovieController


client_controller = ClientController()
movie_controller = MovieController()


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


ui = CommandUI()
ui.loop()
