% JUMP compiler test code

/*
foo(X) :- write(X).

:- append([1],[2],X).

bar(1).
bar(2).
*/
:- dynamic(boo/1).
boo(X) :- write(X).
