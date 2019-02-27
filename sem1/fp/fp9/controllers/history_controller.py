from typing import List, Dict

from observer.observer import Observer


class HistoryController(Observer):
    """Object that implements the undo/redo features."""


    def __init__(self):
        super().__init__()

        self._undo_stack = []
        self._undo_reserve = []

        self._redo_stack = []
        self._redo_reserve = []


    def _apply_change(self, change: Dict):
        """Call the ref method to modify the state."""

        change['ref'](*change['o'])


    def update(self, message: List[Dict]):
        """Handle state modifications coming from other controllers."""

        self._undo_stack.append([action['undo'] for action in message])
        self._redo_stack.append([action['redo'] for action in message])


    def undo(self):
        """Undo the last state modification."""

        try:
            last_undo = self._undo_stack.pop()
            if self._redo_reserve != []:
                self._redo_stack.append(self._redo_reserve.pop())
            for action in last_undo:
                self._apply_change(action)
            # If a redo will be applied, this undo must be applied again.
            self._undo_reserve.append(last_undo)

        except IndexError:
            raise IndexError('No undos available')


    def redo(self):
        """Redo the last state modification."""

        try:
            if self._undo_reserve != []:
                self._undo_stack.append(self._undo_reserve.pop())
            last_redo = self._redo_stack.pop()
            for action in last_redo:
                self._apply_change(action)
            # Just as in the comment from the undo function
            self._redo_reserve.append(last_redo)

        except IndexError:
            raise IndexError('No redos available')
