import os

from grammar import Grammar
from parser import recursive_descent

grammar_path = os.path.join(os.getcwd(), "g1.txt")

grammar = Grammar.from_file(grammar_path)
print(grammar)

with open("input.txt", "r") as fp:
    input = fp.readline().strip().split(" ")

print(input)

rules = recursive_descent(grammar, input)
print(rules)