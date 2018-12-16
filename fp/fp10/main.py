from ui import CommandUI
from table import Table
from game_master import GameMaster
from brain import AI


table = Table()
game_master = GameMaster(one_symbol='X', two_symbol='O', table=table)
ai = AI(symbol='O', difficulty=2, table=table)
ui = CommandUI(game_master=game_master)

ui.new_game()
