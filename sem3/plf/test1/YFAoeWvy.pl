% Replace all occurences of A in given list with elements of L
% flow(i, i, o)
replace([], _, _, []).
replace([A | T], L, A, R) :-
    replace(T, L, A, R1),
    append(L, R1, R).
replace([B | T], L, A, [B | R]) :-
    replace(T, L, A, R).