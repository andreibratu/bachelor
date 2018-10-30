from dao import Dao
from complex import Complex
import unittest

test_dao = Dao()
test_dao.list = [
    Complex(5, 2),
    Complex(6, 0),
    Complex(-3, -2),
    Complex(1, 0)
]


class TestDao(unittest.TestCase):

    def add(self):
        l = len(test_dao.list)
        test_dao.add(Complex(2, 2))
        self.assertEqual(len(test_dao.list), l+1)

    def insert(self):
        l = len(test_dao.list)
        test_dao.insert(Complex(0, 0), 2)
        assert len(test_dao.list) == l+1
        with unittest.assertRaises(IndexError):
            test_dao.insert(ValueErrorComplex(0, 0), len(test_dao.list))

    def remove(self):
        l = len(test_dao.list)
        test_dao.remove(0)
        assert len(test_dao.list) == l-1
        with unittest.assertRaises(ValueError):
            test_dao.remove(len(test_dao.list))

    def removeSlice(self):
        with self.assertRaises(IndexError):
            test_dao.removeSlice(-4, 7)

    def replace(self):
        test_dao.list = [
            Complex(3, 6),
            complex(3, 6),
            Complex(3, 6)
        ]
        test_dao.replace(Complex(3, 6), Complex(2, 4))
        self.assertFalse(Complex(3, 6) in test_dao.list)
        self.assertTrue(Complex(2, 4) in test_dao.list)
        self.assertFalse(test_dao.replace(
            Complex(1, 2),
            Complex(3, 5)
            )
        )

    def display(self):
        test_dao.list = [
            Complex(2, 6),
            Complex(-5, 3),
            Complex(7, 2),
            Complex(4, 6)
        ]
        assert test.dao.display([]) == test_dao.list
        assert len(test_dao.display(['real', 2, 7])) == 3

    def sum(self):
        test_dao.list = [
            Complex(5, 2),
            Complex(6, 0),
            Complex(-3, -2),
            Complex(1, 0)
        ]
        self.assertEqual(test_dao.property(['sum', 0, 2]), Complex(11, 2))
        self.assertEqual(test_dao.property(['sum', 0, 4]), Complex(9, 0))
        # Product uses the same logic

    def filter(self):
        test_dao.list = [
            Complex(5, 2),
            Complex(6, 0),
            Complex(-3, -2),
            Complex(1, 0)
        ]
        test_dao.filter(['real'])
        self.assertEqual(test_dao.list, [])


if __name__ == '__main__':
    unittest.main()
