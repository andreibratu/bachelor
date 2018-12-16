from table import Table


class AI:
    """Class that implements the behaviour of the AI opponent."""


    def __init__(self, symbol: str, difficulty: int, table: Table):
        self._symbol = symbol
        self._difficulty = difficulty
        self._table = table


    def next_move(self) -> int:
        """Return the next possible move of the AI.

        The AI simulates all possible outcomes of playing a number of
        moves ahead, number given by the difficulty variable.

        Returns:
            The column of its move.
        """

        pass
