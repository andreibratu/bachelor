from itertools import product
from operator import itemgetter
from typing import Tuple, Optional

from aco.ant import Ant
from aco.graph import generate_aco_graph
from domain.problem import heuristic
from domain.state import State


def ant_colony_optimization(runs: int, ants_count: int, n: int, alpha: float,
                            beta: float, q: float, trace: int) -> Tuple[Optional[State], int]:
    """
    ACO based optimisation of the problem.
    :param runs: Attempts before stopping the search.
    :param ants_count: How many ants will be used.
    :param n: Degree of the problem.
    :param alpha: Importance of the pheromones in determining next state
    :param beta: Importance of how open is the next state
    :param q: Probability for an ant to choose best current option over a random one.
    :param trace: Constant - pheromone quantity to be left by an ant when going on an edge.
    :return: Best found state and its fitness.
    """
    graph_one = generate_aco_graph(n)
    graph_two = generate_aco_graph(n)
    ants_one = [Ant(n, alpha, beta, trace, q, graph_one) for _ in range(ants_count)]
    ants_two = [Ant(n, alpha, beta, trace, q, graph_two) for _ in range(ants_count)]

    idx = 0
    while idx < runs and (not ants_two[0].done() or not ants_one[0].done()):
        for ant in ants_one:
            ant.iterate()
        for ant in ants_two:
            ant.iterate()
        idx += 1

    assert ants_one[0].done()

    solutions_ones = [ant.path for ant in ants_one]
    solutions_twos = [ant.path for ant in ants_two]
    solutions = []

    for s1, s2 in product(solutions_ones, solutions_twos):
        sol = s1 + s2
        solutions.append((sol, heuristic(sol)))

    solutions.sort(key=itemgetter(1))
    return solutions[0]
