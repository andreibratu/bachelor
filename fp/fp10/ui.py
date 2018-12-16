from game_master import GameMaster
from brain import AI
from os import system


class CommandUI:

    DEBUG = True

    def __init__(self, game_master: GameMaster, ai: AI = None):
        self._symbol_one = 'X'
        self._symbol_two = 'O'
        self._game_master = game_master
        self._ai = ai


    def new_game(self):
        system('clear')
        self.loop()


    def loop(self):

        def _play_again():
            try:
                while True:
                    again = input('Play again (Y/N)? ').upper()
                    if again in ('Y', 'N'):
                        break
                return {'Y': True, 'N': False}[again]

            except KeyboardInterrupt:
                raise KeyboardInterrupt


        while True:

            try:
                print('+++++++Connect-o-Four!+++++++')
                print(self._game_master.get_current_board())

                if self._game_master.check_draw():
                    print('Oh wow, is that a draw?! Yea..')
                    if _play_again():
                        self.new_game()
                    else:
                        break

                result = self._game_master.check_victory()

                if result is not None:
                    print('Player {} has won the game'.format(result))

                    if _play_again():
                        self._game_master.new_game()
                        self.new_game()
                    else:
                        break

                else:
                    p = self._game_master.get_current_player()
                    col = int(
                        input('Player {}, where will you move? '.format(p))
                    )
                    self._game_master.move(col - 1)

                system('clear')

            except KeyboardInterrupt:
                break

            except Exception as e:
                if self.DEBUG:
                    raise e
                else:
                    print(e)
                    continue


    def __del__(self):
        print('\nThanks for playing!')
