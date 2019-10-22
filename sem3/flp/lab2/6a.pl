% flow(i, i)
% Check if element E exists in given list
exists(E, [E|_]).
exists(_, []) :- false.
exists(E, [_|T]):-
    exists(E, T).

% flow(i, i)
% Check if given list is a set
isSet([]).
isSet([E|S]) :- not(exists(E, S)),  isSet(S).