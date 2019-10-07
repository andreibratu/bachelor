from node import Node

def traverse(numbers: Node) -> int:
    if numbers is None:
        return 0
    if numbers.val % 2 == 0:
        return traverse(numbers.tail()) + numbers.val
    else:
        return traverse(numbers.tail()) - numbers.val


l1 = Node.from_array([1, 5, 8, 2, 3])
assert(traverse(l1) == 1)

l2 = Node.from_array([2, 2, 6, 8])
assert(traverse(l2) == 18)

l3 = Node.from_array([1, 5, 2])
assert(traverse(l3) == -4)

l4 = Node.from_array([])
assert(traverse(l4) == 0)