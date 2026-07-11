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
yes
?- queen_2([1,2,3,4],[],X).
push_conj (0,0)
queen_2#[[1,2,3,4]|#[[]|#[X]]]choice=0 conj=1 recur=0 reuse=0
release (1,0)
push_recur (1,0)
qdelete[v_5,1,[2,3,4],v_1]choice=0 conj=1 recur=1 reuse=0
success (1,1)
pop_recur (1,1)
push_recur (1,0)
nodiag[[],1,1]set_result (1,2)
push_recur (1,2)
queen_2[[2,3,4],[1],v_6]choice=0 conj=1 recur=3 reuse=0
release (1,3)
push_recur (1,3)
qdelete[v_15,2,[3,4],v_11]choice=0 conj=1 recur=4 reuse=0
success (1,4)
pop_recur (1,4)
push_recur (1,3)
nodiag[[1],2,1]discard_recur (1,5)
qdelete[2,2,[3,4],[3,4]]choice=1 conj=1 recur=4 reuse=1
release (1,4)
push_recur (1,4)
qdelete[v_17,3,[4],v_21]choice=0 conj=1 recur=5 reuse=0
success (1,5)
pop_recur (1,5)
pop_recur (1,4)
push_recur (1,3)
nodiag[[1],3,1]set_result (1,6)
push_recur (1,6)
queen_2[[2,4],[3,1],v_16]choice=0 conj=1 recur=7 reuse=0
release (1,7)
push_recur (1,7)
qdelete[v_30,2,[4],v_26]choice=0 conj=1 recur=8 reuse=0
success (1,8)
pop_recur (1,8)
push_recur (1,7)
nodiag[[3,1],2,1]discard_recur (1,9)
qdelete[2,2,[4],[4]]choice=1 conj=1 recur=8 reuse=1
release (1,8)
push_recur (1,8)
qdelete[v_32,4,[],v_36]choice=0 conj=1 recur=9 reuse=0
success (1,9)
pop_recur (1,9)
pop_recur (1,8)
push_recur (1,7)
nodiag[[3,1],4,1]discard_recur (1,10)
qdelete[4,4,[],[]]choice=1 conj=1 recur=9 reuse=1
release (1,9)
release (1,9)
discard_recur (1,9)
release (1,8)
discard_recur (1,8)
set_mode (1,7)
qdelete[3,2,[3,4],[2,4]]choice=2 conj=1 recur=7 reuse=0
discard_recur (1,7)
release (1,6)
discard_recur (1,6)
set_mode (1,5)
qdelete[3,3,[4],[4]]choice=1 conj=1 recur=5 reuse=1
release (1,5)
push_recur (1,5)
qdelete[v_22,4,[],v_26]choice=0 conj=1 recur=6 reuse=0
success (1,6)
pop_recur (1,6)
pop_recur (1,5)
push_recur (1,4)
nodiag[[],1,1]set_result (1,7)
push_recur (1,7)
queen_2[[2,3,4],[1],[4|v_16]]choice=0 conj=1 recur=8 reuse=0
release (1,8)
push_recur (1,8)
qdelete[4,2,[3,4],v_31]choice=0 conj=1 recur=9 reuse=0
release (1,9)
push_recur (1,9)
qdelete[4,3,[4],v_41]choice=0 conj=1 recur=10 reuse=0
release (1,10)
push_recur (1,10)
qdelete[4,4,[],v_46]choice=0 conj=1 recur=11 reuse=0
success (1,11)
pop_recur (1,11)
pop_recur (1,10)
pop_recur (1,9)
push_recur (1,8)
nodiag[[1],4,1]set_result (1,12)
push_recur (1,12)
queen_2[[2,3],[4,1],v_36]choice=0 conj=1 recur=13 reuse=0
release (1,13)
push_recur (1,13)
qdelete[v_55,2,[3],v_51]choice=0 conj=1 recur=14 reuse=0
success (1,14)
pop_recur (1,14)
push_recur (1,13)
nodiag[[4,1],2,1]set_result (1,15)
push_recur (1,15)
queen_2[[3],[2,4,1],v_56]choice=0 conj=1 recur=16 reuse=0
release (1,16)
push_recur (1,16)
qdelete[v_65,3,[],v_61]choice=0 conj=1 recur=17 reuse=0
success (1,17)
pop_recur (1,17)
push_recur (1,16)
nodiag[[2,4,1],3,1]discard_recur (1,18)
qdelete[3,3,[],[]]choice=1 conj=1 recur=17 reuse=1
release (1,17)
release (1,17)
discard_recur (1,17)
release (1,16)
discard_recur (1,16)
set_mode (1,15)
qdelete[2,2,[3],[3]]choice=2 conj=1 recur=15 reuse=1
discard_recur (1,15)
release (1,14)
discard_recur (1,14)
set_mode (1,13)
qdelete[4,2,[3,4],[2,3]]choice=2 conj=1 recur=13 reuse=0
discard_recur (1,13)
release (1,12)
discard_recur (1,12)
set_mode (1,11)
qdelete[4,4,[],[]]choice=1 conj=1 recur=11 reuse=1
release (1,11)
release (1,11)
discard_recur (1,11)
release (1,10)
discard_recur (1,10)
discard_conj (1,9)
no
?- 

*/