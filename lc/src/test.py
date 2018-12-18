from number import Number
from validator import NumberValidator
from exceptions import InvalidNumberException


def test_number_class():
    number = Number('1291', 8)
    assert number.val == '1291'
    assert number.base == 8
    number.base = 7
    assert number.base == 7


def test_atrib():
    number = Number('1291', 8)
    assert number.get_representation() == [1, 9, 2, 1]
    number = Number('010101', 2)
    assert number.get_representation == [1, 0, 1, 0, 1, 0]
    number = Number('ABCDEF', 16)
    assert number.get_representation == [15, 14, 13, 12, 11, 10]


def test_add():
    number1 = Number('1291', 10)
    number2 = Number('9', 10)
    sum = number1 + number2
    assert sum.val == '1300'
    number1 = Number('ABC', 16)
    number2 = Number('1012', 16)
    sum = number1 + number2
    assert sum.val == '1ACE'
    number1 = Number('0101', 2)
    number2 = Number('0101', 2)
    sum = number1 + number2
    assert sum.val == '1010'
    number1 = Number('0101', 2)
    number2 = Number('0101', 3)
    try:
        sum = number1 + number2
        assert False
    except ValueError:
        assert True


def test_sub():
    number1 = Number('1291', 10)
    number2 = Number('9', 10)
    dif = number1 - number2
    assert dif.val == '1282'
    number1 = Number('12321', 8)
    number2 = Number('1723', 8)
    dif = number1 - number2
    assert dif.val == '10376'
    number1 = Number('0101', 2)
    number2 = Number('0101', 2)
    dif = number1 - number2
    assert dif.val == '0'
    number1 = Number('1010', 2)
    number2 = Number('111', 2)
    dif = number1 - number2
    assert dif.val == '11'
    number1 = Number('0101', 2)
    number2 = Number('0101', 3)
    try:
        dif = number1 - number2
        assert False
    except ValueError:
        assert True


def test_mul():
    number1 = Number('1291', 10)
    number2 = Number('91', 10)
    try:
        mul = number2 * number1
        assert False
    except ValueError:
        assert True

    number1 = Number('1291', 10)
    number2 = Number('9', 10)
    mul = number1 * number2
    assert mul.val == '11619'
    number1 = Number('12321', 8)
    number2 = Number('7', 8)
    mul = number1 * number2
    assert mul.val == '110667'
    number1 = Number('12321', 8)
    number2 = Number('0', 8)
    mul = number1 * number2
    assert mul.val == '0'
    number1 = Number('ABC', 16)
    number2 = Number('7', 16)
    mul = number1 * number2
    assert mul.val == '4B24'


def test_div():
    number1 = Number('1291', 10)
    number2 = Number('91', 10)
    try:
        div = number2 / number1
        assert False
    except ValueError:
        assert True

    number1 = Number('1291', 10)
    number2 = Number('9', 10)
    div = number1 / number2
    assert div[0].val == '143'
    assert div[1].val == '4'

    number1 = Number('ABC', 16)
    number2 = Number('B', 16)
    div = number1 / number2
    assert div[0].val == 'F9'
    assert div[1].val == '9'


def test_from_base10_to_any_base():
    assert Number('127', 10).to_any_base(16) == Number('7F', 16)
    assert Number('10', 10).to_any_base(2) == Number('1010', 2)
    assert Number('125', 10).to_any_base(6) == Number('325', 6)


def test_from_any_base_to_base10():
    assert Number('1331', 4).to_any_base(10) == Number('125', 10)
    assert Number('1010', 2).to_any_base(10) == Number('10', 10)
    assert Number('7F', 16).to_any_base(10) == Number('127', 10)


def test_any_base_to_any_base():
    assert Number('5274', 8).to_any_base(16) == Number('ABC', 16)
    assert Number('ABC', 16).to_any_base(8) == Number('5274', 8)
    assert Number('1111', 2).to_any_base(16) == Number('F', 16)


def test_fast_2_4():
    number = Number('100110', 2)
    assert number.fast_2_4().val == '212'
    number = Number('1111110001', 2)
    assert number.fast_2_4().val == '33301'
    number = Number('10110', 2)
    assert number.fast_2_4().val == '112'
    number = Number('111110001', 2)
    assert number.fast_2_4().val == '13301'
    number = Number('33301', 4)
    assert number.fast_2_4().val == '1111110001'
    number = Number('13301', 4)
    assert number.fast_2_4().val == '0111110001'


def test_fast_2_8():
    number = Number('1001101', 2)
    assert number.fast_2_8().val == '115'
    number = Number('111110001', 2)
    assert number.fast_2_8().val == '761'
    number = Number('115', 8)
    assert number.fast_2_8().val == '001001101'
    number = Number('761', 8)
    assert number.fast_2_8().val == '111110001'


def test_fast_2_16():
    number = Number('10010101010111', 2)
    assert number.fast_2_16().val == '2557'
    number = Number('1111110010101010111', 2)
    assert number.fast_2_16().val == '7E557'
    number = Number('7E557', 16)
    assert number.fast_2_16().val == '01111110010101010111'
    number = Number('2557', 16)
    assert number.fast_2_16().val == '0010010101010111'


def test_validator():
    number = Number('', '')
    val = NumberValidator()
    try:
        val.validate(number)
        assert False
    except InvalidNumberException as ex:
        assert len(ex.errors) == 2

    number = Number('1284', 8)
    val = NumberValidator()
    try:
        val.validate(number)
        assert False
    except InvalidNumberException as ex:
        assert len(ex.errors) == 1

    number = Number('9ioo;', 10)
    try:
        val.validate(number)
        assert False
    except InvalidNumberException as ex:
        assert len(ex.errors) == 1
