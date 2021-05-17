import threading


class UsersManager:
    def __init__(self):
        self.mutex = threading.Lock()
        self.users = []

    def get_users(self):
        self.mutex.acquire()
        copy_of_list = self.users.copy()
        self.mutex.release()

        return copy_of_list

    def add_user(self, user):
        self.mutex.acquire()
        self.users.append(user)
        self.mutex.release()

    def set_users(self, users):
        self.mutex.acquire()
        self.users = users
        self.mutex.release()

