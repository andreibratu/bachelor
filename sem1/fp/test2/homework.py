class Homework:


    def __init__(self, name, hw, id=None):
        self.id = id
        self.name = name
        self.hw = hw


    def __str__(self):
        return '{} - {} - {}'.format(self.id, self.name, self.hw)
