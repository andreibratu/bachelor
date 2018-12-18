from texttable import Texttable
from itertools import chain

from observer.observable import Observable
from exceptions import ColumnFullException, IllegalMoveException


class Table(Observable):

    COLS = 7
    ROWS = 6

    def __init__(self):
        super().__init__()
        self._table = []
        for _ in range(self.ROWS):
            self._table.append([' ' for _ in range(self.COLS)])


    def __iter__(self):
        return chain.from_iterable(self._table)


    def __getitem__(self, key):
        return self._table[key]


    def __str__(self):
        to_print = Texttable()
        for row in self._table:
            to_print.add_row(row)
        to_print.add_row([i + 1 for i in range(self.COLS)])
        return str(to_print.draw())


    def move(self, symbol: str, column: int):
        """Make a move on the table.

        Args:
            symbol: The "disc" that is added to the table.
            column: The column on which the disc is added.
        Raises:
            ColumnFullException: The column is already filled.
            IllegalMoveException: The given column is not 0 <= col < self.COLS
        """

        first_occupied_row = None

        for i in range(self.ROWS):
            try:
                if self._table[i][column] != ' ':
                    first_occupied_row = i
                    break

            except IndexError:
                raise IllegalMoveException

        if first_occupied_row == 0:
            raise ColumnFullException

        if first_occupied_row is None:
            # Empty column
            first_occupied_row = self.ROWS


        self._table[first_occupied_row - 1][column] = symbol
        self.notify(self._table)  # Notify the AI of table update.


    def new_game(self):
        self._table = []
        for _ in range(self.ROWS):
            self._table.append([' ' for _ in range(self.COLS)])
