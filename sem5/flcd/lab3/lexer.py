import re

from hash_table import HashTable

tokens = HashTable()
reserved_tokens = []
file_input = "pr3"

VARIABLE_RE = r"^[A-Za-z][a-zA-Z\_0-9]{0,}$"
CHAR_RE = r"^\'[A-Za-z0-9\ ]\'$"
NUM_CONST_RE = r"^[-+]?[0-9]*\.?[0-9]+([eE][-+]?[0-9]+)?$"
STR_CONST_RE = r"^\"[a-zA-Z\ 0-9]{0,}\"$"
VALID_PATTERNS = [VARIABLE_RE, NUM_CONST_RE, STR_CONST_RE, CHAR_RE]


with open("token.in", "r") as fp:
    read_tokens = [x for x in fp.read().split("\n") if len(x) != 0]
    for tok in read_tokens:
        reserved_tokens.append(tok)

with open(file_input, "r") as fp:
    content = fp.read().split()

parsed = []
for substr in content:
    extension = [substr]
    # Handle "my_var;" or "int;\n"
    if extension[0][-1] in [":", ";", ","]:
        extension = [substr[:-1], substr[-1]]
    # Array declaration edge case
    if "[" in extension[0] and "]" in extension[0]:
        idx_p_start = extension[0].find("[")
        idx_p_end = extension[0].find("]")

        extension = [
            extension[0][:idx_p_start],
            "[",
            extension[0][idx_p_start + 1 : idx_p_end],
            "]",
            extension[0][idx_p_end + 1 :],
        ] + extension[1:]
    # Next 2 cases handle first and last element from array in-line decl
    # "[4", "5]"
    elif "[" in extension[0]:
        extension = ["[", extension[0][1:]] + extension[1:]
    elif "]" in extension[0]:
        extension = [extension[0][:-1], "]"] + extension[1:]
    parsed.extend(extension)
parsed = [e for e in parsed if len(e) != 0]

print(parsed)

pif, idx = [], 1
for enm, tok in enumerate(parsed):
    if tok in reserved_tokens:
        pif.append((tok, 0))
    else:
        if any([re.match(pattern, tok) for pattern in VALID_PATTERNS]):
            if tokens[tok] is None:
                tokens[tok] = idx
                pif.append((tok, idx))
                idx += 1
            else:
                pif.append((tok, tokens[tok]))
        else:
            print(f"Invalid token {tok} at {enm}!")
            exit(1)

with open("PIF.out", "w+") as fp:
    for tok, idx in pif:
        fp.write(f"{tok} {idx}\n")

with open("ST.out", "w+") as fp:
    fp.write(str(tokens))

print("Lexically correct!")
