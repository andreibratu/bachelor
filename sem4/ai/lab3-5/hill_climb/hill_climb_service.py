from itertools import product
from typing import Tuple, Optional, Generator

from domain.problem import heuristic
from domain.state import State, set_pos, build_random_state


def __hill_climb_expand(state: State) -> Generator[State, None, None]:
    """Explore neighbours of a given state. A neighbour is obtained by
    replacing a random (i, j) index with a new value from the domain."""
    n = len(state) // 2

    for i, j in product(range(n), repeat=2):
        for new_val in product(range(n), repeat=2):
            yield set_pos(state, i, j, new_val)


def hill_climb(n: int, runs: int) -> Tuple[Optional[State], int]:
    """Iteratively improve from a random state towards the optimum."""
    best_state, best_cost = build_random_state(n), float('inf')

    for i in range(runs):
        changed = False
        best_cost = heuristic(best_state)

        for next_state in __hill_climb_expand(best_state):
            next_cost = heuristic(next_state)
            if next_cost < best_cost:
                best_cost = next_cost
                best_state = next_state
                changed = True

        if not changed:
            # Got stuck
            best_state = build_random_state(n)

        if best_cost == 0:
            break

    return best_state, best_cost
