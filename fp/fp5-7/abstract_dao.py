class AbstractDao:
    """Class that describes the basic functionality of the other DAOs."""

    def __init__(self):
        self.objects = {}

    def create(self):
        raise NotImplementedError

    def find_id(self, id: int):
        raise NotImplementedError

    def delete_id(self, id: int):
        raise NotImplementedError

    def update(self):
        raise NotImplementedError

    def display(self):
        print(list(self.objects.values()))
