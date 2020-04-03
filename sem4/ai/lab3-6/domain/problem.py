from domain.state import State, get_row, get_column


def heuristic(state: State) -> int:
    n, cost = len(state) // 2, 0

    # Check columns for duplicates
    for col_idx in range(n):
        col_one, col_two = get_column(state, col_idx)
        cost += len(col_one) - len(set(col_one))
        cost += len(col_two) - len(set(col_two))

    # Check that row-wise elements are not formed from identical values i.e. (2,3) ok, (1,1) not ok
    for row_idx in range(n):
        row_one, row_two = get_row(state, row_idx)
        # Zip will take two equal length lists and form tuples from their elements
        # [1, 2, 3] [4, 5, 6] -> [(1,4), (2,5), (3,6)]
        values = list(zip(row_one, row_two))
        cost += len(values) - len(set(values))

    return cost
