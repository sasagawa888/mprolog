mappend([],X,X).
mappend([A|X],Y,[A|Z]) :-
    mappend(X,Y,Z).
