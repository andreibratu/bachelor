from service import genetic_algorithm, hill_climb, particle_swarm_optimisation

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
        }
}

approaches = {
    0: hill_climb,
    1: genetic_algorithm,
    2: particle_swarm_optimisation
}