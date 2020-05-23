from typing import Tuple, List

from logger import Logger
from service import genetic_search

classes = {
    'Slight-Left-Turn': 0,
    'Move-Forward': 1,
    'Slight-Right-Turn': 2,
    'Sharp-Right-Turn': 3
}


def build_dataset(input_path: str) -> Tuple[List[List[float]], List[int]]:
    inp_dataset, inp_labels = [], []
    with open(input_path, 'r') as f:
        lines = f.readlines()
        for line in lines:
            data_row = line.strip().split(',')
            data_row, label = data_row[:-1], data_row[-1]
            data_row = [float(x) for x in data_row]
            inp_dataset.append(data_row)
            inp_labels.append(classes[label])
    return inp_dataset, inp_labels


if __name__ == '__main__':
    """
    IMPORTANT
    Running a new genetic search will erase logs of the former.
    If this is the first run please consult the logs for proof of working.
    """

    logger = Logger.get_logger()
    dataset, labels = build_dataset('input.data')

    pop_size = int(input("Input population size: "))
    replace_p = float(input("Input replacement percent: "))
    tournament_p = float(input("Input tournament percent: "))
    mutation_c = float(input("Input mutation percent: "))
    epsilon = float(input("Input epsilon target: "))
    genetic_search(
        pop_size=pop_size,
        replace_p=replace_p,
        tournament_p=tournament_p,
        mutation_c=mutation_c,
        epsilon=epsilon,
        dataset=dataset,
        labels=labels
    )
