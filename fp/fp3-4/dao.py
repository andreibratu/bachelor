from complex import Complex
from typing import Tuple, List
from functools import reduce

class Dao:
    """Class that holds the main components of the program."""

    def __init__(self):
        self.list = [
            Complex(5, 7),
            Complex(4, 2),
            Complex(-3, 8),
            Complex(0, 0),
            Complex(-1, 0),
            Complex(6, 0),
            Complex(-2, 4.5),
            Complex(6, 2),
            Complex(9.3, 6.5),
            Complex(18.1, -4.5)
        ]
        self.old = []


    def add(self, c: Complex):
        """Add a number to the list.

        Args:
            c (Complex): The number to be added.
        """
        self.old.append(list(self.list))
        self.list.append(c)


    def insert(self, c: Complex, idx: int):
        """Insert a number at a given idx.

        Args:
            c (Complex): The number to be added.
            idx (int): The idx for insertion.
        Returns:
            True if the insertion was sucessful.
        """

        print(c)
        print(idx)

        if not idx < len(self.list):
            raise IndexError('Invalid index')

        self.old.append(list(self.list))
        self.list.insert(idx, c)


    def remove(self, idx: int):
        """Remove element at given idx.

        Args:
            idx (int): The idx of element to be removed.
        """

        if not idx < len(self.list):
            raise ValueError('Invalid index')

        self.old.append(list(self.list))
        del self.list[idx]


    def removeSlice(self, idx_start: int, idx_stop: int):
        """Remove slice of array given by the indexes.

        Args:
            idx_start (int): The start idx of the slice, inclusive.
            idx_stop (int): The stop idx of the slice, exclusive.
        Returns:
            True if the removal was succesful.
        """

        if not 0 <= idx_start < idx_stop <= len(self.list):
            raise IndexError('Invalid indexes')
        self.old.append(list(self.list))
        del self.list[idx_start:idx_stop]


    def replace(self, old_c: Complex, new_c: Complex):
        """Replace all occurences of a number with another.

        Args:
            old_c (Complex): The number to be replaced.
            new_c (Complex): The replacing number.

        Returns:
            True if the list was modified
        """

        old_list = list(self.list)
        modified_flag = False

        for i in range(0, len(self.list)):
            if self.list[i] == old_c:
                modified_flag = True
                self.list[i] = new_c

        if modified_flag:
            self.old.append(old_list)

        return modified_flag


    def display(self, args: List[str]) -> List[Complex]:
        """List all numbers from list that hold a certain property.

        For flexibility, the function is implemented using a variable number
        of arguements.

        Returns:
            The list of numbers that respect given property,
        """

        REAL, MODULUS = ('real', 'modulus')

        if len(args) == 0:
            return self.list

        if args[0] == REAL:
            try:
                l = float(args[1])
                h = float(args[2])
                new_list = [x for x in self.list if l <= x.real <= h]
                return new_list
            except ValueError:
                raise ValueError('Could not parse the given bounds')

        if args[0] == MODULUS:
            try:
                sign = args[1]
                n = float(args[2])

                # Basically a neat switch
                return {
                    '<': [x for x in self.list if x.modulus < n],
                    '=': [x for x in self.list if x.modulus == n],
                    '>': [x for x in self.list if x.modulus > n]
                }[sign]

            except ValueError:
                raise ValueError('Could not parse given modulus')

            except KeyError:
                raise ValueError('Unknown arhitmetic sign')

        raise ValueError('Unknown display operation')


    def property(self, args: List[str]) -> Complex:
        """Return a characteristic for a given slice of the list.

        Due to multiple characteristics, the function accepts variable number
        of arguments.

        Slicing indexes respects the Python implementation [incl, excl)

        Returns:
            The calculated property.
        """

        SUM, PRODUCT = ('sum', 'product')

        try:
            l = int(args[1])
            r = int(args[2])

            if args[0] == SUM:
                return reduce(
                    lambda acc, x: acc+x, self.list[l:r],
                    Complex(0, 0)
                )

            if args[0] == PRODUCT:
                return reduce(
                    lambda acc, x: acc*x, self.list[l:r],
                    Complex(1, 0)
                )

        except ValueError:
            raise ValueError('Could not parse given indexes')


    def filter(self, args: List[str]) -> bool:
        """Modify list to only contain certain elements.

        Due to multiple characteristics, the function accepts variable number
        of arguments.

        Returns:
            True, if the operation modified the list.
        """

        type = str(args[0])
        REAL, MODULUS = ('real', 'modulus')
        new_list = []

        if type == REAL:
            new_list = [x for x in self.list if x.imag == 0]
            if len(self.list) != len(new_list):
                self.old.append(list(self.list))
                self.list = new_list
                return True

            return False

        if type == MODULUS:
            try:
                sign = args[1]
                n = float(args[2])

                # This is basically a neat switch
                new_list = {
                    '<': [x for x in self.list if x.modulus < n],
                    '=': [x for x in self.list if x.modulus == n],
                    '>': [x for x in self.list if x.modulus > n]
                }[sign]

                if len(self.list) != len(new_list):
                    self.old.append(list(self.list))
                    self.list = new_list
                    return True

                return False

            except KeyError:
                raise ValueError('Unknown arhitmetic operand')

            except ValueError:
                raise ValueError('Could not parse given modulus')

        raise ValueError('Unknown filter operation')

    def undo(self):
        """Undo the last modification made on the list."""
        if len(self.old):
            self.list = self.old.pop()
        else:
            raise ValueError('We are back at the Big Bang!')
