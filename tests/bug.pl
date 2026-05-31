

p(1).
p(2).


foo :- p(X),write(X),fail.
foo.

n(1). n(2). n(3). n(4). n(5).
n(6). n(7). n(8). n(9). n(10).

bench :-
    n(X),
    fail.
bench.

bench1 :-
    n(X),
    n(Y),
    n(Z),
    write([X,Y,Z]),nl,
    fail.
bench1.