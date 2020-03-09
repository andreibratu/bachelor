from service import ProblemService


class UserInterface:

    def __init__(self, service: ProblemService):
        self._service = service

    def _text_menu(self):
        approaches = self._service.get_approaches()
        text = 'Please choose a search algorithm:\n'
        for idx, approach_name in approaches.keys():
            text += f'\t{idx}. {approach_name}\n'
        return text

    def loop(self):
        global option, n
        approaches = self._service.get_approaches()

        while True:
            try:
                print(self._text_menu())
                option = int(input('Please select an approach: '))
                if 1 <= option <= len(approaches):
                    break
            except ValueError:
                continue

        while True:
            try:
                n = int(input('Please input the size of the board: '))
                break
            except ValueError:
                continue

        self._service.set_value_n(n)

        for (idx, _), approach in approaches.items():
            if idx == option:
                result = approach()
                if result is None:
                    print('No solution could be found!')
                else:
                    print(result)
                break
