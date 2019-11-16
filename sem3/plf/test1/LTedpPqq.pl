%  Define a predicate to determine the longest sequences of consecutive even numbers (if exist more maximal
sequences one of them). 

% % flow(i, i) Check if 2nd list is a prefix of first
% flow(i, o) Generate prefixes of 1st list
prefix(_, []).
prefix([X|Xs], [X|Ys]) :- prefix(Xs, Ys).

% flow (i, o)
% Generate continuous subsequences of input list
subseq([], []).
subseq([_|Xs], Ys) :- subseq(Xs, Ys).
subseq([X|Xs], [X|Ys]) :- prefix(Xs, Ys).

% flow (i)
% Check that a list contains only conescutive even numbers
evenConsecutive([]).
evenConsecutive([A]) :- 0 is mod(A, 2).
evenConsecutive([A, B | T]) :-
   0 is mod(A, 2), A is B - 2,
   evenConsecutive([B | T]).

% flow(i, o)
% Filter sublists by evenConsecutive predicate
filter([], []).
filter([A | T], [A | T1]) :- evenConsecutive(A), filter(T, T1).
filter([_ | T], R) :- filter(T, R).

% flow(i, o, o)
% Find the length and the longest sublist from list
% If multiple, return first
longestSublist([], 0, []).
longestSublist([A | T], R, A) :-
    longestSublist(T, R2, _),
    length(A, R), R >= R2.
longestSublist([A | T], R1, R2) :-
    longestSublist(T, R1, R2),
    length(A, R3), R1 > R3.

% flow (i, o)
% Solving problem wrapper
wrapper(A, R) :-
    findall(R1, subseq(A, R1), R2),
    filter(R2, R3),
    longestSublist(R3, _, R).