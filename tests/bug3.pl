
mappend([],X,X).
mappend([A|X],Y,[A|Z]) :-
    mappend(X,Y,Z).

reverse([],[]).
reverse([X|Xs],Y) :-
    reverse(Xs,Y1),
    mappend(Y1,[X],Y).