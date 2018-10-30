from dao import Dao
from helper import parseNumber
from complex import Complex
from typing import Tuple
import sys
import os


class AbstractUI():
    INVALID_IDX = 'Invalid idx..'
    GOODBYE = 'Have a lovely day!'

    def __init__(self):
        self.dao = Dao()

    def loop(self):
        pass


class CommandUI(AbstractUI):
    GREETING = '''
    Welcome tho the really hip CLI of the current assignment. Type help for
    a list of commands.
    '''
    HELP = '''
    add [number] Append number at position
    insert [number] [idx] Insert number at position
    remove [idx] Remove number from given position
    remove [start] [stop] Remove a slice of the list
    replace [old_number] [new_number] Replace all instance of old with new
    list Print the list
    list real [lower_bound] [upper_bound] List numbers with bounded real part
    list modulus [<|=|>] [number] List numbers whose modulus adheres to rule
    sum [start] [stop] Return the sum of numbers in given slice
    product [start] [stop] Return the product of the numbers in given slice
    filter real Filter out all numbers that have an imaginary part
    filter modulus [<|=|>] [number] Filter out numbers with unwanted modulus
    undo Undo the last list modification
    help List this menu
    clear Clear the screen
    exit Exit the application
    '''

    def loop(self):
        print(self.GREETING)
        while True:
            try:
                args = input('> ').split()

                if len(args) == 0:
                    continue

                if args[0] == 'add' and len(args[1:]) == 1:
                    c = parseNumber(args[1])
                    self.dao.add(c)
                    continue

                if args[0] == 'insert' and len(args[1:]) == 2:
                    c = parseNumber(args[1])
                    idx = int(args[2])
                    self.dao.insert(c, idx)
                    continue

                if args[0] == 'remove' and len(args[1:]) == 1:
                    self.dao.remove(int(args[1]))
                    continue

                if args[0] == 'remove' and len(args[1:]) == 2:
                    idx_start = int(args[1])
                    idx_stop = int(args[2])
                    self.dao.removeSlice(idx_start, idx_stop)
                    self.dao.display([])
                    continue

                if args[0] == 'replace' and len(args[1:]) == 2:
                    old = parseNumber(args[1])
                    new = parseNumber(args[2])
                    if self.dao.replace(old, new):
                        self.dao.display([])
                    else:
                        print('Number to be replaced is not in the list')
                    continue

                if args[0] == 'list' and len(args[1:]) in (0, 3):
                    print(self.dao.display(args[1:]))
                    continue

                if args[0] in ('product', 'sum') and len(args[1:]) == 2:
                    num = self.dao.property(args)
                    print(num)
                    continue

                if args[0] == 'filter' and len(args[1:]) in (1, 3):
                    result = self.dao.filter(args[1:])
                    if result:
                        print(self.dao.display([]))
                        continue
                    else:
                        print('No numbers to be filtered')
                        continue

                if args[0] == 'undo' and len(args[1:]) == 0:
                    self.dao.undo()
                    print(self.dao.display([]))
                    continue

                if args[0] == 'help':
                    print(self.HELP)
                    continue

                if args[0] == 'clear':
                    _ = os.system('clear')
                    continue

                if args[0] == 'exit':
                    sys.exit(0)

                raise ValueError('Invalid arg combination')

            except SystemExit:
                print(self.GOODBYE)
                break

            except EOFError:
                print('exit')
                print(self.GOODBYE)
                break

            except (ValueError, IndexError) as e:
                print(e)
                continue


class MenuUI(AbstractUI):
    GREETING = '''
    Welcome the the other hip interface of this project, the menu UI!
    '''
    MENU = '''
     1. Add a number to the list.
     2. Insert number at index.
     3. Remove number at idx.
     4. Remove numbers from a slice.
     5. Replace a number with another number.
     6. Display the entire list.
     7. Display numbers whose real part is between given bounds.
     8. Display numbers whose modulus compares with a given value.
     9. Return the sum of numbers in a given slice.
    10. Return the product of numbers in a given slice.
    11. Filter the list to only contain real numbers
    12. Filter out the numbers whose modulus meets a requirement.
    13. Undo the last list modification.
    14. Exit the application.
    '''
    COMPLEX = 'Input the complex number: '
    IDX = 'Input the idx: '
    LS = 'Input the lower slice idx: '
    US = 'Input the upper slice idx: '
    LB = 'Input the lower bound: '
    UB = 'Input the upper bound: '

    def loop(self):
        while True:
            try:
                print(self.MENU)
                opt = int(input('Your option: '))

                if opt == 1:
                    self.dao.add(parseNumber(input(self.COMPLEX)))
                    continue

                if opt == 2:
                    self.dao.insert(
                        parseNumber(input(self.COMPLEX)),
                        int(input(self.IDX))
                    )
                    continue

                if opt == 3:
                    self.dao.remove(int(input(self.IDX)))
                    continue

                if opt == 4:
                    self.dao.removeSlice(
                        int(input(self.LS)),
                        int(input(self.US))
                    )
                    continue

                if opt == 5:
                    old = parseNumber(input('Input old number: '))
                    new = parseNumber(input('Input new number: '))
                    if self.dao.replace(old, new):
                        self.dao.display()
                    else:
                        print('Number to be replaced is not in the list')
                    continue

                if opt == 6:
                    print(self.dao.display([]))
                    continue

                if opt == 7:
                    lb = int(input(self.LB))
                    ub = int(input(self.UB))
                    self.dao.display(['real', lb, ub])
                    continue

                if opt == 8:
                    sign = input('Input a comparator [<|=|>]: ')
                    target_modulus = float(input('Input target modulus: '))
                    continue

                if opt == 9:
                    lb = int(input(self.LB))
                    ub = int(input(self.UB))
                    self.dao.property(['sum', lb, ub])
                    continue

                if opt == 10:
                    lb = int(input(self.LB))
                    ub = int(input(self.UB))
                    self.dao.property(['product', lb, ub])

                if opt == 11:
                    result = self.dao.filter(['filter', 'real'])
                    if result:
                        print(self.dao.display([]))
                    else:
                        print('No numbers to be filtered')
                    continue

                if opt == 12:
                    sign = input('Input a comparator [<|=|>]: ')
                    t_modulus = float(input('Input target modulus: '))

                    result = self.dao.property(['modulus', sign, t_modulus])

                    if result:
                        print(self.dao.display([]))
                    else:
                        print('No numbers to be filtered')
                    continue

                if opt == 13:
                    self.dao.undo()
                    print(self.dao.display([]))
                    continue

                if opt == 14:
                    sys.exit(0)

                raise ValueError('Invalid option')

            except SystemExit:
                print(self.GOODBYE)
                break

            except EOFError:
                print('exit')
                print(self.GOODBYE)
                break

            except (ValueError, IndexError) as e:
                print(e)
                continue
