from node import Node

def find(x: int, list: Node) -> bool:
    if list is None:
        return False
    if x == list.val:
        return True
    return find(x, list.tail())

def difference(list_a: Node, list_b: Node) -> Node:
    if list_a is None:
        return None
    if not find(list_a.val, list_b):
        return Node.union(list_a.val, difference(list_a.tail(), list_b))
    else:
        return difference(list_a.tail(), list_b)

assert(find(6, Node.from_array([1, 4, 7, 8])) is False)
assert(find(7, Node.from_array([])) is False)
assert(find(7, Node.from_array([7, 1, 5, 6])) is True)

l1 = Node.from_array([])
l2 = Node.from_array([1, 2, 6, 9])
assert(difference(l1, l2) is None)

l1 = Node.from_array([1, 5, 7, 9])
l2 = Node.from_array([7, 9])
diff = difference(l1, l2)
values = []
while diff is not None:
    values.append(diff.val)
    diff = diff.next
assert(values == [1, 5])

l1 = Node.from_array([1, 2, 7, 3, 4])
l2 = Node.from_array([7, 9])
diff = difference(l1, l2)
values = []
while diff is not None:
    values.append(diff.val)
    diff = diff.next
assert(values == [1, 2, 3, 4])