from repos.repos.client_repository import ClientRepository
import pickle
import os


class PickleClientRepository(ClientRepository):

    def __init__(self):

        self._path = 'storage/clients.txt'

        super().__init__()

        if os.stat(self._path).st_size != 0:
            with open(self._path, 'rb') as f:
                db = pickle.load(f)
                self._clients = db['objects']
                self._counter = db['counter']


    def __del__(self):

        with open(self._path, 'wb') as f:
            db = {
                'objects': self._clients,
                'counter': self._counter
            }
            pickle.dump(db, f)
