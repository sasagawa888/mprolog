
make_list(0,X,[]).
make_list(N,X,[X|Y]) :-
    N1 is N-1,
    make_list(N1,X,Y).

reverse([],[]).
reverse([X|Xs],Y) :-
    reverse(Xs,Y1),
    append(Y1,[X],Y).

remove_at(0,[X|Xs],Xs).
remove_at(N,[X|Xs],[X|Y]) :-
    N1 is N-1,
    remove_at(N1,Xs,Y).

insert_at(0,X,L,[X|L]).
insert_at(N,X,[L|Ls],[L|Y]) :-
    N1 is N-1,
    insert_at(N1,X,Ls,Y).

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



primetest :-
    prime(s(s(s(s(s(s(s(s(s(s(s(0)))))))))))).

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


f(1,Y) :- Y is 2.
f(2,Y) :- Y is 3.


