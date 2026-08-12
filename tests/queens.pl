% 9-queens program


test16 :- between(1,16,X),test1,fail.
test :- queen([1,2,3,4,5,6,7,8,9],X),write(X),nl,fail.
test1 :- queen([1,2,3,4,5,6,7,8,9],X),fail.


queen(Data, Out) :-
    queen2(Data, [], Out).

queen2([], _, []).
queen2([H|T], History, [Q|M]) :-
    qdelete(Q, H, T, L1),
    write(dt(Q,H,T,L1)),
    nodiag(History, Q, 1),
    queen2(L1, [Q|History], M).


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
?- ['./tests/queens.o'].
yes
?- queen2([1,2,3,4],[],X).
 push_conj (0,0)
 save_arg (1,0)
 Jpush_next (1,0)
queen2#[[1,2,3,4]|#[[]|#[X]]]#[[1,2,3,4]|#[[]|#[X]]] release (1,0) SP=0 AC=30000001
 inc_choice (1,0)
 Jset_back (1,0)
 release (1,0) SP=0 AC=30000001
 inc_choice (1,0)
 Jset_back (1,0)
 Jpush_back (1,0)
 push_recur (1,0) SP=4 AC=30000007
 Jpush_next (1,1)
 get_choice (1,1) ch=0
qdelete[v_5,v_2,v_3,v_1][v_5,1,[2,3,4],v_1] release (1,1) SP=4 AC=30000007
 inc_choice (1,1)
 Jset_back (1,1)
success Jpop_next (1,1)
 get_choice (1,1) ch=1
 Jpush_back (1,1)
 push_recur (1,1) SP=8 AC=30000009
 Jpush_next (1,2)
dt(1,1,[2,3,4],[2,3,4])success Jpop_next (1,2)
 get_choice (1,2) ch=0
 Jpush_next (1,2)
nodiag[v_4,v_5,1][[],1,1]success Jpop_next (1,2)
 get_choice (1,2) ch=0
 Jpush_next (1,2)
 get_choice (1,2) ch=0
queen2[v_1,[v_5|v_4],v_6][[2,3,4],[1],v_6] release (1,2) SP=8 AC=30000009
 inc_choice (1,2)
 Jset_back (1,2)
 release (1,2) SP=8 AC=30000009
 inc_choice (1,2)
 Jset_back (1,2)
 Jpush_back (1,2)
 push_recur (1,2) SP=12 AC=30000015
 Jpush_next (1,3)
 get_choice (1,3) ch=0
qdelete[v_13,v_10,v_11,v_9][v_13,2,[3,4],v_9] release (1,3) SP=12 AC=30000015
 inc_choice (1,3)
 Jset_back (1,3)
success Jpop_next (1,3)
 get_choice (1,3) ch=1
 Jpush_back (1,3)
 push_recur (1,3) SP=16 AC=30000017
 Jpush_next (1,4)
dt(2,2,[3,4],[3,4])success Jpop_next (1,4)
 get_choice (1,4) ch=0
 Jpush_next (1,4)
nodiag[v_12,v_13,1][[1],2,1]allfail pop_recur (1,4)
 Jpop_next (1,3)
 get_arg (1,3) 
 get_vp (1,3) 
 get_np (1,3) 
 Jpush_next (1,3)
 get_choice (1,3) ch=1
qdelete[v_13,v_10,v_11,v_9][2,2,[3,4],[3,4]] release (1,3) SP=12 AC=30000015
 inc_choice (1,3)
 Jset_back (1,3)
 Jpush_back (1,3)
 push_recur (1,3) SP=17 AC=30000020
 Jpush_next (1,4)
 get_choice (1,4) ch=0
qdelete[v_15,v_16,v_17,v_19][v_15,3,[4],v_19] release (1,4) SP=17 AC=30000020
 inc_choice (1,4)
 Jset_back (1,4)
success Jpop_next (1,4)
 get_choice (1,4) ch=1
success Jpop_next (1,4)
 get_choice (1,4) ch=1
 Jpush_back (1,4)
 push_recur (1,4) SP=21 AC=30000022
 Jpush_next (1,5)
dt(3,2,[3,4],[2,4])success Jpop_next (1,5)
 get_choice (1,5) ch=0
 Jpush_next (1,5)
nodiag[v_12,v_13,1][[1],3,1]success Jpop_next (1,5)
 get_choice (1,5) ch=0
 Jpush_next (1,5)
 get_choice (1,5) ch=0
