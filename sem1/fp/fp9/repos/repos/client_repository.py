from repos.abstract_repos.iterable_repository import IterableRepository


class ClientRepository(IterableRepository):
    """Object that manages Client entities."""


    def __init__(self):
        IterableRepository.__init__(self)
