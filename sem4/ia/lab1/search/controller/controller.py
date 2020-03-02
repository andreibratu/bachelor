from pandas import DataFrame

from service.service import ProblemService


class CommandLineController:

    _MENU = '1. Sudoku\n2. Cryptarithmetic\n3. Geometric\n4. Exit\n'

    def __init__(self, service: ProblemService):
        self._service = service

    def loop(self):
        while True:
            print(CommandLineController._MENU)
            try:
                opt = int(input("Please input an option: "))
            except ValueError:
                continue
            if not 1 <= opt <= 4:
                continue
            {
                1: self._solve_sudoku,
                2: self._solve_crypt,
                3: self._geometric,
                4: lambda: exit()
            }[opt]()

    def _solve_sudoku(self):
        size, att = None, None
        while True:
            try:
                size = int(input("Sudoku board size: "))
                att = int(input("Input number of attempts: "))
                break
            except ValueError:
                continue
        solution = self._service.solve_sudoku(size, att)
        if solution is None:
            print("No solution could be found!")
        else:
            print(DataFrame(solution))
            print('\n===\n\n')

    def _solve_crypt(self):
        op_one, op_two, op, result, attempts = [None] * 5
        while True:
            try:
                op_one = input("Input first number: ")
                op_two = input("Input second number: ")
                op = input("Input desired operation (+ - \\ *): ")
                result = input("Input result number: ")
                attempts = int(input("Input number of attempts: "))
                break
            except ValueError:
                continue
        solution = self._service.solve_crypt(op_one, op_two, op, result, attempts)
        if solution is None:
            print("No solution could be found!")
        else:
            print(solution)
            print('\n===\n\n')

    def _geometric(self):
        attempts = None
        while True:
            try:
                attempts = int(input("Input number of attempts: "))
                break
            except ValueError:
                continue
        solution = self._service.solve_geometric(attempts)
        if solution is None:
            print("No solution could be found!")
        else:
            print(DataFrame(solution))
            print('\n===\n\n')
