class Movie:
    """Class that describes the Movie entity."""

    def __init__(self, title: str, description: str, genre: str, id=None):
        if id is not None:
            self.id = id
        self.title = title
        self.description = description
        self.genre = genre


    def update(self, title: str, description: str, genre: str):
        self.title = title
        self.description = description
        self.genre = genre


    def __str__(self):
        return ' -- '.join((
            str(self.id),
            self.title,
            self.description,
            self.genre)
        )

    __repr__ = __str__
