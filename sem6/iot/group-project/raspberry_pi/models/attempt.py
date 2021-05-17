from datetime import date


class Attempt:
    def __init__(self):
        self.id = ""
        self.create_date = date.today()
        self.user_id = None
        self.photo_url = ""
