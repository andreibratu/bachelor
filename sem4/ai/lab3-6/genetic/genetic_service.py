from copy import deepcopy
from functools import reduce
from operator import itemgetter
from random import randint, random, choices
from typing import Tuple, Optional

import numpy as np

from domain.problem import heuristic
from domain.state import State, build_random_state


def __crossover(parent_one: State, parent_two: State) -> State:
    """XO crossover operator applied over two States."""
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
    """Randomly mutate a row belonging to value_one permutations and value_two permutations."""
    n = len(offspring) // 2
    offspring = deepcopy(offspring)

    pos_one = randint(0, n-1)
    perm_one = (np.random.permutation(n) + 1).tolist()

    pos_two = randint(n, 2*n-1)
    perm_two = (np.random.permutation(n) + 1).tolist()

    offspring[pos_one] = perm_one
    offspring[pos_two] = perm_two

    return offspring


def genetic_algorithm(n: int, pop_size: int, pop_replace: int,
                      tournament_size: int, runs: int, mutation_chance: float) -> Tuple[Optional[State], int]:
    """Genetic approach using tournament selection, elitism and constant population."""
    assert pop_replace <= pop_size, 'Cannot replace more individuals than available!'
    assert mutation_chance < 1
    solution = None
    individuals = [build_random_state(n) for _ in range(pop_size)]

    func = lambda idv: heuristic(idv)
    better_fitness = lambda i1, i2: i1 if i1[1] < i2[1] else i2
    best_fitness = float('inf')

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

        # Select best individual seen until now - not restricted to this generation only
        for ind, fitness in pool:
            if fitness < best_fitness:
                best_fitness = fitness
                solution = ind

    return solution, best_fitness
