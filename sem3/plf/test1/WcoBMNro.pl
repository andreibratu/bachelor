% Sum two given numbers as lists

% Sum numbers
% A - List, B - List, R1 - Integer (remainder last op), R2 - List (result)
% flow(i, i, o, o)
sum([], [], 0, []).
sum([A | T], [B | T1], R, [C | T2]) :-
    sum(T, T1, R1, T2),
    C is mod(A+B+R1, 10),
    R is div(A+B+R1, 10).

% Complete smaller numbers with zeroes in front
% flow(i, i, o, o)
completeZeroes([], [], [], []).
completeZeroes(A, B, AO, BO) :-
	length(A, L1), length(B, L2),
    L1 = L2, !,
    AO = A, BO = B.
completeZeroes(A, [B | T], [0 | AO], [B | BO]) :-
    length(A, L1), length([B | T], L2),
    L1 < L2,
    completeZeroes(A, T, AO, BO).
completeZeroes([A | T], B, [A | AO], [0 | BO]) :-
    length([A | T], L1), length(B, L2),
    L1 > L2,
    completeZeroes(T, B, AO, BO).

% Wrapper that adds 1 if sum overflows
% flow(i, i, o)
wrapper(A, B, R) :-
    completeZeroes(A, B, A1, B1),
    sum(A1, B1, R1, R),
    R1 = 0.
wrapper(A, B, [1 | R]) :-
    completeZeroes(A, B, A1, B1),
    sum(A1, B1, R1, R),
    R1 = 1.
