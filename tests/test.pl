% JUMP compiler test code


uoo(X) :- write(X).

/*
:- append([1],[2],X).

bar(1).
bar(2).
*/
:- dynamic(boo/1).
boo(X) :- write(X).

foo(0).
foo(X) :-
    write(X),
    X1 is X - 1,foo(X1).
