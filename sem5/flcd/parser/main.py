import os

from grammar import Grammar
from parser import recursive_descent

grammar_path = os.path.join(os.getcwd(), "g2.txt")

grammar = Grammar.from_file(grammar_path)
print(grammar)

with open("input.txt", "r") as fp:
    input = fp.readline().strip().split(" ")

with open("PIF.out", "r") as fp:
    lines = fp.readlines()
    lines = [line.strip().split(" ") for line in lines]
    inp = ' '.join([line[0] for line in lines])

print(inp)

rules = recursive_descent(grammar, inp)
print(rules)
