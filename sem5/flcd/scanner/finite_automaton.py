from os import curdir
from typing import List, Optional, Dict
from copy import deepcopy
import json
import string


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

    def __str__(self):
        return str(self.to_dict())

    __repr__ = __str__

    def to_dict(self) -> Dict[str, str]:
        return {
            "n_id": self.n_id,
            "is_start": self.is_start,
            "is_end": self.is_end,
            "next_nodes": [node.n_id for node in self.next_nodes],
            "edges": deepcopy(self.edges),
        }

    def __eq__(self, o: object) -> bool:
        try:
            return self.n_id == o.n_id
        except:
            return False

    def __hash__(self) -> int:
        return hash(frozenset(self.to_dict()))

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
        for n in nodes:
            if (
                len(set([n2.n_id for n2 in n.next_nodes if n.n_id != n2.n_id]))
                > 1
            ):
                raise ValueError(
                    f"Finite automaton is nondeterministic due to node {n}"
                )

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

    def write_ebnf(self, fn):
        alphabet = [
            n.edges for n in self.start_nodes + self.intermediary_nodes
        ]
        alphabet = set([e for sl in alphabet for e in sl])
        start_nodes = set(deepcopy(self.start_nodes))
        end_nodes = set([n for n in self.intermediary_nodes if n.is_end])
        transitions = [
            f"{n1.n_id} -> {n2.n_id} | {e}"
            for n1 in self.start_nodes + self.intermediary_nodes
            for n2 in n1.next_nodes
            for e in n1.edges
        ]
        with open(fn, "w+") as fp:
            json.dump(
                {
                    "alphabet": [x for x in alphabet],
                    "start_nodes": [n.n_id for n in start_nodes],
                    "end_nodes": [n.n_id for n in end_nodes],
                    "transitions": transitions,
                },
                fp,
                indent=4,
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
#     next_nodes=[node2],
#     is_start=True,
# )
# node3 = AutomatonNode(
#     edges=list(string.ascii_letters), next_nodes=[end], is_start=True
# )
# variable_automaton = FiniteAutomaton(nodes=[node1, node2, node3, end])
# variable_automaton.to_json("automatons/variable_automaton.json")

variable_automaton = FiniteAutomaton.from_json(
    "../automatons/variable_automaton.json"
)
assert variable_automaton.match("a")
assert not variable_automaton.match("")
assert not variable_automaton.match("_dfg")
assert variable_automaton.match("asd_45")
variable_automaton.write_ebnf("../automatons/variable_ebnf")

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
# node5 = AutomatonNode(
#     edges=list("123456789"),
#     next_nodes=[end_2],
#     is_start=True,
#     to_self=True,
# )
# node2 = AutomatonNode(edges=list("+-"), next_nodes=[node3], is_start=True)
# integer_automaton = FiniteAutomaton(
#     nodes=[node1, node2, node3, node4, end_2, node5]
# )
# integer_automaton.to_json("automatons/integer_automaton.json")

integer_automaton = FiniteAutomaton.from_json(
    "../automatons/integer_automaton.json"
)
integer_automaton.write_ebnf("../automatons/integer_ebnf")
assert integer_automaton.match("+122131")
assert integer_automaton.match("4")
assert integer_automaton.match("-123")
assert not integer_automaton.match("-045")
assert not integer_automaton.match("0000")