queen2[v_9,[v_13|v_12],v_14][[2,4],[3,1],v_14] release (1,5) SP=21 AC=30000022
 inc_choice (1,5)
 Jset_back (1,5)
 release (1,5) SP=21 AC=30000022
 inc_choice (1,5)
 Jset_back (1,5)
 Jpush_back (1,5)
 push_recur (1,5) SP=25 AC=30000028
 Jpush_next (1,6)
 get_choice (1,6) ch=0
qdelete[v_26,v_23,v_24,v_22][v_26,2,[4],v_22] release (1,6) SP=25 AC=30000028
 inc_choice (1,6)
 Jset_back (1,6)
success Jpop_next (1,6)
 get_choice (1,6) ch=1
 Jpush_back (1,6)
 push_recur (1,6) SP=29 AC=30000030
 Jpush_next (1,7)
dt(2,2,[4],[4])success Jpop_next (1,7)
 get_choice (1,7) ch=0
 Jpush_next (1,7)
nodiag[v_25,v_26,1][[3,1],2,1]allfail pop_recur (1,7)
 Jpop_next (1,6)
 get_arg (1,6) 
 get_vp (1,6) 
 get_np (1,6) 
 Jpush_next (1,6)
 get_choice (1,6) ch=1
qdelete[v_26,v_23,v_24,v_22][2,2,[4],[4]] release (1,6) SP=25 AC=30000028
 inc_choice (1,6)
 Jset_back (1,6)
 Jpush_back (1,6)
 push_recur (1,6) SP=30 AC=30000033
 Jpush_next (1,7)
 get_choice (1,7) ch=0
qdelete[v_28,v_29,v_30,v_32][v_28,4,[],v_32] release (1,7) SP=30 AC=30000033
 inc_choice (1,7)
 Jset_back (1,7)
success Jpop_next (1,7)
 get_choice (1,7) ch=1
success Jpop_next (1,7)
 get_choice (1,7) ch=1
 Jpush_back (1,7)
 push_recur (1,7) SP=34 AC=30000035
 Jpush_next (1,8)
dt(4,2,[4],[2])success Jpop_next (1,8)
 get_choice (1,8) ch=0
 Jpush_next (1,8)
nodiag[v_25,v_26,1][[3,1],4,1]allfail pop_recur (1,8)
 Jpop_next (1,7)
 get_arg (1,7) 
 get_vp (1,7) 
 get_np (1,7) 
 Jpush_next (1,7)
 get_choice (1,7) ch=1
qdelete[v_31,v_28,v_29,v_27][2,4,4,v_27] release (1,7) SP=30 AC=30000033
 inc_choice (1,7)
 Jset_back (1,7)
 Jpop_back (1,7)
allfail pop_recur (1,7)
 Jpop_next (1,6)
 get_arg (1,6) 
 get_vp (1,6) 
 get_np (1,6) 
 Jpop_back (1,6)
allfail pop_recur (1,6)
 Jpop_next (1,5)
 get_arg (1,5) 
 get_vp (1,5) 
 get_np (1,5) 
 Jpop_back (1,5)
allfail pop_recur (1,5)
 Jpop_next (1,4)
 get_arg (1,4) 
 get_vp (1,4) 
 get_np (1,4) 
 Jpush_next (1,4)
 get_choice (1,4) ch=1
qdelete[v_18,v_15,v_16,v_14][2,3,3,[v_36|v_27]] release (1,4) SP=17 AC=30000020
 inc_choice (1,4)
 Jset_back (1,4)
 Jpop_back (1,4)
allfail pop_recur (1,4)
 Jpop_next (1,3)
 get_arg (1,3) 
 get_vp (1,3) 
 get_np (1,3) 
 Jpop_back (1,3)
allfail pop_recur (1,3)
 Jpop_next (1,2)
 get_arg (1,2) 
 get_vp (1,2) 
 get_np (1,2) 
 Jpop_back (1,2)
allfail pop_recur (1,2)
 Jpop_next (1,1)
 get_arg (1,1) 
 get_vp (1,1) 
 get_np (1,1) 
 Jpush_next (1,1)
 get_choice (1,1) ch=1
qdelete[v_5,v_2,v_3,v_1][1,1,[2,3,4],[2,3,4]] release (1,1) SP=4 AC=30000007
 inc_choice (1,1)
 Jset_back (1,1)
 Jpush_back (1,1)
 push_recur (1,1) SP=9 AC=30000012
 Jpush_next (1,2)
 get_choice (1,2) ch=0
qdelete[v_7,v_8,v_9,v_11][v_7,2,[3,4],v_11] release (1,2) SP=9 AC=30000012
 inc_choice (1,2)
 Jset_back (1,2)
