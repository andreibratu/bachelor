from typing import Tuple


class Node:
    def __init__(self, val):
        self.val = val
        self.next = None


class BucketList:
    # Wow, much pun
    def __init__(self):
        self.head = None

    def insert(self, val: Tuple):
        if self.head is None:
            self.head = Node(val)
        else:
            before, it = None, self.head
            while it is not None:
                k, v = it.val
                if val[0] == k:
                    # Key has been previously inserted
                    # We replace the value
                    it.val = val
                    break
                before = it
                it = it.next
            if it is None:
                # First time insert of key
                before.next = Node(val)

    def __getitem__(self, key):
        it, val = self.head, None
        while it is not None:
            k, v = it.val
            if key == k:
                val = v
                break
            it = it.next
        return val
