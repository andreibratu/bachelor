from state import State
from production import Production
from status_enum import StatusEnum


def get_next_production(prod, productions):
    for i in range(len(productions)):
        if prod == productions[i] and i < len(productions) - 1:
            return productions[i + 1]
    return None


def recursive_descent(grammar, sequence):
    state = State(grammar.start_symbol)
    while (
        state.status != StatusEnum.FINAL and state.status != StatusEnum.ERROR
    ):
        if state.status == StatusEnum.NORMAL:
            if len(state.input_stack) == 0 and state.index == len(sequence):
                state.status = StatusEnum.FINAL
            elif len(state.input_stack) == 0:
                state.status = StatusEnum.BACK
            else:
                if state.input_stack[0] in grammar.non_terminals:
                    non_term = state.input_stack[0]
                    first_prod = grammar.get_productions_of(non_term)[0]
                    state.work_stack.append(
                        (
                            first_prod.left_term,
                            first_prod.right_term,
                        )
                    )
                    state.input_stack = (
                        first_prod.right_term + state.input_stack[1:]
                    )
                else:
                    if state.index == len(sequence):
                        state.status = StatusEnum.BACK
                    elif state.input_stack[0] == "e":
                        state.work_stack.append("e")
                        state.input_stack = state.input_stack[1:]
                    elif state.input_stack[0] == sequence[state.index]:
                        state.index += 1
                        state.work_stack.append(state.input_stack[0])
                        state.input_stack = state.input_stack[1:]
                    else:
                        state.status = StatusEnum.BACK
        else:
            if state.status == StatusEnum.BACK:
                if state.work_stack[-1] in grammar.terminals:
                    if state.work_stack[-1] == "e":
                        state.work_stack.pop(-1)
                    else:
                        state.index -= 1
                        terminal = state.work_stack.pop(-1)
                        state.input_stack = [terminal] + state.input_stack
                else:
                    last_production = state.work_stack[-1]
                    productions = grammar.get_productions_of(
                        last_production[0]
                    )
                    productions = [
                        (prod.left_term, prod.right_term)
                        for prod in productions
                    ]
                    next_prod = get_next_production(
                        last_production, productions
                    )
                    if next_prod:
                        state.status = StatusEnum.NORMAL
                        state.work_stack.pop(-1)
                        state.work_stack.append((next_prod[0], next_prod[1]))
                        state.input_stack = state.input_stack[
                            len(last_production[1]) :
                        ]
                        state.input_stack = next_prod[1] + state.input_stack
                    elif (
                        state.index == 0
                        and last_production[0] == grammar.start_symbol
                    ):
                        state.status = StatusEnum.ERROR
                    else:
                        state.work_stack.pop(-1)
                        if last_production[1] == ["e"]:
                            state.input_stack = [
                                last_production[0]
                            ] + state.input_stack
                        else:
                            state.input_stack = [
                                last_production[0]
                            ] + state.input_stack[len(last_production[1]) :]
    production_rules = []
    if state.status == StatusEnum.ERROR:
        raise ValueError()
    else:
        for prod in state.work_stack:
            if len(prod) > 1:
                if Production(prod[0], prod[1]) in grammar.productions:
                    production_rules.append(prod)

    return production_rules
