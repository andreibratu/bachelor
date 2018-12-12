from repos.abstract_repos.iterable_repository import IterableRepository


class MovieRepository(IterableRepository):
    """Object that manages Movie entities."""


    def __init__(self):
        IterableRepository.__init__(self)