success Jpop_next (1,2)
 get_choice (1,2) ch=1
success Jpop_next (1,2)
 get_choice (1,2) ch=1
 Jpush_back (1,2)
 push_recur (1,2) SP=13 AC=30000014
 Jpush_next (1,3)
dt(2,1,[2,3,4],[1,3,4])success Jpop_next (1,3)
 get_choice (1,3) ch=0
 Jpush_next (1,3)
nodiag[v_4,v_5,1][[],2,1]success Jpop_next (1,3)
 get_choice (1,3) ch=0
 Jpush_next (1,3)
 get_choice (1,3) ch=0
queen2[v_1,[v_5|v_4],v_6][[1,3,4],[2],v_6] release (1,3) SP=13 AC=30000014
 inc_choice (1,3)
 Jset_back (1,3)
 release (1,3) SP=13 AC=30000014
 inc_choice (1,3)
 Jset_back (1,3)
 Jpush_back (1,3)
 push_recur (1,3) SP=17 AC=30000020
 Jpush_next (1,4)
 get_choice (1,4) ch=0
qdelete[v_18,v_15,v_16,v_14][v_18,1,[3,4],v_14] release (1,4) SP=17 AC=30000020
 inc_choice (1,4)
 Jset_back (1,4)
success Jpop_next (1,4)
 get_choice (1,4) ch=1
 Jpush_back (1,4)
 push_recur (1,4) SP=21 AC=30000022
 Jpush_next (1,5)
dt(1,1,[3,4],[3,4])success Jpop_next (1,5)
 get_choice (1,5) ch=0
 Jpush_next (1,5)
nodiag[v_17,v_18,1][[2],1,1]allfail pop_recur (1,5)
 Jpop_next (1,4)
 get_arg (1,4) 
 get_vp (1,4) 
 get_np (1,4) 
 Jpush_next (1,4)
 get_choice (1,4) ch=1
qdelete[v_18,v_15,v_16,v_14][1,1,[3,4],[3,4]] release (1,4) SP=17 AC=30000020
 inc_choice (1,4)
 Jset_back (1,4)
 Jpush_back (1,4)
 push_recur (1,4) SP=22 AC=30000025
 Jpush_next (1,5)
 get_choice (1,5) ch=0
qdelete[v_20,v_21,v_22,v_24][v_20,3,[4],v_24] release (1,5) SP=22 AC=30000025
 inc_choice (1,5)
 Jset_back (1,5)
success Jpop_next (1,5)
 get_choice (1,5) ch=1
success Jpop_next (1,5)
 get_choice (1,5) ch=1
 Jpush_back (1,5)
 push_recur (1,5) SP=26 AC=30000027
 Jpush_next (1,6)
dt(3,1,[3,4],[1,4])success Jpop_next (1,6)
 get_choice (1,6) ch=0
 Jpush_next (1,6)
nodiag[v_17,v_18,1][[2],3,1]allfail pop_recur (1,6)
 Jpop_next (1,5)
 get_arg (1,5) 
 get_vp (1,5) 
 get_np (1,5) 
 Jpush_next (1,5)
 get_choice (1,5) ch=1
qdelete[v_23,v_20,v_21,v_19][1,3,3,v_19] release (1,5) SP=22 AC=30000025
 inc_choice (1,5)
 Jset_back (1,5)
 Jpop_back (1,5)
allfail pop_recur (1,5)
 Jpop_next (1,4)
 get_arg (1,4) 
 get_vp (1,4) 
 get_np (1,4) 
 Jpop_back (1,4)
allfail pop_recur (1,4)
 Jpop_next (1,3)
 get_arg (1,3) 
 get_vp (1,3) 
 get_np (1,3) 
 Jpop_back (1,3)
allfail pop_recur (1,3)
 Jpop_next (1,2)
 get_arg (1,2) 
 get_vp (1,2) 
 get_np (1,2) 
 Jpush_next (1,2)
 get_choice (1,2) ch=1
qdelete[v_10,v_7,v_8,v_6][1,2,2,[v_28|v_19]] release (1,2) SP=9 AC=30000012
 inc_choice (1,2)
 Jset_back (1,2)
 Jpop_back (1,2)
allfail pop_recur (1,2)
 Jpop_next (1,1)
 get_arg (1,1) 
 get_vp (1,1) 
 get_np (1,1) 
 Jpop_back (1,1)
allfail pop_recur (1,1)
 Jpop_next (1,0)
 get_arg (1,0) 
 get_vp (1,0) 
 get_np (1,0) 
 Jpop_back (1,0)
allfail discard_conj (1,0)
no
?- 
*/