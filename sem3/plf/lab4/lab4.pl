% Find all increasing sublists from list
% flow(i, o)
inc_sublist([], []).
inc_sublist([A | T], [A]) :-
    inc_sublist(T, []).
inc_sublist([A | T], [A, B | T1]) :-
    inc_sublist(T, [B | T1]),
    A < B.
inc_sublist([_ | T], T1) :-
    inc_sublist(T, T1).
