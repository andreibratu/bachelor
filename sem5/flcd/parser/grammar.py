from production import Production
from typing import Dict
from collections import defaultdict


class Grammar:
    def __init__(self, start_symbol, terminals, non_terminals, productions):
        self.start_symbol = start_symbol
        self.terminals = terminals
        self.non_terminals = non_terminals
        self.productions = productions

    def get_productions(self):
        prods = defaultdict(list)
        for p in self.productions:
            prods[p.left_term].append(" ".join(p.right_term))
        return prods

    def get_productions_of(self, symbol):
        return list(filter(lambda x: x.left_term == symbol, self.productions))

    def is_terminal(self, symbol):
        return symbol in self.terminals

    def is_non_terminal(self, symbol):
        return symbol in self.non_terminals

    def __str__(self):
        string_prod = "\n".join([str(p) for p in self.productions])
        string_term = " ".join([term for term in self.terminals])
        string_non_term = " ".join([non_term for non_term in self.terminals])

        return (
            "Start symbol: " + self.start_symbol + "\n"
            "Terminals: " + string_term + "\n"
            "Non-terminals: " + string_non_term + "\n"
            "Productions:\n" + string_prod
        )

    @staticmethod
    def __check_cycle(graph: Dict):
        print(graph)
        seen = {}
        try:
            start_node = list(graph.keys())[0]
        except IndexError:
            # The graph is empty i.e. no dependencies between non-terminals
            return
        dfs_stack = [start_node]
        while len(dfs_stack) != 0:
            curr_node = dfs_stack.pop()
            seen[curr_node] = True
            for neigh in graph[curr_node]:
                if neigh in seen and seen[neigh]:
                    raise ValueError("Grammar is left recursive!")
                dfs_stack.append(neigh)

    @staticmethod
    def from_file(filename):
        dep_graph = defaultdict(list)
        with open(filename) as fp:
            non_terminals = fp.readline().rstrip().split(" ")
            terminals = fp.readline().rstrip().split(" ")
            start_sym = fp.readline().rstrip()
            productions = []
            line = fp.readline().rstrip()
            while line:
                line = line.split(" ")
                lhs = line[0]
                rhs = line[1].split("@")
                if rhs[0] in non_terminals:
                    try:
                        neighbours = list(dep_graph[lhs])
                    except KeyError:
                        neighbours = []
                    neighbours.append(rhs[0])
                    dep_graph[lhs] = tuple(neighbours)
                productions.append(Production(line[0], line[1].split("@")))
                line = fp.readline().rstrip()
        print(dep_graph)
        Grammar.__check_cycle(dep_graph)
        return Grammar(start_sym, terminals, non_terminals, productions)
