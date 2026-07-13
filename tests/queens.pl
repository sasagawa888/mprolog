% 9-queens program

skip_test(X,Y) :-
    qdelete(X,1,[2,4],Y),
    nodiag([2,4],X,1).

test16 :- between(1,16,X),test1,fail.
test :- queen([1,2,3,4,5,6,7,8,9],X),write(X),nl,fail.
test1 :- queen([1,2,3,4,5,6,7,8,9],X),fail.


queen(Data, Out) :-
    queen_2(Data, [], Out).

queen_2([], _, []).
queen_2([H|T], History, [Q|M]) :-
    write([H|T]),
    qdelete(Q, H, T, L1),
    nodiag(History, Q, 1),
    queen_2(L1, [Q|History], M).


qdelete(A, A, L, L).
qdelete(X, A, [H|T], [A|R]) :-
    qdelete(X, H, T, R).


nodiag([], _, _).
nodiag([N|L], B, D) :-
    D =\= N - B,
    D =\= B - N,
    D1 is D + 1,
    nodiag(L, B, D1).


/*
X = [2,4,1,3] ;
queen_2#[[1,2,3,4]|#[[]|#[[2,4,1,3]]]]queen_2 choice=10001 conj=1 recur=7 reuse=0
[[]|32000000]queen_2 push_recur (1,7)
qdelete[1,1,[3],[3]]
qdelete choice=10000 conj=1 recur=8 reuse=1
qdelete success (1,8)
qdelete pop_recur (1,8)
nodiag[525751369,#[[1,2,3,4]|#[[]|#[[2,4,1,3]]]],1]qdelete set_mode (1,7)
qdelete push_recur (1,7)
qdelete[1,1,[3],[3]]
qdelete choice=10000 conj=1 recur=8 reuse=1
qdelete success (1,8)
qdelete pop_recur (1,8)
nodiag[525751369,#[[1,2,3,4]|#[[]|#[[2,4,1,3]]]],1]qdelete set_mode (1,7)
qdelete push_recur (1,7)
qdelete[1,1,[3],[3]]
qdelete choice=10000 conj=1 recur=8 reuse=1
qdelete success (1,8)
qdelete pop_recur (1,8)
nodiag[525751369,#[[1,2,3,4]|#[[]|#[[2,4,1,3]]]],1]qdelete set_mode (1,7)
qdelete push_recur (1,7)
qdelete[1,1,[3],[3]]
qdelete choice=10000 conj=1 recur=8 reuse=1
qdelete success (1,8)
qdelete pop_recur (1,8)
nodiag[525751369,#[[1,2,3,4]|#[[]|#[[2,4,1,3]]]],1]qdelete set_mode (1,7)
qdelete push_recur (1,7)
qdelete[1,1,[3],[3]]
qdelete choice=10000 conj=1 recur=8 reuse=1
qdelete success (1,8)
qdelete pop_recur (1,8)
nodiag[525751369,#[[1,2,3,4]|#[[]|#[[2,4,1,3]]]],1]qdelete set_mode (1,7)
qdelete push_recur (1,7)
qdelete[1,1,[3],[3]]
qdelete choice=10000 conj=1 recur=8 reuse=1
qdelete success (1,8)
qdelete pop_recur (1,8)
nodiag[525751369,#[[1,2,3,4]|#[[]|#[[2,4,1,3]]]],1]qdelete set_mode (1,7)
qdelete push_recur (1,7)
qdelete[1,1,[3],[3]]
qdelete choice=10000 conj=1 recur=8 reuse=1
qdelete success (1,8)
qdelete pop_recur (1,8)
nodiag[525751369,#[[1,2,3,4]|#[[]|#[[2,4,1,3]]]],1]qdelete set_mode (1,7)
qdelete push_recur (1,7)
qdelete[1,1,[3],[3]]        
qdelete choice=10000 conj=1 recur=8 reuse=1
qdelete success (1,8)
qdelete pop_recur (1,8)
nodiag[525751369,#[[1,2,3,4]|#[[]|#[[2,4,1,3]]]],1]qdelete set_mode (1,7)
qdelete push_recur (1,7)
qdelete[1,1,[3],[3]]


*/