
qsort([], []).
qsort([Pivot|Rest], Sorted) :-
    partition(Pivot, Rest, Left, Right), 
    qsort(Left, SortedLeft),          
    qsort(Right, SortedRight),       
    append(SortedLeft, [Pivot|SortedRight], Sorted). 

partition(_, [], [], []). 
partition(Pivot, [H|T], [H|Left], Right) :-
    H =< Pivot,  
    partition(Pivot, T, Left, Right).
partition(Pivot, [H|T], Left, [H|Right]) :-
    H > Pivot,  
    partition(Pivot, T, Left, Right).

permutation([], []).
permutation(L, [X|L2]) :-
    del(X, L, L1),
    permutation(L1, L2).

del(X, [X|L], L).
del(X, [Y|L], [Y|L1]) :-
    del(X, L, L1).

flatten([],[]).
flatten([L|Ls],[L|Y]) :-
    atomic(L),
    flatten(Ls,Y).
flatten([L|Ls],Z) :-
    list(L),
    flatten(L,Y1),
    flatten(Ls,Y2),
    append(Y1,Y2,Z).

min_list([L],L).
min_list([L|Ls],L) :-
    min_list(Ls,X),
    L < X.
min_list([L|Ls],X) :-
    min_list(Ls,X),
    L >= X.

max_list([L],L).
max_list([L|Ls],L) :-
    max_list(Ls,X),
    L > X.
max_list([L|Ls],X) :-
    max_list(Ls,X),
    L =< X.

same_set(L1,L2) :-
    sort(L1,S1),
    sort(L2,S2),
    S1 = S2.


mappend([],X,X).
mappend([A|X],Y,[A|Z]) :-
    mappend(X,Y,Z).


apptest :-
    mappend(X,Y,[1,2,3]),
    write(X),
    write(Y),
    fail.



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

apptest1 :-
    mappend(X,Y,[1,2,3,4,5,6,7,8,9,0]),
    fail.

