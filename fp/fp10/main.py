from ui import CommandUI
from table import Table
from game_master import GameMaster
from brain import AI
from validator import Validator


table = Table()
game_master = GameMaster(one_symbol='X', two_symbol='O', table=table)
validator = Validator()

opt = None
while True:
    opt = input('Would you like to play against the AI (Y/N)? ')
    opt = opt.upper()
    if opt in ('Y', 'N'):
        break
ai = {
    'Y': AI(symbol='O', difficulty=5, player_symbol='X', table=table),
    'N': None
}[opt]

ui = CommandUI(game_master=game_master, ai=ai, validator=validator)

ui.new_game()
