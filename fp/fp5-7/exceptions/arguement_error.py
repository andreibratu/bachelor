class ArguementError(Exception):
    """Exception raised for invalid combination of arguements."""

    def __init__(self, message):
        super(ArguementError, self).__init__(message)
