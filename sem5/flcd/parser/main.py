import os

from grammar import Grammar
from parser import recursive_descent

grammar_path = os.path.join(os.getcwd(), "g2.txt")

grammar = Grammar.from_file(grammar_path)
print(grammar)
print("######")

# G1 grammar
with open("input.txt", "r") as fp:
    inp = fp.readline().strip().split(" ")

# G2 grammar
with open("PIF-input.out", "r") as fp:
    lines = fp.readlines()
    lines = [line.strip().split(" ") for line in lines]
    lines = [line[0] for line in lines]
    inp = lines

print("#### INPUT ####")
print(inp)
print("######")

rules = recursive_descent(grammar, inp)
print(rules)
