from typing import List, Dict

from abstract.observer import Observer


class HistoryController(Observer):
    """object that implements the undo/redo features."""


    def __init__(self):
        Observer.__init__(self)

        self.__undo_stack = []
        self.__undo_reserve = []

        self.__redo_stack = []
        self.__redo_reserve = []


    def __apply_change(self, change: Dict):
        """Call the op method of the ref object to modify the state."""

        getattr(change['ref'], change['op'])(change['o'])


    def update(self, message: List[Dict]):
        """Handle state modifications coming from other controllers."""

        self.__undo_stack.append([action['undo'] for action in message])
        self.__redo_stack.append([action['redo'] for action in message])


    def undo(self):
        """Undo the last state modification."""

        try:
            last_undo = self.__undo_stack.pop()
            if self.__redo_reserve != []:
                self.__redo_stack.append(self.__redo_reserve.pop())
            for action in last_undo:
                self.__apply_change(action)
            # If a redo will be applied, this undo must be applied again.
            self.__undo_reserve.append(last_undo)

        except IndexError:
            raise IndexError('No undos available')


    def redo(self):
        """Redo the last state modification."""

        try:
            if self.__undo_reserve != []:
                self.__undo_stack.append(self.__undo_reserve.pop())
            last_redo = self.__redo_stack.pop()
            for action in last_redo:
                self.__apply_change(action)
            # Just as in the comment from the undo function
            self.__redo_reserve.append(last_redo)

        except IndexError:
            raise IndexError('No redos available')
