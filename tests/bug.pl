


plus(0, Y, Y).
plus(s(X), Y, s(Z)) :- plus(X, Y, Z).


times(0, _, 0).
times(s(X), Y, Z) :- times(X, Y, Z1), plus(Z1, Y, Z).



color(red).
color(green).
color(blue).


mappend([],X,X).
mappend([A|X],Y,[A|Z]) :-
    mappend(X,Y,Z).


n(1). n(2). n(3). n(4). n(5).
n(6). n(7). n(8). n(9). n(10).
bench :-
    n(X),
    n(Y),
    n(Z),
    n(A),
    n(B),
    fail.
bench.


nat(0).
nat(s(X)) :- nat(X).


le(X, Y) :- plus(X, _, Y).

lt(X, Y) :- le(s(X), Y).


quot(X, Y, 0, X) :- lt(X, Y).
quot(X, Y, s(Q), R) :- plus(Y, X1, X), quot(X1, Y, Q, R).


dnd(M, N) :- quot(N, M, _, s(_)).

df(s(0), _).
df(s(s(M)), N) :- dnd(s(s(M)), N), df(s(M), N).

prime(s(X)) :- df(X, s(X)).

foo(X,Y,Z) :- plus(X,Y,Z).

apptest :-
    mappend(X,Y,[1,2,3]),
    write(X),
    write(Y),
    fail.



apptest1 :-
    mappend(X,Y,[1,2,3,4,5,6,7,8,9,0]),
    fail.



likes(kim,robin).
likes(sandy,lee).
likes(sandy,kim).
likes(robin,cats).
likes(sandy,X) :- likes(X,cats).
likes(kim,X) :- likes(X,lee),likes(X,kim).
likes(X,X).



nodiag([], _, _).
nodiag([N|L], B, D) :-
    D =\= N - B,
    D =\= B - N,
    D1 is D + 1,
    nodiag(L, B, D1).

