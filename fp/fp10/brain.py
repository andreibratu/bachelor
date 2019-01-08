from typing import List
from copy import deepcopy

from table import Table
from exceptions import ColumnFullException


class AI:
    """Class that implements the behaviour of the AI opponent."""


    def __init__(self, symbol: str, difficulty: int,
                 player_symbol: str, table: Table):
        self._ai_symbol = symbol
        self._player_symbol = player_symbol
        self._difficulty = difficulty
        self._table = table


    def _calculate_score(self, table: List[List[str]]):
        """Calculate the value of a given board, as defined in self._strategy.

        Args:
            table (List[List[str]]): A connect-4 table
        Returns:
            The value of the table.
        """

        def in_table(rr, cc):
            return 0 <= rr < Table.ROWS and 0 <= cc < Table.COLS

        # The eight possible directions on the table
        dir = {
            0: (-1, 0), 1: (-1, 1), 2: (0, 1), 3: (1, 1),
            4: (1, 0), 5: (1, -1), 6: (0, 1), 7: (-1, -1)
        }

        found_winning = False

        for r in range(Table.ROWS):
            for c in range(Table.COLS):
                for d in range(8):
                    rr = r
                    cc = c
                    build = ''

                    for i in range(4):
                        if in_table(rr, cc):
                            build += table[rr][cc]
                            rr += dir[d][0]
                            cc += dir[d][1]
                        else:
                            break

                    if build == self._ai_symbol * 4:
                        found_winning = True
                        break

                    if build == self._player_symbol * 4:
                        return -1

        if found_winning:
            return 1

        return 0


    def _minimax(self, table: Table, moves: int, ai_turn: bool):
        """Implementation of the minimax algorithm.

        The AI simulates all possible outcomes of playing a number of
        moves ahead, number given by the difficulty variable.

        Args:
            table (Table): The game table.
            moves (int): How many times minimax should recurse.
            ai_turn (bool): Wheter it is AI's turn to move.

        Returns:
            A tuple containing the best column the AI can move on and
            the associated best score.
        """

        if moves == 0:
            return (self._calculate_score(table._table), None)

        best = float('-inf') if ai_turn else float('inf')
        symbol = self._ai_symbol if ai_turn else self._player_symbol
        best_move = None

        for col in range(Table.COLS):

            try:
                copy_table = deepcopy(table)
                copy_table.move(symbol, col)
                assert self._table._table != copy_table._table

                score = self._minimax(
                    table=copy_table,
                    ai_turn=not ai_turn,
                    moves=moves - 1)[0]

                if ai_turn:
                    if score > best:
                        best = score
                        best_move = col
                else:
                    if score < best:
                        best = score
                        best_move = col

            except ColumnFullException:
                continue

        return (best, best_move)


    def next_move(self) -> int:
        """Return the next possible move of the AI.

        The method is a public wrapper around the minimax algorithm.

        Returns:
            The column of its move.
        """

        t = deepcopy(self._table)
        col = self._minimax(
            table=deepcopy(self._table),
            ai_turn=True,
            moves=self._difficulty
        )[1]
        assert t._table == self._table._table
        return col
