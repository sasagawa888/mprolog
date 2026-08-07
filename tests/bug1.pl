n(1).
n(2).
n(3).

bench_count :-
    n(X),
    n(Y),
    write(X-Y),
    nl,
    fail.
bench_count.


foo(X) :- write(X).

bar(X) :- n(X),foo(X).

last([],[]).
last([X],X).
last([X|Xs],Y) :-
    last(Xs,Y).

butlast([],[]).
butlast([X],[]).
butlast([X|Xs],[X|Y]) :-
    butlast(Xs,Y).

cons(X,[],[X]).
cons(X,Y,[X|Y]).

second([],[]).
second([_,X|_],X).

nth(N,[],[]).
nth(1,[X|Xs],X).
nth(N,[X|Xs],Y) :-
    N1 is N-1,
    nth(N1,Xs,Y).

nth0(N,[],[]).
nth0(0,[X|Xs],X).
nth0(N,[X|Xs],Y) :-
    N1 is N-1,
    nth0(N1,Xs,Y).

iota(S,S,[S]).
iota(S,E,[S|L]) :-
    S1 is S+1,
    iota(S1,E,L).
