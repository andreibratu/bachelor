from repos.repos.repository import AbstractRepository


class MovieRepository(AbstractRepository):
    """Object that manages Movie entities."""


    def __init__(self):
        super().__init__()
