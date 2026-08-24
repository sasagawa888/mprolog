
%test :-
%    fail;write(2).

test1 :-
    between1(1,10,X),
    write(X),
    fail.

between1(L, H, L) :-
    L =< H.

between1(L, H, X) :-
    L < H,
    L1 is L + 1,
    between1(L1, H, X).

select1(X,[X|Xs],Xs).
select1(X,[Y|Ys],[Y|Zs]) :-
    select1(X,Ys,Zs).


perm1([],[]).
perm1(Xs,[X|Ys]) :-
    select1(X,Xs,Zs),
    perm1(Zs,Ys).
