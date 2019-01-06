from table import Table


class Validator:
    """Object that validates user input."""

    def is_valid_column(self, c: int) -> bool:
        return 0 < c <= Table.COLS
