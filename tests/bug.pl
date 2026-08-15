mbetween(X,Y,X) :-
    X =< Y.
mbetween(X,Y,Z) :-
    X < Y,
    A is X + 1,
    mbetween(A,Y,Z).

