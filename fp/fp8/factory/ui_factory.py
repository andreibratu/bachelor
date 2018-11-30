import json

from ui.cli import CommandUI
from ui.gui import GraphicalUI


class UIFactory:

    def __init__(self):

        with open('settings.json', 'r') as f:

            object = json.loads(f.read())['ui']

            try:
                self._ui = {
                    'cli': CommandUI,
                    'gui': GraphicalUI
                }[object]

            except KeyError:
                raise ValueError('Invalid ui setting')

    def build(self, client_controller, movie_controller,
              rental_controller, history_controller):
        return self._ui(client_controller=client_controller,
                        movie_controller=movie_controller,
                        rental_controller=rental_controller,
                        history_controller=history_controller)
