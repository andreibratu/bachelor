from collections import Counter

class Service:

    def __init__(self, repo):
        self.repo = repo


    def pick_word(self):

        self.answer = self.repo.pick()
        self.lookup = Counter()

        for c in self.answer:
            self.lookup[c] += 1


    def query(self, user_word):

        if len(user_word) != len(self.answer) or not self.repo.is_valid(user_word):
            return (False, None, None)

        bulls = 0
        cows = 0
        available = dict(self.lookup)

        for i in range(0, len(self.answer)):
            if self.answer[i] == user_word[i]:
                bulls += 1
            else:
                if user_word[i] in available and [user_word[i]] != 0:
                    cows += 1
                    available[user_word[i]] -= 1

        if bulls == len(self.answer):
            return (True, None, None)

        return (False, bulls, cows)


    def add_score(self, name, score):
        self.repo.add_score((name, self.answer, score))


    def print_scores(self):
        print(self.repo.get_scores())
