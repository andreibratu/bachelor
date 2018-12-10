from typing import List, Callable


def my_filter(arr: List, f: Callable):
    return [x for x in arr if f(x)]
