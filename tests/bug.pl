mmember(X,[X|_]).
mmember(X,[_|Xs]) :-
    mmember(X,Xs).


nat(0).
nat(s(X)) :- nat(X).

plus(0, Y, Y).
plus(s(X), Y, s(Z)) :- plus(X, Y, Z).

times(0, _, 0).
times(s(X), Y, Z) :- times(X, Y, Z1), plus(Z1, Y, Z).


le(X, Y) :- plus(X, _, Y).

lt(X, Y) :- le(s(X), Y).

quot(X, Y, 0, X) :- lt(X, Y).
quot(X, Y, s(Q), R) :- plus(Y, X1, X), quot(X1, Y, Q, R).


dnd(M, N) :- quot(N, M, _, s(_)).

df(s(0), _).
df(s(s(M)), N) :- dnd(s(s(M)), N), df(s(M), N).

prime(s(X)) :- df(X, s(X)).

mappend([],X,X).
mappend([A|X],Y,[A|Z]) :-
    mappend(X,Y,Z).

apptest :-
    mappend(X,Y,[1,2,3]),
    write(X),
    write(Y),
    fail.

apptest1 :-
    mappend(X,Y,[1,2,3,4,5,6,7,8,9,0]),
    fail.

disj :-
    write(a)
 ;
    write(b).

disjtest :-
    disj,
    fail.

p(1).
p(2).
p(3).

cut(X) :-
    p(X),
    !,
    write(X).

cuttest :- cut(X).

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

bench1 :-
    n(X),
    n(Y),
    n(Z),
    write([X,Y,Z]),nl,
    fail.
bench1.


nodiag([], _, _).
nodiag([N|L], B, D) :-
    D =\= N - B,
    D =\= B - N,
    D1 is D + 1,
    nodiag(L, B, D1).

bar(X) :- write(X).

f(1,Y) :- Y is 2.
f(2,Y) :- Y is 3.

