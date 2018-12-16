from table import Table


class GameMaster:

    def __init__(self, one_symbol, two_symbol, table: Table):
        self._table = table
        self._turn = True
        self._player_symbols = {
            True: one_symbol,
            False: two_symbol
        }


    def check_draw(self):
        """Check if no more moves are possible."""

        return ' ' not in [cell for cell in self._table]


    def check_victory(self):
        """Check if a player has won the current game.

        Returns:
            The player that won, or None if nobody won yet.
        """

        def in_board(r, c):
            """Check if a given position is nout outside the board."""

            return 0 <= r < Table.ROWS and 0 <= c < Table.COLS

        dir = {
            0: (-1, 0), 1: (-1, 1), 2: (0, 1), 3: (1, 1),
            4: (1, 0), 5: (1, -1), 6: (0, 1), 7: (-1, -1)
        }

        win_symbol = None

        for i in range(self._table.ROWS):
            for j in range(self._table.COLS):
                if self._table[i][j] != ' ':
                    # For current cell check all 8 directions for 4-in-row
                    for d in dir.values():
                        delta_r, delta_c = d
                        r = i
                        c = j
                        flag = True
                        for _ in range(3):
                            rr = r + delta_r
                            cc = c + delta_c
                            if not in_board(rr, cc):
                                flag = False
                                break
                            if self._table[rr][cc] != self._table[r][c]:
                                flag = False
                                break
                            r, c = rr, cc
                        if flag:
                            win_symbol = self._table[i][j]

        if win_symbol in self._player_symbols.values():
            # Someone won the game, use the symbol dict to get the player
            if {v: k for k, v in self._player_symbols.items()}[win_symbol]:
                return 1
            else:
                return 2

        # Game is still going
        return None


    def move(self, column: int):
        """Move on the table according to the current player."""

        try:
            self._table.move(self._player_symbols[self._turn], column)
            self._turn = not self._turn
        except Exception as e:
            raise e


    def new_game(self):
        self._table.new_game()
        self._turn = True


    def get_current_player(self):
        return 1 if self._turn else 2


    def get_current_board(self):
        return str(self._table)
