class ConflictError(Exception):
    """Exception raised when client has already rented movie."""

    def __init__(self, message):
        super(ConflictError, self).__init__(message)
