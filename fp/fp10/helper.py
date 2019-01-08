from table import Table


def in_table(rr, cc):
    """Check if given cell is in the game board or outside.

    Args:
        rr (int): The row of the cell;
        cc (int): The column of the cell.
    """

    return 0 <= rr < Table.ROWS and 0 <= cc < Table.COLS
