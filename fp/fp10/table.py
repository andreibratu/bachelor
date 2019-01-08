from typing import List, Iterable

from texttable import Texttable
from itertools import chain

from exceptions import ColumnFullException, InvalidMoveException


class Table:

    COLS = 7
    ROWS = 6

    def __init__(self):
        self._table = []
        for _ in range(self.ROWS):
            self._table.append([' ' for _ in range(self.COLS)])


    def __iter__(self) -> Iterable:
        """Return an iterable that iterates the entire game matrix."""

        return chain.from_iterable(self._table)


    def __getitem__(self, key) -> List[int]:
        """Return the n-th row of the game table."""

        return self._table[key]


    def __str__(self):
        """Return visual representation of the game table."""

        to_print = Texttable()
        for row in self._table:
            to_print.add_row(row)
        to_print.add_row([i + 1 for i in range(self.COLS)])
        return str(to_print.draw())


    def is_column_available(self, column: int):
        """Return if a move can be made on given column.

        Args:
            c (int): The column
        Returns:
            A tuple with a bool representing wether a move can be made.
        """

        for i in range(Table.ROWS):
            if self._table[i][column] == ' ':
                return True

        return False


    def move(self, symbol: str, column: int):
        """Make a move on the table.

        Args:
            symbol: The "disc" that is added to the table.
            column: The column on which the disc is added.
        Raises:
            ColumnFullException: The column is already filled.
            IllegalMoveException: The given column is not 0 <= col < self.COLS
        """

        if not 0 <= column < Table.COLS:
            raise InvalidMoveException

        if not self.is_column_available(column):
            raise ColumnFullException

        for i in reversed(range(self.ROWS)):
            # Find the first move row of the column that is not occupied.
            if self._table[i][column] == ' ':
                self._table[i][column] = symbol
                break


    def new_game(self):
        """Clear the game board."""

        self._table = [
            [' ' for _ in range(Table.COLS)]
            for _ in range(Table.ROWS)
        ]
