
mappend([],X,X).
mappend([A|X],Y,[A|Z]) :-
    mappend(X,Y,Z).

apptest :-
    mappend(X,Y,[1,2,3]),
    write(X),
    write(Y),
    fail.


disj :-
    write(a)
 ;
    write(b).

disjfail :-
    disj,
    fail.

p(1).
p(2).
p(3).

cut(X) :-
    p(X),
    !,
    write(X).


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

