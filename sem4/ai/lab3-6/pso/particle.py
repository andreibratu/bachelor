from random import random
from typing import Tuple, List

import numpy as np

from domain.problem import heuristic
from domain.state import build_random_state, State


def _get_fitness(position) -> int:
    as_state = position.tolist()
    return heuristic(as_state)


class Particle:

    def __init__(self, n: int, w: float, c1: float, c2: float):
        assert w + c1 + c2 == 1
        self._n = n
        self._w = w
        self._c1 = c1
        self._c2 = c2
        # Init with random positions and velocities
        self._velocity = np.array(build_random_state(n))
        self._position = np.array(build_random_state(n))
        self._personal_best = self._position
        self._swarm_best = None

    def get_personal_best(self):
        """Return best position identified by individual."""
        return self._personal_best

    def set_swarm_best(self, position: np.ndarray):
        """Set the best position identified by the swarm."""
        self._swarm_best = position

    def update(self):
        """
        Update position and velocity of the individual.
        :return:
        """
        global _get_fitness
        assert self._swarm_best is not None
        r1, r2 = random(), random()
        new_velocity = \
            self._w * self._velocity + \
            self._c1 * r1 * (self._personal_best - self._position) + \
            self._c2 * r2 * (self._swarm_best - self._position)
        self._position = self._position + new_velocity
        self._velocity = new_velocity

        if _get_fitness(self._position) > _get_fitness(self._personal_best):
            self._personal_best = self._position

    @property
    def position(self):
        return self._position
