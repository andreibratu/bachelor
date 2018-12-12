from entities.file_manager import FileManager

from repos.abstract_repos.file_repository import FileRepository
from repos.repos.rental_repository import RentalRepository


class FileRentalRepository(RentalRepository, FileRepository):

    def __init__(self, file_manager: FileManager):
        path = 'storage/rentals.txt' \
               if file_manager.type == 'pickle' else 'storage/rentals.json'
        RentalRepository.__init__(self)
        FileRepository.__init__(
            self,
            path=path,
            file_manager=file_manager,
            extra_args=['_movie_stats_days', '_movie_stats_times']
        )
