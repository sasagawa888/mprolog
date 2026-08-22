
test :-
    write(1);write(2).


select1(X,[X|Xs],Xs).
select1(X,[Y|Ys],[Y|Zs]) :-
    select1(X,Ys,Zs).


perm1([],[]).
perm1(Xs,[X|Ys]) :-
    select1(X,Xs,Zs),
    perm1(Zs,Ys).
