from itertools import combinations
from copy import copy

from homework import Homework


class HomeworkController:

    def __init__(self, hw_repo):
        self._repo = hw_repo


    def all(self):
        """Return a list of all assignments

        Returns:
            A list of Homework objects.
        """
        return self._repo.all()


    def insert(self, name, hw):
        """Insert a Homework object into the repository.

        Args:
            name (str): The name of the student.
            hw (str): The assignment
        """
        self._repo.insert(Homework(name=name, hw=hw))


    def check_dishonest(self):
        """Check for dishonest assignments.

        For each pair of Homework objects, we check wether a word from the
        hw property appears in the field of the other object. The dishonesty
        percentage is calculated as the percent of the total words that appear.

        Should a word in appear twice in hw1 and once in hw2, it will be
        counted only once.

        Returns:
            A list of messages regarding dishonesty.
        """

        messages = []

        # Try all combinations of 2 assignments
        for hw1, hw2 in combinations(self._repo.all(), 2):
            text1 = hw1.hw.split()
            text2 = hw2.hw.split()
            count1 = len(text1)
            count2 = len(text2)

            # Copies to preserve original form
            copy1 = copy(text1)
            copy2 = copy(text2)

            illegal1 = 0
            for word in text1:
                if word in text2:
                    text2.remove(word)  # Remove from the list (see docs)
                    illegal1 += 1

            text1 = copy1
            text2 = copy2

            illegal2 = 0
            for word in text2:
                if word in text1:
                    text1.remove(word)  # Ditto
                    illegal2 += 1

            p1 = illegal1 / count1
            if p1 >= 0.2:
                messages.append("{} -> {} ({}% of {}'s solution)".format(
                    hw1.name,
                    hw2.name,
                    int(p1 * 100),
                    hw2.name
                ))

            p2 = illegal2 / count2
            if p2 >= 0.2:
                messages.append("{} -> {} ({}% of {}'s solution)".format(
                    hw2.name,
                    hw1.name,
                    int(p2 * 100),
                    hw1.name
                ))

        return messages
