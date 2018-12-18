from number import Number
from validator import NumberValidator
from exceptions import InvalidNumberException


class UI(object):
    """Class delegated with the user interface."""

    def _print_menu(self):
        menu = "1. To add two numbers in a base\n" \
               "2. To substract two numbers in a base\n" \
               "3. To multiply a number with a digit in a base\n" \
               "4. To divide a number to a digit in a base\n" \
               "5. To convert a number from a base to another\n" \
               "6. To fast transform a number between base2 and base8\n" \
               "7. To fast transform a number between base2 and base8\n" \
               "8. To fast transform a number between base2 and base16\n" \
               "9. To exit the application"

        print(menu)


    def _read_number_add_sub(self, ordinal: str) -> Number:
        """Read number instance for addition or substraction.

        Args:
            ordinal (str): Ordinal of the number to be inputed (first/ second)
        Returns:
            The read number.
        """

        number = input('Input {} number'.format(ordinal))
        base = int(input('Input the base of the number: '))
        nr = Number(number, base)
        val = NumberValidator()

        try:
            val.validate(nr)
            return nr

        except InvalidNumberException as ex:
            print(ex)

        except ValueError:
            print("Invalid numbers basis combination!")


    def _read_number_mul_div(self, ordinal):
        """Read number instance for prodiplication or division.

        Args:
            ordinal (str): Ordinal of the number to be inputed (first/ second)
        Returns:
            The read number.
        """

        number = input('Input {}: '.format(ordinal))
        base = int(input("Input base: "))
        nr = Number(number, base)
        val = NumberValidator()

        try:
            val.validate(nr)
            return nr

        except InvalidNumberException as ex:
            print(ex)

        except ValueError:
            print("Invalid numbers' basis combination!")


    def _add(self):
        """Add two numbers in a given base."""

        number1 = self._read_number_add_sub('first')
        if number1 is None:
            return
        number2 = self._read_number_add_sub('second')
        if number2 is None:
            return
        base3 = int(input('Input the base for addition: '))

        number1 = number1.to_any_base(base3)
        number2 = number2.to_any_base(base3)

        sum = number1 + number2
        print('Sum in base {} is: '.format(base3))
        print('{} + {} = {}\n'.format(number1.val, number2.val, sum.val))


    def _sub(self):
        """Substract two numbers in a given base."""

        number1 = self._read_number_add_sub('first')
        if number1 is None:
            return

        number2 = self._read_number_add_sub('first')
        if number2 is None:
            return

        base3 = int(input('Input the base for subtraction: '))

        number1 = number1.to_any_base(base3)
        number2 = number2.to_any_base(base3)

        if number1 > number2:
            dif = number1 - number2
            print('Result in base {} is: '.format(base3))
            print('{} - {} = {}'.format(number1.val, number2.val, dif.val))

        else:
            dif = number2 - number1
            print('Result in base {} is: '.format(base3))
            print('{} - {} = {}'.format(number2.val, number1.val, dif.val))


    def _mul(self):
        """Multiply two numbers in given base."""

        number1 = self._read_number_mul_div('first number')
        if number1 is None:
            return

        number2 = self._read_number_mul_div('digit')
        if number2 is None:
            return

        base3 = int(input('Input the base for the multiplication: '))

        number1 = number1.to_any_base(base3)
        number2 = number2.to_any_base(base3)

        try:
            prod = number1 * number2
            print('The product in base {}:'.format(base3))
            print('{} * {} = {}'.format(number1.val, number2.val, prod.val))

        except ValueError as e:
            print(e)
            print('Second number has more than one digit!')


    def _div(self):
        """Divide two numbers in given base."""

        number1 = self._read_number_mul_div('first number')
        if number1 is None:
            return

        number2 = self._read_number_mul_div('digit')
        if number2 is None:
            return

        base3 = int(input('Input the base for the division: '))

        number1 = number1.to_any_base(base3)
        number2 = number2.to_any_base(base3)

        try:
            div = number1 / number2
            print('Remainder in base {} is:'.format(base3))
            print('{} / {} = {}'.format(number1.val, number2.val, div[0].val))
            print('The remainder in base {} is:'.format(base3))
            print('{} % {} = {}'.format(number1.val, number2.val, div[1].val))

        except ValueError as e:
            print(e)
            print('Second number has more than one digit')


    def _change_base(self):
        """Change base of a number."""

        nr = self._read_number_mul_div('number')
        if nr is None:
            return

        new_base = int(input('Input the new base of the number: '))
        new_n = nr.to_any_base(new_base)
        val = NumberValidator()

        try:
            val.validate(new_n)
            print('The number in base {} is {}'.format(new_base, new_n.val))

        except InvalidNumberException as ex:
            print(ex)


    def _fast_2_4(self):
        """Fast convert between base2 and base4."""

        nr = self._read_number_mul_div('number')
        if nr is None:
            return

        if nr.base != 2 and nr.base != 4:
            print('Number must be in base2 or base4')
            return

        if nr.base == 2:
            new_base = 4
        else:
            new_base = 2

        new_n = nr.to_any_base(new_base)
        val = NumberValidator()
        try:
            val.validate(new_n)
            print('Number {} in the new base is {}'.format(nr.val, new_n.val))

        except InvalidNumberException as ex:
            print(ex)


    def _fast_2_8(self):
        """Fast convert between base2 and base8."""

        nr = self._read_number_mul_div('number')

        if nr is None:
            return

        if nr.base != 2 and nr.base != 8:
            print('Number must be in base2 or base8')
            return

        if nr.base == 2:
            new_base = 8
        else:
            new_base = 2

        new_n = nr.to_any_base(new_base)
        val = NumberValidator()
        try:
            val.validate(new_n)
            print('Number {} in the new base is {}'.format(nr.val, new_n.val))

        except InvalidNumberException as ex:
            print(ex)


    def _fast_2_16(self):
        """Fast convert between base2 and base16."""

        nr = self._read_number_mul_div('number')

        if nr is None:
            return

        if nr.base != 2 and nr.base != 16:
            print('Number must be in base2 or base16')
            return

        if nr.base == 2:
            new_base = 16
        else:
            new_base = 2

        new_n = nr.to_any_base(new_base)
        val = NumberValidator()
        try:
            val.validate(new_n)
            print('Number {} in the new base is {}'.format(nr.val, new_n.val))

        except InvalidNumberException as ex:
            print(ex)


    def show_menu(self):
        """Display interface menu."""

        while True:

            try:
                self._print_menu()
                cmd = input('Please input command: ')

                try:
                    {
                        '1': self._add,
                        '2': self._sub,
                        '3': self._mul,
                        '4': self._div,
                        '5': self._change_base,
                        '6': self._fast_2_4,
                        '7': self._fast_2_8,
                        '8': self._fast_2_16,
                        '9': exit
                    }[cmd]()

                except KeyError:
                    print('Invalid command..')
                    continue

            except KeyboardInterrupt:
                print('\nGoodbye!')
                exit()
