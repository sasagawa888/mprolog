
p(1).
p(2).
p(3).


mappend([],X,X).
mappend([A|X],Y,[A|Z]) :-
    mappend(X,Y,Z).
