"""
Generate all sequences of n parentheses that close correctly.
Example: for n=4 there are two solutions: (()) and ()()
"""


def is_valid(seq):
    """Check if given sequence contains correctly formed paranthesis."""

    p_stack = []
    for c in seq:
        if c == '(':
            p_stack.append('(')
        else:
            if len(p_stack) == 0:
                return False

            if p_stack[-1] != '(':
                return False

            else:
                p_stack.pop()

    return len(p_stack) == 0


def is_consistent(seq):
    """Check if given incomplete sequence can become valid."""

    p_stack = []
    for c in seq:
        if c == '(':
            p_stack.append('(')
        else:
            if len(p_stack) == 0:
                return False

            if p_stack[-1] != '(':
                return False

            else:
                p_stack.pop()

    # Contains only left-paranthesis, check if there are enough
    # characters left to close
    return len(p_stack) <= len(n-seq)


def backtracking(seq):

    if len(seq) == n:
        if is_valid(seq):
            print(seq)
            return

    else:
        if is_consistent(seq):
            backtracking(seq + '(')
            backtracking(seq + ')')


while True:
    n = int(input('Please input the size the sequences: '))
    if n > 0 and n % 2 == 0:
        break
    else:
        continue

backtracking('')
