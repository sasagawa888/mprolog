

p(1).
p(2).


foo :- p(X),p(Y),write(X),write(Y),fail.
foo.


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

fact(0, 1).
fact(X, Sum) :-
    X > 0, X1 is X - 1, fact(X1, Sum1), Sum is X * Sum1. 
