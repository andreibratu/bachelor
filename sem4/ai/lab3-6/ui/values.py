from aco.aco_service import ant_colony_optimization
from genetic.genetic_service import genetic_algorithm
from hill_climb.hill_climb_service import hill_climb
from pso.pso_service import particle_swarm_optimisation

default_values = {
    0:
        {
            'hcInput': 3,
            'hcRunsInput': 1000
        },
    1:
        {
            'geneticNInput': 2,
            'geneticPopSizeInput': 50,
            'geneticPopReplaceInput': 10,
            'geneticTournamentSizeInput': 3,
            'geneticRunsInput': 1000,
            'geneticMutationChanceInput': 0.3
        },
    2:
        {
            'psoNInput': 3,
            'psoRunsInput': 500,
            'psoSwarmSizeInput': 1000,
            'psoWInput': 0.3,
            'psoC1Input': 0.2,
            'psoC2Input': 0.5
        },
    3:
        {
            'acoNInput': 3,
            'acoRunsInput': 100,
            'acoAntsCountInput': 10,
            'acoAlphaInput': 3,
            'acoBetaInput': 5,
            'acoQInput': 0.7,
            'acoTraceInput': 5
        }
}

approaches = {
    0: hill_climb,
    1: genetic_algorithm,
    2: particle_swarm_optimisation,
    3: ant_colony_optimization
}
