from typing import Tuple


class Node:
    def __init__(self, val):
        self.val = val
        self.next = None


class SimpleList:
    # Wow, much pun
    def __init__(self):
        self.head = None

    def insert(self, val):
        if self.head is None:
            self.head = Node(val)
        else:
            before, it = None, self.head
            while it is not None:
                if val == it.val:
                    # Key has been previously inserted
                    break
                before = it
                it = it.next
            if it is None:
                # First time insert of key
                before.next = Node(val)

    def __getitem__(self, key):
        it, val = self.head, None
        while it is not None:
            if key == it.val:
                val = it.val
                break
            it = it.next
        return val
