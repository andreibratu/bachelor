from repos.abstract_repos.pickle_repository import PickleRepository
from repos.repos.client_repository import ClientRepository


class PickleClientRepository(ClientRepository, PickleRepository):
    """Pickle implementation of the Client repository."""


    def __init__(self):
        ClientRepository.__init__(self)
        PickleRepository.__init__(self, path='storage/clients.txt')
