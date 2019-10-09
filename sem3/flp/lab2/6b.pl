countOccurences(_, [], 0).
countOccurences(H, [H|T], N) :- countOccurences(H, T, N1), N is N1 + 1.
countOccurences(E, [_|T], N) :- countOccurences(E, T, N).

removeInstances(_, [], []).
removeInstances(X, [X|T], S) :- removeInstances(X, T, S).
removeInstances(X, [U|T], [U|S]) :- removeInstances(X, T, S).

removeKInstances(_, [], _, 0).
removeKInstances(X, [X|T], [X|S], 0) :- removeKInstances(X, T, S, 0).
removeKInstances(X, [X|T], S, N) :- removeKInstances(X, T, S, N1), N is N1+1.
removeKInstances(X, [U|T], [U|S], N) :- removeKInstances(X, T, S, N).


