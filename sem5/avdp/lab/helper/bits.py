import json
from typing import List


def add_one_binary(binary: List[int]) -> List[int]:
    carry = 1
    answer = binary[::-1]
    for idx, _ in enumerate(answer):
        answer[idx] += carry
        carry = answer[idx] // 2
        answer[idx] %= 2
    if carry != 0:
        answer.append(1)
    return answer[::-1]


def precompute_representations(upp_bound_rank: int):
    int_to_bit = {}
    negative_numbers = set()
    positive_numbers = set()
    for rank in range(upp_bound_rank + 1):
        mask = [0 for _ in range(rank)]
        negative_bound = - (2 ** rank) + 1
        while negative_bound not in negative_numbers and negative_bound < 0:
            int_to_bit[negative_bound] = "".join([str(x) for x in mask])
            mask = add_one_binary(mask)
            negative_numbers.add(negative_bound)
            negative_bound += 1
        positive_bound = (2 ** rank) - 1
        while positive_bound not in positive_numbers and positive_bound > 0:
            int_to_bit[positive_bound] = "".join([str(x) for x in mask])
            mask = add_one_binary(mask)
            positive_numbers.add(positive_bound)
            positive_bound -= 1

    bit_to_int = {v: k for k, v in int_to_bit.items()}

    with open("precompute_bit.json", "w+") as fp:
        json.dump([int_to_bit, bit_to_int], fp, indent=4)
    return int_to_bit, bit_to_int


assert add_one_binary([0]) == [1]
assert add_one_binary([1, 0]) == [1, 1]
assert add_one_binary([1, 0, 1, 1]) == [1, 1, 0, 0]
assert add_one_binary([1, 1]) == [1, 0, 0]