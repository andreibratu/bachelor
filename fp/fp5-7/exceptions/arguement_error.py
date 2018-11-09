class ArguementError(Exception):
    """Exception raised for invalid arguements combination."""

    def __init__(self, message):
        super(ArguementError, self).__init__(message)
