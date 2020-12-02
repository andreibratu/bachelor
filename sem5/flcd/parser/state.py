from status_enum import StatusEnum


class State:
    def __init__(self, start_sym):
        self.status = StatusEnum.NORMAL
        self.index = 0
        self.work_stack = []
        self.input_stack = [start_sym]

    def __str__(self):
        work_stack_str = " ".join(s for s in self.work_stack)
        input_stack_str = " ".join(s for s in self.input_stack)

        return (
            "State: " + self.status + "\n"
            "Index: " + str(self.index) + "\n"
            "Work Stack: " + work_stack_str + "\n"
            "Input Stack: " + input_stack_str
        )
