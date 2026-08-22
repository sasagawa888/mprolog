
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

prime(s(X)) :- df(X, s(X)).

df(s(0), _).
df(s(s(M)), N) :- dnd(s(s(M)), N), df(s(M), N).

dnd(M, N) :- quot(N, M, _, s(_)).



mbetween(Low, High, Low) :-
    Low =< High.

mbetween(Low, High, X) :-
    Low < High,
    Low1 is Low + 1,
    mbetween(Low1, High, X).

select1(X,[X|Xs],Xs).
select1(X,[Y|Ys],[Y|Zs]) :-
    select1(X,Ys,Zs).


perm1([],[]).
perm1(Xs,[X|Ys]) :-
    select1(X,Xs,Zs),
    perm1(Zs,Ys).
