from copy import deepcopy
from functools import reduce
from itertools import product
from operator import itemgetter
from random import randint, choices, random
from typing import Generator, Optional

import numpy as np
from PyQt5.QtCore import pyqtSignal

from particle import Swarm
from problem import heuristic
from state import build_random_state, State, set_pos


def __hill_climb_expand(state: State) -> Generator[State, None, None]:
    n = len(state) // 2

    for i, j in product(range(n), range(n)):
        for new_val in product(range(n), range(n)):
            yield set_pos(state, i, j, new_val)


def hill_climb(n: int, runs: int) -> Optional[State]:
    best_state = build_random_state(n)
    for _ in range(runs):
        changed = False
        best_cost = heuristic(best_state)

        print(best_cost)

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
    return best_state


def __crossover(parent_one: State, parent_two: State) -> State:
    offspring = []

    for i in range(len(parent_one)):
        perm_one = list(parent_one[i])
        perm_two = list(parent_two[i])
        n = len(perm_one)

        i1 = randint(0, n // 2 - 1)
        i2 = i1 + n // 2

        perm = [0] * n
        for j in range(i1, i2):
            perm[j] = perm_one[j]

        index = i2
        for j in range(i2, n):
            if perm[j] == 0:
                while perm_two[index % n] in perm:
                    index += 1
                perm[j] = perm_two[index % n]
        for j in range(i1):
            if perm[j] == 0:
                while perm_two[index % n] in perm:
                    index += 1
                perm[j] = perm_two[index % n]

        offspring.append(perm)

    assert len(offspring) == len(parent_one)
    assert len(parent_one) == len(parent_two)
    assert len(offspring[0]) == len(parent_one[0])

    return offspring


def __apply_mutation(offspring: State) -> State:
    n = len(offspring) // 2
    offspring = deepcopy(offspring)

    pos_one = randint(0, n-1)
    perm_one = (np.random.permutation(n) + 1).tolist()

    pos_two = randint(n, 2*n-1)
    perm_two = (np.random.permutation(n) + 1).tolist()

    offspring[pos_one] = perm_one
    offspring[pos_two] = perm_two

    return offspring


def genetic_algorithm(n: int, pop_size: int, pop_replace: int, tournament_size: int,
                      runs: int, mutation_chance: float, logging: pyqtSignal) -> Optional[State]:
    assert pop_replace <= pop_size, 'Cannot replace more individuals than available!'
    assert mutation_chance < 1
    solution = None
    individuals = [build_random_state(n) for _ in range(pop_size)]

    func = lambda idv: heuristic(idv)
    better_fitness = lambda i1, i2: i1 if i1[1] < i2[1] else i2

    for i in range(runs):

        if solution is not None:
            break

        fitness = list(map(func, individuals))
        pool = list(zip(individuals, fitness))

        for j in range(pop_replace):
            selected = list(choices(pool, k=tournament_size*2))

            first_parent = list(reduce(better_fitness, selected[:tournament_size]))[0]
            second_parent = list(reduce(better_fitness, selected[tournament_size:]))[0]

            offspring = __crossover(first_parent, second_parent)
            if random() < mutation_chance:
                offspring = __apply_mutation(offspring)
            pool.append((offspring, func(offspring)))

        # Keep first `pop_size` most well-fitted individuals
        pool.sort(key=itemgetter(1))
        pool = pool[:pop_size]

        logging.emit(np.average([x[1] for x in pool]), np.median([x[1] for x in pool]), i)

        for ind, fitness in pool:
            if fitness == 0:
                solution = ind
                break

    print(solution)
    return solution


def particle_swarm_optimisation(n: int, runs: int, swarm_size: int, w: float,
                                c1: float, c2: float, logging: pyqtSignal) -> Optional[State]:
    swarm = Swarm(swarm_size, n, w, c1, c2)
    solution, solution_fitness = swarm.get_swarm_best()
    idx = 0
    while idx < runs and solution_fitness > 0:
        swarm.update()
        solution, solution_fitness = swarm.get_swarm_best()
        idx += 1

        fitness = swarm.get_swarm_fitness()
        logging.emit(np.average(fitness), np.median(fitness), idx)

    return solution if solution_fitness == 0 else None
