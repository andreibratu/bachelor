import random


class Repository:


    def __init__(self):
        with open('words.txt') as f:
            self.__words = [w for w in f.read().split('\n') if len(w) == 4]
            self.__hs = []


    def is_valid(self, w):
        return w in self.__words


    def add_score(self, result):
        self.__hs.append(result)


    def get_scores(self):
        return self.__hs


    def pick(self):
        return self.__words[random.randint(0, len(self.__words))]
