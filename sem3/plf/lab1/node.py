class Node:

    def __init__(self, val):
        self.val = val
        self.next = None
    
    def head(self):
        return self.val
    
    def tail(self):
        return self.next

    @classmethod
    def from_array(cls, array):
        if len(array) == 0:
            return None
        nodes = [Node(x) for x in array]
        for idx in range(0, len(array)-1):
            nodes[idx].next = nodes[idx+1]
        return nodes[0]

    @classmethod 
    def union(cls, x: int, node = None):
        n = Node(x)
        n.next = node
        return n