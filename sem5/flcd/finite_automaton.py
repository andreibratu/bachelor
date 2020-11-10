from os import curdir
from typing import List, Optional, Dict
from copy import deepcopy
import json


class AutomatonNode:

    curr_id = 0

    def __init__(
        self,
        edges: List[str],
        next_nodes: List["AutomatonNode"],
        n_id: Optional[int] = None,
        is_end: bool = False,
        is_start: bool = False,
        to_self: bool = False,
    ):
        self.edges = edges
        self.next_nodes = next_nodes
        self.is_end = is_end
        self.is_start = is_start
        if n_id is None:
            # Not read from file, issue an n_id for it
            self.n_id = AutomatonNode.curr_id
            AutomatonNode.curr_id += 1
        else:
            self.n_id = n_id
        if to_self:
            self.next_nodes.append(self)

    def matches(self, attempt: str) -> bool:
        return attempt[0] in self.edges

    def isEndNode(self) -> bool:
        return self.is_end

    def to_dict(self) -> Dict[str, str]:
        return {
            "n_id": self.n_id,
            "is_start": self.is_start,
            "is_end": self.is_end,
            "next_nodes": [node.n_id for node in self.next_nodes],
            "edges": deepcopy(self.edges),
        }

    @staticmethod
    def from_dict(dict_rep) -> "AutomatonNode":
        AutomatonNode.curr_id = max(
            AutomatonNode.curr_id, dict_rep["n_id"] + 1
        )
        return AutomatonNode(
            edges=dict_rep["edges"],
            next_nodes=dict_rep["next_nodes"],
            n_id=dict_rep["n_id"],
            is_start=dict_rep["is_start"],
            is_end=dict_rep["is_end"],
        )


class FiniteAutomaton:
    def __init__(self, nodes: List[AutomatonNode]):
        self.start_nodes = [n for n in nodes if n.is_start]
        self.intermediary_nodes = [
            n for n in nodes if not n.is_start or not n.is_end
        ]

    def _match_subalg(self, match_str: str, node: AutomatonNode) -> bool:
        if len(match_str) == 0:
            return node.is_end
        if not node.matches(match_str):
            return False
        return any(
            [
                self._match_subalg(match_str[1:], neigh)
                for neigh in node.next_nodes
            ]
        )

    def match(self, match_str: str) -> bool:
        return any(
            [
                self._match_subalg(match_str, start_n)
                for start_n in self.start_nodes
            ]
        )

    def to_json(self, fn: str):
        lists = [self.start_nodes, self.intermediary_nodes]
        json_nodes = [node.to_dict() for subl in lists for node in subl]

        with open(fn, "w+") as fp:
            json.dump(json_nodes, fp, indent=4, sort_keys=True)

    @staticmethod
    def from_json(fn: str) -> "FiniteAutomaton":
        with open(fn, "r") as fp:
            nodes = json.load(fp)
        nodes = [AutomatonNode.from_dict(n_repr) for n_repr in nodes]
        for n in nodes:
            # For each node, replace ids of its next_nodes with ref to obj
            n.next_nodes = [
                neigh for neigh in nodes if neigh.n_id in n.next_nodes
            ]
        return FiniteAutomaton(nodes=nodes)


# end = AutomatonNode(edges=[], next_nodes=[], is_end=True)
# node2 = AutomatonNode(
#     edges=list(string.ascii_letters) + list(string.digits) + ["_"],
#     next_nodes=[end],
#     to_self=True,
# )
# node1 = AutomatonNode(
#     edges=list(string.ascii_letters),
#     next_nodes=[end, node2],
#     is_start=True,
# )
# variable_automaton = FiniteAutomaton(nodes=[node1, node2, end])
# variable_automaton.to_json("variable_automaton.json")

variable_automaton = FiniteAutomaton.from_json("variable_automaton.json")
print("VARIABLE")
print(variable_automaton.match("a"))
print(variable_automaton.match(""))
print(variable_automaton.match("_dfg"))
print(variable_automaton.match("asd_45"))

# end_2 = AutomatonNode(edges=[], next_nodes=[], is_end=True)
# node1 = AutomatonNode(edges=["0"], next_nodes=[end_2], is_start=True)
# node4 = AutomatonNode(
#     edges=list("0123456789"), next_nodes=[end_2], to_self=True
# )
# node3 = AutomatonNode(
#     edges=list("123456789"),
#     next_nodes=[node4],
#     is_start=True,
#     to_self=True,
# )
# node2 = AutomatonNode(edges=list("+-"), next_nodes=[node3], is_start=True)
# integer_automaton = FiniteAutomaton(nodes=[node1, node2, node3, node4, end_2])
# integer_automaton.to_json("integer_automaton.json")

integer_automaton = FiniteAutomaton.from_json("integer_automaton.json")
print("\n\nINTEGER")
print(integer_automaton.match("+122131"))
print(integer_automaton.match("0"))
print(integer_automaton.match("-123"))
print(integer_automaton.match("-045"))
print(integer_automaton.match("0000"))