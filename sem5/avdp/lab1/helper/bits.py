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


def substract_one_binary(binary: List[int]) -> List[int]:
    carry = 1
    answer = binary[::-1]
    for idx, _ in enumerate(answer):
        answer[idx] -= carry
        carry = 0
        if answer[idx] == -1:
            answer[idx] = 1
            carry = 1
    if carry == 1:
        answer = answer[:-1]
    return answer[::-1]


def precompute_representations(upp_bound_rank: int):
    try:
        with open("precompute_bit.json", "r") as fp:
            int_to_bit, bit_to_int = json.load(fp)
            if int_to_bit["max_rank"] < upp_bound_rank:
                raise FileNotFoundError
            return int_to_bit, bit_to_int
    except FileNotFoundError:
        # Memoisation does not exist or is not sufficient
        int_to_bit = {}
        for rank in range(upp_bound_rank + 1):
            negative_bound = - (2 ** rank) + 1
            negative_mask = [1 for _ in range(rank+1)]
            last_negative_mask = [1] + [0 for _ in range(rank)]
            while negative_mask != last_negative_mask:
                int_to_bit[negative_bound] = "".join([str(x) for x in negative_mask])
                negative_mask = substract_one_binary(negative_mask)
                negative_bound -= 1

            positive_bound = (2 ** rank) - 1
            positive_mask = [0] + [1 for _ in range(rank)]
            last_positive_mask = [0 for _ in range(rank + 1)]
            while positive_mask != last_positive_mask:
                int_to_bit[positive_bound] = "".join([str(x) for x in positive_mask])
                positive_mask = substract_one_binary(positive_mask)
                positive_bound -= 1
        bit_to_int = {v: k for k, v in int_to_bit.items()}
        int_to_bit["max_rank"] = upp_bound_rank
        bit_to_int["max_rank"] = upp_bound_rank
        with open("precompute_bit.json", "w+") as fp:
            json.dump([int_to_bit, bit_to_int], fp)
        return int_to_bit, bit_to_int


assert add_one_binary([0]) == [1]
assert add_one_binary([1, 0]) == [1, 1]
assert add_one_binary([1, 0, 1, 1]) == [1, 1, 0, 0]
assert add_one_binary([1, 1]) == [1, 0, 0]

assert substract_one_binary([1]) == [0]
assert substract_one_binary([1, 1, 0]) == [1, 0, 1]
assert substract_one_binary([1, 1, 0, 1]) == [1, 1, 0, 0]
assert substract_one_binary([0, 1, 1, 0, 0, 0]) == [0, 1, 0, 1, 1, 1]
assert substract_one_binary([0, 1, 0, 0]) == [0, 0, 1, 1]

precompute_representations(12)