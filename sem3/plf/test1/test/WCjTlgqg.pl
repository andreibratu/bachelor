% flow(i, o)
% L (i) - Input list
% O (o) - Minimum value in list
minValue([], _) :- false.
minValue([A], A).
minValue([A | T], A) :-
    minValue(T, B),
    A =< B.
minValue([A | T], B) :-
    minValue(T, B),
    A > B.

% flow(i, i, o)
% L  (i) - Input list
% E  (i) - Value to filter
% L' (o) - Filtered list
filterValue([], _, []).
filterValue([A | T], A, R) :-
    filterValue(T, A, R).
filterValue([A | T], B, [A | R]) :-
    not(A = B),
    filterValue(T, B, R).

% flow(i, o)
% L  (i) - Input list
% L' (o) - List with minimum value filtered
filterMinimum([], []).
filterMinimum(A, R) :-
    minValue(A, M),
    filterValue(A, M, R).