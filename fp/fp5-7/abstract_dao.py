class AbstractDao:

    objects = {}

    def create(self):
        raise NotImplementedError

    def find_id(self, id: int):
        raise NotImplementedError

    def delete_id(self, id: int):
        raise NotImplementedError

    def update(self):
        raise NotImplementedError

    def display(self):
        print(list(AbstractDao.objects.values()))
