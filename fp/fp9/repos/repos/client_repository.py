from repos.repos.repository import AbstractRepository


class ClientRepository(AbstractRepository):
    """Object that manages Client entities."""


    def __init__(self):
        super().__init__()
