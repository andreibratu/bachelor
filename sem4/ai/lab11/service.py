from functools import reduce
from math import floor
from random import randint, random, seed
from typing import List

from numpy.random import choice

from chromosome import Chromosome
from logger import Logger

DEPTH_MAX = 7
terminals = ['-165', '-150', '-135', '-120', '-105', '-90', '-75',
             '-60', '-45', '-30', '-15', '0', '15', '30', '45', '60', '75',
             '90', '105', '120', '135', '150', '165'] \
            # + [f'C{i}' for i in range(10)]
functions = ['+', '-', '*', 'sin', 'cos']
unary_functions = ['sin', 'cos']
binary_functions = ['+', '-', '*']
constants = []
classes = {
    'Slight-Left-Turn':     0,
    'Move-Forward':         1,
    'Slight-Right-Turn':    2,
    'Sharp-Right-Turn':     3
}


def crossover(parent_one: Chromosome, parent_two: Chromosome) -> Chromosome:
    """
    Replace a subtree from the first parent with one from the second parent
    :param parent_one: First parent, acting as host
    :param parent_two: Second parent, donates a subtree
    :return: Offspring chromosome
    """
    offspring = Chromosome(maximum_depth=DEPTH_MAX, terminals=terminals, functions=functions, constants=constants)

    start_parent_one = randint(0, parent_one.size - 1)
    end_parent_one = parent_one.traverse(start_parent_one)

    start_parent_two = randint(0, parent_two.size - 1)
    end_parent_two = parent_two.traverse(start_parent_two)

    offspring.representation = [0 for _ in range(len(parent_one.representation) + len(parent_two.representation))]

    while len(offspring.representation) < len(parent_one.representation) + len(parent_two.representation):
        offspring.representation += [0]
    i = -1
    for i in range(start_parent_one):
        offspring[i] = parent_one[i]
    for j in range(start_parent_two, end_parent_two):
        i = i + 1
        offspring[i] = parent_two[j]
    for j in range(end_parent_one, parent_one.size):
        i = i + 1
        offspring[i] = parent_one[j]
    offspring.representation = [x for x in offspring.representation if x != 0]
    offspring.size = len(offspring.representation)
    return offspring


def mutation(chromosome: Chromosome):
    """
    Replace a random position in the chromosome tree with an equivalent one.
    :param chromosome: The chromosome to be mutated
    :return: Mutated chromosome.
    """
    offspring = Chromosome(maximum_depth=DEPTH_MAX, terminals=terminals, functions=functions, constants=constants)
    pos = randint(0, chromosome.size-1)
    offspring.representation = chromosome[:]
    offspring.size = chromosome.size
    if offspring[pos] > 0:
        # Mutation node is terminal
        offspring[pos] = randint(1, len(terminals))
    else:
        # Mutation node is function
        curr_func = offspring.get_func_at_index(pos)
        if curr_func in unary_functions:
            while True:
                offspring[pos] = -randint(1, len(functions))
                new_func = offspring.get_func_at_index(pos)
                if new_func in unary_functions and new_func != curr_func:
                    break
        else:
            while True:
                offspring[pos] = -randint(1, len(functions))
                new_func = offspring.get_func_at_index(pos)
                if new_func in binary_functions and new_func != curr_func:
                    break
    return offspring


def genetic_search(
        dataset: List[List[float]],
        labels: List[int],
        pop_size: int = 1000,
        replace_p: float = 0.2,
        tournament_p: float = 0.05,
        mutation_c: float = 0.1,
        epsilon: float = 0.65) -> Chromosome:
    """
    Genetic search using tournament selection, mutation and elitism with constant population.
    :param dataset          Training dataset
    :param labels           Training labels
    :param pop_size:        Size of population
    :param replace_p:       Percent of population to be replaced in [0, 1]; equal to percent of
                            children to be generated in order to keep population constant
    :param tournament_p:    Tournament size proportionally to population, should be in [0, 1]
    :param mutation_c:      Chance of mutation in [0, 1]
    :param epsilon          Threshold accuracy to be obtained in [0, 1]
    :return:                Return best fitting individual
    """
    dataset = [row + constants for row in dataset]
    logger = Logger.get_logger()
    seed(None)

    assert mutation_c < 1, "Mutation chance should be between 0 and 1"
    assert replace_p < 1, "Children percent of population for generation should be between 0 and 1"
    assert tournament_p < 1, "Tournament size percent of should be between 0 and 1"
    logger.log('GENERATING INIT POOL, WILL TAKE A WHILE..')
    individuals = [Chromosome(DEPTH_MAX, terminals, functions, constants) for _ in range(pop_size)]
    for individual in individuals:
        individual.compute_fitness(dataset=dataset, labels=labels)
    best_individual = None
    tournament_size = int(floor(pop_size * tournament_p))
    pop_replace = int(floor(pop_size * replace_p))

    better_fitness = lambda i1, i2: i1 if i1.fitness < i2.fitness else i2

    epoch_idx = 0
    while best_individual is None or best_individual.accuracy < epsilon:
        logger.log(f'START EPOCH {epoch_idx+1}')

        try:
            """
            Smaller fitness score translated to better individual;
            Selection probability must be inversely proportional
            """
            prob_distribution = [max(ind.fitness for ind in individuals) - ind.fitness for ind in individuals]
            # Normalize distribution to sum 1
            prob_distribution = [p / sum(prob_distribution) for p in prob_distribution]
        except ZeroDivisionError:
            """
            Waring: the algorithm might get stuck in a local optimum, resulting in the following unusual
            behaviour: the fittest local optimum individual will take over the entire pool, resulting in a
            pool with identical fitness; thus the code crashes with division by zero error due to above lines.
            """
            logger.log(f'STUCK IN LOCAL OPTIMUM {best_individual.fitness} {best_individual.accuracy}')
            assert False

        offsprings = []
        for i in range(pop_replace):
            """
            Avoid sampling {tournament_size * 2} - individuals selected for the first tournament will not
            have a chance in being picked for the second parent
            """
            selected = list(choice(individuals, size=tournament_size, replace=False, p=prob_distribution))
            selected += list(choice(individuals, size=tournament_size, replace=False, p=prob_distribution))

            first_parent = reduce(better_fitness, selected[:tournament_size])
            second_parent = reduce(better_fitness, selected[tournament_size:])

            offspring = crossover(first_parent, second_parent)
            # Mutate the offspring
            if random() < mutation_c:
                offspring = mutation(offspring)

            offsprings.append(offspring)
        logger.log(f'GENERATED OFFSPRINGS')

        # Calculate fitness
        for offspring in offsprings:
            offspring.compute_fitness(dataset=dataset, labels=labels)
        individuals += offsprings
        logger.log(f'CALCULATED OFFSPRING FITNESS')

        # Apply elitism - keep population pool constant
        individuals.sort(key=lambda indiv: indiv.fitness)
        individuals = individuals[:pop_size]

        # Select next best individual
        if best_individual is None or best_individual.accuracy < individuals[0].accuracy:
            best_individual = individuals[0]

        logger.log(f'BEST INDIVIDUAL {best_individual.fitness} {best_individual.accuracy} vs {epsilon}')
        logger.log('========')
        epoch_idx += 1

    logger.log(f'POP_SIZE {pop_size} MUTATION {mutation_c} REPLACE {replace_p} TOURNAMENT {tournament_p}')
    logger.log(str(best_individual))
    logger.log(f'{best_individual.fitness}, {best_individual.accuracy}')
