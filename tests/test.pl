% JUMP compiler test code

test(L) :-
    bagof(P,type(P,_,recur),L),write(L).

type(a,1,recur).
type(b,2,recur).
type(c,3,recur).


uoo(X) :- write(X).

bar(1).
bar(2).

:- dynamic(boo/1).
boo(X) :- write(X).

foo(0).
foo(X) :-
    write(X),
    X1 is X - 1,foo(X1).
