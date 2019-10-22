% flow(i, i, o, i)
removeKInstances(_, [], [], _).
removeKInstances(X, [X|T], [X|S], 0) :- removeKInstances(X, T, S, 0).
removeKInstances(X, [X|T], S, N) :- N1 is N-1, removeKInstances(X, T, S, N1).
removeKInstances(X, [U|T], [U|S], N) :- removeKInstances(X, T, S, N).


