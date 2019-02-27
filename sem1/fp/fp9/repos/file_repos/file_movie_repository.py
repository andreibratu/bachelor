from entities.file_manager import FileManager

from repos.abstract_repos.file_repository import FileRepository
from repos.repos.movie_repository import MovieRepository


class FileMovieRepository(MovieRepository, FileRepository):
    """Pickle implementation of the MovieRepository."""

    def __init__(self, file_manager: FileManager):
        path = 'storage/movies.txt' \
               if file_manager.type == 'pickle' else 'storage/movies.json'
        MovieRepository.__init__(self)
        FileRepository.__init__(
            self,
            path=path,
            file_manager=file_manager
        )
