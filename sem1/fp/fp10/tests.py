import unittest

from table import Table
from game_master import GameMaster
from exceptions import ColumnFullException, InvalidColumnException


class TableTest(unittest.TestCase):

    def setUp(self):
        self.table = Table()

    def test_table_move_method(self):
        self.table.move('X', 0)
        assert 'X' in self.table[Table.ROWS - 1]
        self.table.move('O', 0)
        assert 'O' in self.table[Table.ROWS - 2]


    def test_table_column_full_exception(self):
        for _ in range(6):
            self.table.move('X', 0)
        with self.assertRaises(ColumnFullException):
            self.table.move('X', 0)

    def test_table_column_invalid_exception(self):
        with self.assertRaises(InvalidColumnException):
            self.table.move('O', -1)


class GameMasterTest(unittest.TestCase):

    def setUp(self):
        table = Table()
        self.table = table
        self.game_master = GameMaster(
            one_symbol='X',
            two_symbol='O',
            table=table)

    def test_check_victory(self):
        self.assertIsNone(self.game_master.check_victory())
        for col in range(4):
            self.game_master.move(col)
            if self.game_master.check_victory() is None:
                self.game_master.move(col)
        self.assertEqual(self.game_master.check_victory(), 1)

    def test_check_draw(self):
        self.assertFalse(self.game_master.check_draw())

    def test_move(self):
        self.game_master.move(0)
        self.assertTrue('X' in self.table._table[Table.ROWS - 1])


if __name__ == '__main__':
    unittest.main()
