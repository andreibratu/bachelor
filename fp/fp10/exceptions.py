class ColumnFullException(Exception):

    def __init__(self):
        super().__init__(message='The column is already full!')


class InvalidMoveException(Exception):

    def __init__(self):
        super().__init__(message='Given column is invalid')
