class User:
    COORDINATES_FIELD = "coordinates"
    CREATED_AT_FIELD = "createdAt"
    ID_FIELD = "id"
    PHOTO_URL = "photoUrl"

    def __init__(self):
        self.id = ""
        self.coordinates = None
        self.photoUrl = ""
        self.createdAt = ""

    @staticmethod
    def create_from(obj):
        user = User()

        if User.COORDINATES_FIELD in obj:
            user.coordinates = obj[User.COORDINATES_FIELD]

        if User.CREATED_AT_FIELD in obj:
            user.createdAt = obj[User.CREATED_AT_FIELD]

        if User.ID_FIELD in obj:
            user.id = obj[User.ID_FIELD]

        if User.PHOTO_URL in obj:
            user.photoUrl = obj[User.PHOTO_URL]

        return user
