from table import Table


class GameMaster:

    def __init__(self, one_symbol: str, two_symbol: str, table: Table):
        self._table = table
        self._is_first_player_turn = True
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
            1 or 2 if a player has won, or None if the game is still going.
        """

        def in_board(r, c):
            """Check if given position is inside the board."""

            return 0 <= r < Table.ROWS and 0 <= c < Table.COLS

        directions = {
            0: (-1, 0), 1: (-1, 1), 2: (0, 1), 3: (1, 1),
            4: (1, 0), 5: (1, -1), 6: (0, 1), 7: (-1, -1)
        }

        for i in range(self._table.ROWS):
            for j in range(self._table.COLS):
                if self._table[i][j] != ' ':
                    # For current cell check all 8 directions for 4-in-row
                    for direction in directions.values():
                        delta_r, delta_c = direction
                        r = i
                        c = j
                        four_in_row = True

                        for _ in range(3):
                            rr = r + delta_r
                            cc = c + delta_c

                            if not in_board(rr, cc):
                                four_in_row = False
                                break

                            if self._table[rr][cc] != self._table[r][c]:
                                four_in_row = False
                                break

                            r, c = rr, cc

                        if four_in_row:
                            # Winning move must have been made by last player
                            return {
                                1: 2,
                                2: 1
                            }[self.get_current_player()]

        # Could not find four in a row, game is still going
        return None


    def move(self, column: int):
        """Move on the table according to player turn."""

        symbol = self._player_symbols[self._is_first_player_turn]

        try:
            self._table.move(symbol, column)
            self._is_first_player_turn = not self._is_first_player_turn

        except Exception as e:
            raise e


    def new_game(self):
        """Reset the game session."""

        self._table.new_game()
        self._is_first_player_turn = True


    def get_current_player(self):
        return 1 if self._is_first_player_turn else 2


    def get_board(self):
        return str(self._table)
