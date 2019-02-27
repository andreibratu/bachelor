from homework import Homework


class HomeworkRepository:

    def __init__(self):
        self.homework = {}
        with open('hw.txt', 'r') as f:
            lines = f.readlines()
            lines = [tuple(line.strip().split(',')) for line in lines]
            for line in lines:
                self.insert(Homework(id=line[0], name=line[1], hw=line[2]))


    def insert(self, hw):
        if hw.id is None:
            hw.id = len(self.homework) + 1
        self.homework[hw.id] = hw


    def delete(self, id):
        del self.homework[id]


    def get(self, id):
        return self.homework[id]


    def all(self):
        return self.homework.values()
