from repos.repos.client_repository import ClientRepository
import jsonpickle
import os


class JsonClientRepository(ClientRepository):

    def __init__(self):

        self._path = 'storage/clients.json'

        super().__init__()

        if os.stat(self._path).st_size != 0:
            with open(self._path, 'r') as f:
                db = jsonpickle.decode(f.read(), keys=True)
                self._clients = db['objects']
                self._counter = db['counter']


    def __del__(self):

        with open(self._path, 'w') as f:
            db = {
                'objects': self._clients,
                'counter': self._counter,
            }
            f.write(jsonpickle.encode(db))
