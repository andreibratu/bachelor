% flow(i, o)
% Remove all sequences of consecutive values from list

rem_seq([], []):-!.

rem_seq([H1, H2], R) :-
    H2 is H1 + 1, !,
    rem_seq([], R).

rem_seq([H1, H2, H3 | T], R) :-
    H2 is H1 + 1,
    not(H3 is H2 + 1), !,
    rem_seq([H3 | T], R).

rem_seq([H1, H2 | T], R) :-
    H2 is H1+1, !,
    rem_seq([H2 | T], R).

rem_seq([H | T], [H | R]):-
    rem_seq(T, R).


% flow(i, o)
% Remove sequences of conescutive values from sublists, return the list

rem_seq_list([], []) :- !.

rem_seq_list([H | T], [H | R]) :-
    not(is_list(H)),
    rem_seq_list(T, R).

rem_seq_list([H | T], [E | R]) :-
	  rem_seq(H, E),
    rem_seq_list(T, R).
