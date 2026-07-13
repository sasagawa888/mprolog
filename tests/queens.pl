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
?- queen_2([1,2,3,4],[],X).
[] push_conj (0,0)
queen_2#[[1,2,3,4]|#[[]|#[X]]]queen_2 choice=0 conj=1 recur=0 reuse=0
queen_2 release (1,0)
[1,2,3,4]queen_2 push_recur (1,0)
qdelete[v_5,1,[2,3,4],v_1]qdelete choice=0 conj=1 recur=1 reuse=0
qdelete success (1,1)
qdelete pop_recur (1,1)
nodiag[[],1,1]qdelete push_recur (1,0)
queen_2[[2,3,4],[1],v_6]queen_2 choice=0 conj=1 recur=2 reuse=0
queen_2 release (1,2)
[2,3,4]queen_2 push_recur (1,2)
qdelete[v_15,2,[3,4],v_11]qdelete choice=0 conj=1 recur=3 reuse=0
qdelete success (1,3)
qdelete pop_recur (1,3)
nodiag[[1],2,1]qdelete set_mode (1,2)
qdelete[2,2,[3,4],[3,4]]qdelete choice=10001 conj=1 recur=2 reuse=0
qdelete push_recur (1,2)
qdelete[2,2,[3,4],[3,4]]qdelete choice=1 conj=1 recur=3 reuse=1
qdelete release (1,3)
qdelete push_recur (1,3)
qdelete[v_17,3,[4],v_21]qdelete choice=0 conj=1 recur=4 reuse=0
qdelete success (1,4)
qdelete pop_recur (1,4)
qdelete pop_recur (1,3)
qdelete pop_recur (1,2)
nodiag[[1],3,1]qdelete push_recur (1,1)
queen_2[[2,4],[3,1],v_16]queen_2 choice=0 conj=1 recur=5 reuse=0
queen_2 release (1,5)
[2,4]queen_2 push_recur (1,5)
qdelete[v_30,2,[4],v_26]qdelete choice=0 conj=1 recur=6 reuse=0
qdelete success (1,6)
qdelete pop_recur (1,6)
nodiag[[3,1],2,1]qdelete set_mode (1,5)
qdelete[2,2,[4],[4]]qdelete choice=10001 conj=1 recur=5 reuse=0
qdelete push_recur (1,5)
qdelete[2,2,[4],[4]]qdelete choice=1 conj=1 recur=6 reuse=1
qdelete release (1,6)
qdelete push_recur (1,6)
qdelete[v_32,4,[],v_36]qdelete choice=0 conj=1 recur=7 reuse=0
qdelete success (1,7)
qdelete pop_recur (1,7)
qdelete pop_recur (1,6)
qdelete pop_recur (1,5)
nodiag[[3,1],4,1]qdelete set_mode (1,4)
qdelete[3,3,[4],[4]]qdelete choice=1 conj=1 recur=4 reuse=1
qdelete release (1,4)
qdelete push_recur (1,4)
qdelete[v_22,4,[],v_26]qdelete choice=0 conj=1 recur=8 reuse=0
qdelete success (1,8)
qdelete pop_recur (1,8)
qdelete pop_recur (1,7)
nodiag[v_29,v_30,1]qdelete set_mode (1,6)
qdelete[[],4,[],[]]qdelete choice=10001 conj=1 recur=6 reuse=1
qdelete push_recur (1,6)
qdelete[v_32,v_33,v_34,v_36]qdelete choice=1 conj=1 recur=7 reuse=1
qdelete release (1,7)
qdelete push_recur (1,7)
qdelete[v_37,v_38,v_39,v_41]qdelete choice=0 conj=1 recur=9 reuse=0
qdelete success (1,9)
qdelete pop_recur (1,9)
qdelete pop_recur (1,8)
qdelete pop_recur (1,7)
nodiag[[],[],1]qdelete push_recur (1,6)
queen_2[[],[[]],v_31]queen_2 choice=0 conj=1 recur=10 reuse=0
queen_2 success (1,10)
queen_2 pop_recur (1,10)
queen_2 pop_recur (1,9)
queen_2 pop_recur (1,8)
X = [1,4|v_16] .
*/