from collections import defaultdict
from copy import copy

from observer.observer import Observer


class AI(Observer):
    """Class that implements the behaviour of the AI opponent."""


    def __init__(self, symbol: str, difficulty: int):
        super.__init__()
        self._symbol = symbol
        self._difficulty = difficulty
        self._table = []

        self._strategy = defaultdict(int)
        for k, v in [
            (2222, float('inf')),
            (2220, 1000),
            (2200, 100),
            (2000, 10),
            (0000, 0),
            (1000, -10),
            (1100, -100),
            (1110, -1000),
            (1111, float('-inf'))
        ]:
            self._strategy[k] = v


    def update(self, message):
        self._table = message


    def _minmax(table, ai_turn):
        """Implementation of the minmax algorithm.

        The AI simulates all possible outcomes of playing a number of
        moves ahead, number given by the difficulty variable.

        Args:
            table (List[List[int]]): The game table.
            ai_turn (bool): Wheter it is AI's turn to move.

        Returns:
            The best move the AI can make as column.
        """


    def next_move(self) -> int:
        """Return the next possible move of the AI.

        The method is a public wrapper around the minmax algorithm.

        Returns:
            The column of its move.
        """

        return self._minmax(copy(self._table), True)
