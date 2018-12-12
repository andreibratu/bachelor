from repos.abstract_repos.json_repository import JsonRepository
from repos.repos.client_repository import ClientRepository


class JsonClientRepository(ClientRepository, JsonRepository):

    def __init__(self):
        ClientRepository.__init__(self)
        JsonRepository.__init__(self, path='storage/clients.json')
