from typing import Tuple, Optional

from domain.state import State
from pso.swarm import Swarm


def particle_swarm_optimisation(n: int, runs: int, swarm_size: int,
                                w: float, c1: float, c2: float) -> Tuple[Optional[State], int]:
    """PSO approach. Each particle orients itself using its position, its best known position and swarm's best."""
    swarm = Swarm(swarm_size, n, w, c1, c2)
    solution, solution_fitness = swarm.get_swarm_best()
    idx = 0

    while idx < runs and solution_fitness > 0:
        swarm.update()
        solution, solution_fitness = swarm.get_swarm_best()
        idx += 1

    return solution, solution_fitness
