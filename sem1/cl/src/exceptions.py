class InvalidNumberException(Exception):
    """Exception thrown in case of a validation error."""

    def __init__(self, errors):
        self.errors = errors


    def __str__(self):
        return '\n'.join(err for err in self.errors)
