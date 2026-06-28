
p(1).
p(2).
p(3).

q(5).
q(6).

r(X,Y) :- p(X),q(Y).


mappend([],X,X).
mappend([A|X],Y,[A|Z]) :-
    mappend(X,Y,Z).

