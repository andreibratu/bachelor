class UI:

    def __init__(self, hw_controller):
        self._hw_controller = hw_controller


    def _print_menu(self):
        menu = '''1.Add\n2.Display\n3.Dishonesty\n4.Exit'''
        print(menu)


    def _add(self):
        name = input('Input a name: ')
        hw = input('Input a solution: ')
        self._hw_controller.insert(name=name, hw=hw)


    def _display(self):
        for hw in self._hw_controller.all():
            print(hw)


    def _dishonest(self):
        for message in self._hw_controller.check_dishonest():
            print(message)


    def loop(self):
        while True:
            self._print_menu()
            option = input('Input option: ')

            if option == '4':
                print('\nGoodbye!')
                break

            try:
                print('---')
                {
                    '1': self._add,
                    '2': self._display,
                    '3': self._dishonest,
                }[option]()
                print('---')

            except KeyError:
                print('\nInvalid option\n')
                continue
