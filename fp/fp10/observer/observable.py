class Observable:
    """Abstract class implementation of Observable side of the pattern."""

    def __init__(self):
        self.__observers = set()


    def subscribe(self, observer):
        self.__observers.add(observer)


    def unsubscribe(self, observer):
        self.__observers.discard(observer)


    def notify(self, message):
        for o in self.__observers:
            o.update(message)
