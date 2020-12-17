from re import match
from finite_automaton import FiniteAutomaton
import re
import os

from hash_table import HashTable

reserved_tokens = []
file_input = "../language/pr2"

CHAR_RE = r"^\'[A-Za-z0-9\ ]\'$"
DOUBLE_CONST_RE = r"^([+-]?(0|[1-9][0-9]*)\.[0-9]+)$"
STR_CONST_RE = r"^\"[a-zA-Z\ 0-9]{0,}\"$"
VALID_PATTERNS = [DOUBLE_CONST_RE, STR_CONST_RE, CHAR_RE]
INT_AUTOMATON = FiniteAutomaton.from_json(
    "../automatons/integer_automaton.json"
)
VARIABLE_AUTOMATON = FiniteAutomaton.from_json(
    "../automatons/variable_automaton.json"
)
VALID_AUTOMATONS = [INT_AUTOMATON, VARIABLE_AUTOMATON]

if os.path.exists("ST.out"):
    os.remove("ST.out")
if os.path.exists("../parser/PIF.out"):
    os.remove("../parser/PIF.out")
if os.path.exists("../parser/PIF-input.out"):
    os.remove("../parser/PIF-input.out")

with open("../language/token.in", "r") as fp:
    read_tokens = [x for x in fp.read().split("\n") if len(x) != 0]
    for tok in read_tokens:
        reserved_tokens.append(tok)

with open(file_input, "r") as fp:
    content = fp.read()


curr_token, tokens = "", []
stoppers = [":", "[", "]", "<", ";", "(", ")", ",", "/", "%", "+", "-"]
white_space = ["\n", " ", "\t"]
it = iter(content)
line, pos = 0, 0
while True:
    try:
        pos += 1
        cr = next(it)
        if cr in white_space:
            if cr == "\n":
                line += 1
                pos = 0
            tokens.append((line, pos, curr_token))
            curr_token = ""
            continue
        elif cr in stoppers:
            if curr_token != "":
                tokens.append((line, pos - 1, curr_token))
            tokens.append((line, pos, cr))
            curr_token = ""
        else:
            curr_token += cr
    except StopIteration:
        break
if curr_token != "":
    tokens.append((line, pos, curr_token))
tokens = [tok for tok in tokens if tok[2] != ""]

final_tokens = []
idx = 0
while idx < len(tokens):
    try:
        x, y = tokens[idx], tokens[idx + 1]
        print(x[2], y[2])
        if x[2] in ["+", "-", "/", "%", "//"] and y[2] in ["+", "-"]:
            print("1")
            final_tokens.append((x[0], x[1], x[2]))
            idx += 1
            continue
        if x[2] == "<" and y[2] == "-":
            print("2")
            final_tokens.append((x[0], y[1], "<-"))
            idx += 2
            continue
        elif x[2] in ["-", "+"] and (
            INT_AUTOMATON.match(y[2]) or re.match(DOUBLE_CONST_RE, y[2])
        ):
            print("3")
            final_tokens.extend([x, y])
            idx += 2
        else:
            print("4")
            final_tokens.append(x)
            idx += 1
    except IndexError:
        final_tokens.append(y)
        break

print([tok[2] for tok in final_tokens])
pif = []
table = HashTable()
idx = 1
for enm, tok_tuple in enumerate(final_tokens):
    tok = tok_tuple[2]
    if tok in reserved_tokens:
        pif.append((tok, 0))
    else:
        if any([re.match(pattern, tok) for pattern in VALID_PATTERNS]) or any(
            [automaton.match(tok) for automaton in VALID_AUTOMATONS]
        ):
            if table[tok] is None:
                table[tok] = idx
                pif.append((tok, idx))
                idx += 1
            else:
                pif.append((tok, table[tok]))
        else:
            print(
                f"Invalid token {tok} at line {tok_tuple[0]+1} position {tok_tuple[1]}!"
            )
            exit(1)

with open("../parser/PIF.out", "w+") as fp:
    for tok, idx in pif:
        fp.write(f"{tok} {idx}\n")


with open("../parser/PIF-input.out", "w+") as fp:
    for tok, idx in pif:
        if tok in reserved_tokens:
            fp.write(f"{tok} {idx}\n")
            continue
        if VARIABLE_AUTOMATON.match(tok):
            fp.write(f"identifier {idx}\n")
        elif re.match(CHAR_RE, tok):
            fp.write(f"charconst {idx}\n")
        elif re.match(STR_CONST_RE, tok):
            fp.write(f"strconst {idx}\n")
        elif re.match(DOUBLE_CONST_RE, tok):
            fp.write(f"doubleconst {idx}\n")
        elif INT_AUTOMATON.match(tok):
            fp.write(f"intconst {idx}\n")

with open("ST.out", "w+") as fp:
    fp.write(str(table))


print("Lexically correct!")
