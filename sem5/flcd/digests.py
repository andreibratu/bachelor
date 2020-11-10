def str_digest(string_val: str) -> int:
    result = 0
    p, init_p = 1, 53
    for char in string_val:
        result += ord(char) * p
        p *= init_p
    return int(result)


def float_digest(float_val: float) -> int:
    x = round(float_val, 37)
    return int(x * 1e37)