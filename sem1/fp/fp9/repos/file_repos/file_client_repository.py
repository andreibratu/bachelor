from entities.file_manager import FileManager

from repos.abstract_repos.file_repository import FileRepository
from repos.repos.client_repository import ClientRepository


class FileClientRepository(ClientRepository, FileRepository):
    """Pickle implementation of the Client repository."""


    def __init__(self, file_manager: FileManager):
        path = 'storage/clients.txt' \
               if file_manager.type == 'pickle' else 'storage/clients.json'
        ClientRepository.__init__(self)
        FileRepository.__init__(
            self,
            file_manager=file_manager,
            path=path
        )
