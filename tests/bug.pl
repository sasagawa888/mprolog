
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
