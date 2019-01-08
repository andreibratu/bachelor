from os import system

from exceptions import InvalidMoveException, ColumnFullException
from game_master import GameMaster
from brain import AI


class CommandUI:

    DEBUG = True

    def __init__(self, game_master: GameMaster, ai: AI):
        self._symbol_one = 'X'
        self._symbol_two = 'O'
        self._game_master = game_master
        self._ai = ai


    def new_game(self):
        self.clear_screen()
        if self._ai is not None:
            self.ai_loop()
        else:
            self.human_loop()


    def clear_screen(self):
        system('clear')


    def _play_again(self) -> bool:
        """Check if the players want another game round."""

        try:
            while True:
                '''
                Take the upper equivalent of the use input and check if it
                is a Y or a not. Continue until it is.
                '''
                again = input('Play again (Y/N)? ').upper()
                if again in ('Y', 'N'):
                    break
            return {'Y': True, 'N': False}[again]

        except KeyboardInterrupt:
            raise KeyboardInterrupt


    def _print_board(self):
        print('+++++++Connect-o-Four!+++++++')
        print(self._game_master.get_board())


    def ai_loop(self):

        player_turn = True

        while True:
            self._print_board()

            if self._game_master.check_draw():
                print('Oh wow, is that a draw?! Yea..')
                if self._play_again():
                    self.new_game()
                else:
                    break

            result = self._game_master.check_victory()

            if result is not None:
                print(f'Player {result} has won the game')

                if self._play_again():
                    self._game_master.new_game()
                    self.new_game()
                else:
                    break

            if player_turn:
                while True:
                    try:
                        col = input(f'Player 1, where will you move? ')
                        col = int(col)
                        self._game_master.move(col - 1)
                        break

                    except ValueError:
                        continue

                    except ColumnFullException:
                        print(f'Column {col} is full!')
                        continue

                    except InvalidMoveException:
                        print('Please input a valid column!')
                        continue

            else:
                print('Thinking...')
                col = self._ai.next_move()
                self._game_master.move(col)

            player_turn = not player_turn

            self.clear_screen()


    def human_loop(self):

        while True:

            try:
                self._print_board()

                if self._game_master.check_draw():
                    print('Oh wow, is that a draw?! Yea..')
                    if self._play_again():
                        self.new_game()
                    else:
                        break

                result = self._game_master.check_victory()

                if result is not None:
                    print('Player {} has won the game'.format(result))

                    if self._play_again():
                        self._game_master.new_game()
                        self.new_game()
                    else:
                        break

                else:
                    p = self._game_master.get_current_player()
                    while True:
                        try:
                            col = input(f'Player {p}, where will you move? ')
                            col = int(col)
                            self._game_master.move(col - 1)
                            break

                        except ValueError:
                            continue

                        except ColumnFullException:
                            print(f'Column {col} if full!')
                            continue

                        except InvalidMoveException:
                            print('Please input a valid column!')
                            continue

                self.clear_screen()

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
