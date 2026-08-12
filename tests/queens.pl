% 9-queens program


test16 :- between(1,16,X),test1,fail.
test :- queen([1,2,3,4,5,6,7,8,9],X),write(X),nl,fail.
test1 :- queen([1,2,3,4,5,6,7,8,9],X),fail.


queen(Data, Out) :-
    queen2(Data, [], Out).

queen2([], _, []).
queen2([H|T], History, [Q|M]) :-
    qdelete(Q, H, T, L1),
    nodiag(History, Q, 1),
    write(L1),
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
queen2#[[1,2,3,4]|#[[]|#[X]]]#[[1,2,3,4]|#[[]|#[X]]] release (1,0) SP=0 AC=30000001

var_0 -1000000001 inc_choice (1,0)
 release (1,0) SP=0 AC=30000001

var_0 -1000000001 inc_choice (1,0)
 push_recur (1,0) SP=4 AC=30000007
 get_choice (1,1) ch=0
qdelete[v_5,v_2,v_3,v_1][v_5,1,[2,3,4],v_1] release (1,1) SP=4 AC=30000007

0 v_2
1 v_3
2 v_4
3 X
var_0 -1000000001
var_1 -1000000001
var_2 1
var_3 [2,3,4]
var_4 []
var_5 -1000000001
var_6 -1000000001 inc_choice (1,1)
success get_choice (1,1) ch=1
 push_recur (1,1) SP=8 AC=30000009
nodiag[v_4,v_5,1][[],1,1]success get_choice (1,2) ch=0
[2,3,4]success get_choice (1,2) ch=0
 push_recur (1,2) SP=8 AC=30000009
 get_choice (1,3) ch=0
queen2[v_1,[v_5|v_4],v_6][[2,3,4],[1],v_6] release (1,3) SP=8 AC=30000009

0 v_2
1 v_3
2 v_4
3 X
4 v_5
5 v_7
6 v_8
7 v_1
var_0 -1000000001
var_1 [2,3,4]
var_2 1
var_3 [2,3,4]
var_4 []
var_5 v_7
var_6 -1000000001
var_7 1
var_8 [2,3,4] inc_choice (1,3)
 release (1,3) SP=8 AC=30000009

0 v_2
1 v_3
2 v_4
3 X
4 v_5
5 v_7
6 v_8
7 v_1
var_0 -1000000001
var_1 [2,3,4]
var_2 1
var_3 [2,3,4]
var_4 []
var_5 v_7
var_6 -1000000001
var_7 1
var_8 [2,3,4] inc_choice (1,3)
 push_recur (1,3) SP=12 AC=30000015
 get_choice (1,4) ch=0
qdelete[v_13,v_10,v_11,v_9][v_13,2,[3,4],v_9] release (1,4) SP=12 AC=30000015

0 v_2
1 v_3
2 v_4
3 X
4 v_5
5 v_7
6 v_8
7 v_1
8 v_10
9 v_11
10 v_12
11 v_6
var_0 -1000000001
var_1 [2,3,4]
var_2 1
var_3 [2,3,4]
var_4 []
var_5 v_7
var_6 [v_13|v_14]
var_7 1
var_8 [2,3,4]
var_9 -1000000001
var_10 2
var_11 [3,4]
var_12 [v_5|v_4]
var_13 -1000000001
var_14 -1000000001 inc_choice (1,4)
success get_choice (1,4) ch=1
 push_recur (1,4) SP=16 AC=30000017
nodiag[v_12,v_13,1][[1],2,1]allfail pop_recur (1,5)
 get_arg (1,4) 
 get_vp (1,4) 
 get_np (1,4) 
 get_choice (1,4) ch=1
qdelete[v_13,v_10,v_11,v_9][2,2,[3,4],[3,4]] release (1,4) SP=12 AC=30000015

0 v_2
1 v_3
2 v_4
3 X
4 v_5
5 v_7
6 v_8
7 v_1
8 v_10
9 v_11
10 v_12
11 v_6
var_0 -1000000001
var_1 [2,3,4]
var_2 1
var_3 [2,3,4]
var_4 []
var_5 v_7
var_6 [v_13|v_14]
var_7 1
var_8 [2,3,4]
var_9 -1000000001
var_10 2
var_11 [3,4]
var_12 [v_5|v_4]
var_13 -1000000001
var_14 -1000000001 inc_choice (1,4)
 push_recur (1,4) SP=17 AC=30000020
 get_choice (1,5) ch=0
qdelete[v_15,v_16,v_17,v_19][v_15,3,[4],v_19] release (1,5) SP=17 AC=30000020

0 v_2
1 v_3
2 v_4
3 X
4 v_5
5 v_7
6 v_8
7 v_1
8 v_10
9 v_11
10 v_12
11 v_6
12 v_13
13 v_18
14 v_16
15 v_17
16 v_9
var_0 -1000000001
var_1 [2,3,4]
var_2 1
var_3 [2,3,4]
var_4 []
var_5 v_7
var_6 [v_13|v_14]
var_7 1
var_8 [2,3,4]
var_9 [v_18|v_19]
var_10 2
var_11 [3,4]
var_12 [v_5|v_4]
var_13 v_15
var_14 -1000000001
var_15 -1000000001
var_16 3
var_17 [4]
var_18 2
var_19 -1000000001 inc_choice (1,5)
success get_choice (1,5) ch=1
success get_choice (1,5) ch=1
 push_recur (1,5) SP=21 AC=30000022
nodiag[v_12,v_13,1][[1],3,1]success get_choice (1,6) ch=0
[2,4]success get_choice (1,6) ch=0
 push_recur (1,6) SP=21 AC=30000022
 get_choice (1,7) ch=0
queen2[v_9,[v_13|v_12],v_14][[2,4],[3,1],v_14] release (1,7) SP=21 AC=30000022

0 v_2
1 v_3
2 v_4
3 X
4 v_5
5 v_7
6 v_8
7 v_1
8 v_10
9 v_11
10 v_12
11 v_6
12 v_13
13 v_18
14 v_16
15 v_17
16 v_9
17 v_15
18 v_20
19 v_21
20 v_19
var_0 -1000000001
var_1 [2,3,4]
var_2 1
var_3 [2,3,4]
var_4 []
var_5 v_7
var_6 [v_13|v_14]
var_7 1
var_8 [2,3,4]
var_9 [v_18|v_19]
var_10 2
var_11 [3,4]
var_12 [v_5|v_4]
var_13 v_15
var_14 -1000000001
var_15 v_20
var_16 3
var_17 [4]
var_18 2
var_19 [4]
var_20 3
var_21 [4] inc_choice (1,7)
 release (1,7) SP=21 AC=30000022

0 v_2
1 v_3
2 v_4
3 X
4 v_5
5 v_7
6 v_8
7 v_1
8 v_10
9 v_11
10 v_12
11 v_6
12 v_13
13 v_18
14 v_16
15 v_17
16 v_9
17 v_15
18 v_20
19 v_21
20 v_19
var_0 -1000000001
var_1 [2,3,4]
var_2 1
var_3 [2,3,4]
var_4 []
var_5 v_7
var_6 [v_13|v_14]
var_7 1
var_8 [2,3,4]
var_9 [v_18|v_19]
var_10 2
var_11 [3,4]
var_12 [v_5|v_4]
var_13 v_15
var_14 -1000000001
var_15 v_20
var_16 3
var_17 [4]
var_18 2
var_19 [4]
var_20 3
var_21 [4] inc_choice (1,7)
 push_recur (1,7) SP=25 AC=30000028
 get_choice (1,8) ch=0
qdelete[v_26,v_23,v_24,v_22][v_26,2,[4],v_22] release (1,8) SP=25 AC=30000028

0 v_2
1 v_3
2 v_4
3 X
4 v_5
5 v_7
6 v_8
7 v_1
8 v_10
9 v_11
10 v_12
11 v_6
12 v_13
13 v_18
14 v_16
15 v_17
16 v_9
17 v_15
18 v_20
19 v_21
20 v_19
21 v_23
22 v_24
23 v_25
24 v_14
var_0 -1000000001
var_1 [2,3,4]
var_2 1
var_3 [2,3,4]
var_4 []
var_5 v_7
var_6 [v_13|v_14]
var_7 1
var_8 [2,3,4]
var_9 [v_18|v_19]
var_10 2
var_11 [3,4]
var_12 [v_5|v_4]
var_13 v_15
var_14 [v_26|v_27]
var_15 v_20
var_16 3
var_17 [4]
var_18 2
var_19 [4]
var_20 3
var_21 [4]
var_22 -1000000001
var_23 2
var_24 [4]
var_25 [v_13|v_12]
var_26 -1000000001
var_27 -1000000001 inc_choice (1,8)
success get_choice (1,8) ch=1
 push_recur (1,8) SP=29 AC=30000030
nodiag[v_25,v_26,1][[3,1],2,1]allfail pop_recur (1,9)
 get_arg (1,8) 
 get_vp (1,8) 
 get_np (1,8) 
 get_choice (1,8) ch=1
qdelete[v_26,v_23,v_24,v_22][2,2,[4],[4]] release (1,8) SP=25 AC=30000028

0 v_2
1 v_3
2 v_4
3 X
4 v_5
5 v_7
6 v_8
7 v_1
8 v_10
9 v_11
10 v_12
11 v_6
12 v_13
13 v_18
14 v_16
15 v_17
16 v_9
17 v_15
18 v_20
19 v_21
20 v_19
21 v_23
22 v_24
23 v_25
24 v_14
var_0 -1000000001
var_1 [2,3,4]
var_2 1
var_3 [2,3,4]
var_4 []
var_5 v_7
var_6 [v_13|v_14]
var_7 1
var_8 [2,3,4]
var_9 [v_18|v_19]
var_10 2
var_11 [3,4]
var_12 [v_5|v_4]
var_13 v_15
var_14 [v_26|v_27]
var_15 v_20
var_16 3
var_17 [4]
var_18 2
var_19 [4]
var_20 3
var_21 [4]
var_22 -1000000001
var_23 2
var_24 [4]
var_25 [v_13|v_12]
var_26 -1000000001
var_27 -1000000001 inc_choice (1,8)
 push_recur (1,8) SP=30 AC=30000033
 get_choice (1,9) ch=0
qdelete[v_28,v_29,v_30,v_32][v_28,4,[],v_32] release (1,9) SP=30 AC=30000033

0 v_2
1 v_3
2 v_4
3 X
4 v_5
5 v_7
6 v_8
7 v_1
8 v_10
9 v_11
10 v_12
11 v_6
12 v_13
13 v_18
14 v_16
15 v_17
16 v_9
17 v_15
18 v_20
19 v_21
20 v_19
21 v_23
22 v_24
23 v_25
24 v_14
25 v_26
26 v_31
27 v_29
28 v_30
29 v_22
var_0 -1000000001
var_1 [2,3,4]
var_2 1
var_3 [2,3,4]
var_4 []
var_5 v_7
var_6 [v_13|v_14]
var_7 1
var_8 [2,3,4]
var_9 [v_18|v_19]
var_10 2
var_11 [3,4]
var_12 [v_5|v_4]
var_13 v_15
var_14 [v_26|v_27]
var_15 v_20
var_16 3
var_17 [4]
var_18 2
var_19 [4]
var_20 3
var_21 [4]
var_22 [v_31|v_32]
var_23 2
var_24 [4]
var_25 [v_13|v_12]
var_26 v_28
var_27 -1000000001
var_28 -1000000001
var_29 4
var_30 []
var_31 2
var_32 -1000000001 inc_choice (1,9)
success get_choice (1,9) ch=1
success get_choice (1,9) ch=1
 push_recur (1,9) SP=34 AC=30000035
nodiag[v_25,v_26,1][[3,1],4,1]allfail pop_recur (1,10)
 get_arg (1,9) 
 get_vp (1,9) 
 get_np (1,9) 
 get_choice (1,9) ch=1
qdelete[v_31,v_28,v_29,v_27][2,4,4,v_27] release (1,9) SP=30 AC=30000033

0 v_2
1 v_3
2 v_4
3 X
4 v_5
5 v_7
6 v_8
7 v_1
8 v_10
9 v_11
10 v_12
11 v_6
12 v_13
13 v_18
14 v_16
15 v_17
16 v_9
17 v_15
18 v_20
19 v_21
20 v_19
21 v_23
22 v_24
23 v_25
24 v_14
25 v_26
26 v_31
27 v_29
28 v_30
29 v_22
var_0 -1000000001
var_1 [2,3,4]
var_2 1
var_3 [2,3,4]
var_4 []
var_5 v_7
var_6 [v_13|v_14]
var_7 1
var_8 [2,3,4]
var_9 [v_18|v_19]
var_10 2
var_11 [3,4]
var_12 [v_5|v_4]
var_13 v_15
var_14 [v_26|v_27]
var_15 v_20
var_16 3
var_17 [4]
var_18 2
var_19 [4]
var_20 3
var_21 [4]
var_22 [v_31|v_32]
var_23 2
var_24 [4]
var_25 [v_13|v_12]
var_26 v_28
var_27 -1000000001
var_28 -1000000001
var_29 4
var_30 []
var_31 2
var_32 -1000000001 inc_choice (1,9)
allfail pop_recur (1,9)
 get_arg (1,8) 
 get_vp (1,8) 
 get_np (1,8) 
allfail pop_recur (1,8)
 get_arg (1,7) 
 get_vp (1,7) 
 get_np (1,7) 
allfail pop_recur (1,7)
 get_arg (1,6) 
 get_vp (1,6) 
 get_np (1,6) 
allfail pop_recur (1,6)
 get_arg (1,5) 
 get_vp (1,5) 
 get_np (1,5) 
 get_choice (1,5) ch=1
qdelete[v_18,v_15,v_16,v_14][2,3,3,[v_36|v_27]] release (1,5) SP=17 AC=30000020

0 v_2
1 v_3
2 v_4
3 X
4 v_5
5 v_7
6 v_8
7 v_1
8 v_10
9 v_11
10 v_12
11 v_6
12 v_13
13 v_18
14 v_16
15 v_17
16 v_9
var_0 -1000000001
var_1 [2,3,4]
var_2 1
var_3 [2,3,4]
var_4 []
var_5 v_7
var_6 [v_13|v_14]
var_7 1
var_8 [2,3,4]
var_9 [v_18|v_19]
var_10 2
var_11 [3,4]
var_12 [v_5|v_4]
var_13 v_15
var_14 -1000000001
var_15 -1000000001
var_16 3
var_17 [4]
var_18 2
var_19 -1000000001 inc_choice (1,5)
allfail pop_recur (1,5)
 get_arg (1,4) 
 get_vp (1,4) 
 get_np (1,4) 
allfail pop_recur (1,4)
 get_arg (1,3) 
 get_vp (1,3) 
 get_np (1,3) 
allfail pop_recur (1,3)
 get_arg (1,2) 
 get_vp (1,2) 
 get_np (1,2) 
allfail pop_recur (1,2)
 get_arg (1,1) 
 get_vp (1,1) 
 get_np (1,1) 
 get_choice (1,1) ch=1
qdelete[v_5,v_2,v_3,v_1][1,1,[2,3,4],[2,3,4]] release (1,1) SP=4 AC=30000007

0 v_2
1 v_3
2 v_4
3 X
var_0 -1000000001
var_1 -1000000001
var_2 1
var_3 [2,3,4]
var_4 []
var_5 -1000000001
var_6 -1000000001 inc_choice (1,1)
 push_recur (1,1) SP=9 AC=30000012
 get_choice (1,2) ch=0
qdelete[v_7,v_8,v_9,v_11][v_7,2,[3,4],v_11] release (1,2) SP=9 AC=30000012

0 v_2
1 v_3
2 v_4
3 X
4 v_5
5 v_10
6 v_8
7 v_9
8 v_1
var_0 -1000000001
var_1 [v_10|v_11]
var_2 1
var_3 [2,3,4]
var_4 []
var_5 v_7
var_6 -1000000001
var_7 -1000000001
var_8 2
var_9 [3,4]
var_10 1
var_11 -1000000001 inc_choice (1,2)
success get_choice (1,2) ch=1
success get_choice (1,2) ch=1
 push_recur (1,2) SP=13 AC=30000014
nodiag[v_4,v_5,1][[],2,1]success get_choice (1,3) ch=0
[1,3,4]success get_choice (1,3) ch=0
 push_recur (1,3) SP=13 AC=30000014
 get_choice (1,4) ch=0
queen2[v_1,[v_5|v_4],v_6][[1,3,4],[2],v_6] release (1,4) SP=13 AC=30000014

0 v_2
1 v_3
2 v_4
3 X
4 v_5
5 v_10
6 v_8
7 v_9
8 v_1
9 v_7
10 v_12
11 v_13
12 v_11
var_0 -1000000001
var_1 [v_10|v_11]
var_2 1
var_3 [2,3,4]
var_4 []
var_5 v_7
var_6 -1000000001
var_7 v_12
var_8 2
var_9 [3,4]
var_10 1
var_11 [3,4]
var_12 2
var_13 [3,4] inc_choice (1,4)
 release (1,4) SP=13 AC=30000014

0 v_2
1 v_3
2 v_4
3 X
4 v_5
5 v_10
6 v_8
7 v_9
8 v_1
9 v_7
10 v_12
11 v_13
12 v_11
var_0 -1000000001
var_1 [v_10|v_11]
var_2 1
var_3 [2,3,4]
var_4 []
var_5 v_7
var_6 -1000000001
var_7 v_12
var_8 2
var_9 [3,4]
var_10 1
var_11 [3,4]
var_12 2
var_13 [3,4] inc_choice (1,4)
 push_recur (1,4) SP=17 AC=30000020
 get_choice (1,5) ch=0
qdelete[v_18,v_15,v_16,v_14][v_18,1,[3,4],v_14] release (1,5) SP=17 AC=30000020

0 v_2
1 v_3
2 v_4
3 X
4 v_5
5 v_10
6 v_8
7 v_9
8 v_1
9 v_7
10 v_12
11 v_13
12 v_11
13 v_15
14 v_16
15 v_17
16 v_6
var_0 -1000000001
var_1 [v_10|v_11]
var_2 1
var_3 [2,3,4]
var_4 []
var_5 v_7
var_6 [v_18|v_19]
var_7 v_12
var_8 2
var_9 [3,4]
var_10 1
var_11 [3,4]
var_12 2
var_13 [3,4]
var_14 -1000000001
var_15 1
var_16 [3,4]
var_17 [v_5|v_4]
var_18 -1000000001
var_19 -1000000001 inc_choice (1,5)
success get_choice (1,5) ch=1
 push_recur (1,5) SP=21 AC=30000022
nodiag[v_17,v_18,1][[2],1,1]allfail pop_recur (1,6)
 get_arg (1,5) 
 get_vp (1,5) 
 get_np (1,5) 
 get_choice (1,5) ch=1
qdelete[v_18,v_15,v_16,v_14][1,1,[3,4],[3,4]] release (1,5) SP=17 AC=30000020

0 v_2
1 v_3
2 v_4
3 X
4 v_5
5 v_10
6 v_8
7 v_9
8 v_1
9 v_7
10 v_12
11 v_13
12 v_11
13 v_15
14 v_16
15 v_17
16 v_6
var_0 -1000000001
var_1 [v_10|v_11]
var_2 1
var_3 [2,3,4]
var_4 []
var_5 v_7
var_6 [v_18|v_19]
var_7 v_12
var_8 2
var_9 [3,4]
var_10 1
var_11 [3,4]
var_12 2
var_13 [3,4]
var_14 -1000000001
var_15 1
var_16 [3,4]
var_17 [v_5|v_4]
var_18 -1000000001
var_19 -1000000001 inc_choice (1,5)
 push_recur (1,5) SP=22 AC=30000025
 get_choice (1,6) ch=0
qdelete[v_20,v_21,v_22,v_24][v_20,3,[4],v_24] release (1,6) SP=22 AC=30000025

0 v_2
1 v_3
2 v_4
3 X
4 v_5
5 v_10
6 v_8
7 v_9
8 v_1
9 v_7
10 v_12
11 v_13
12 v_11
13 v_15
14 v_16
15 v_17
16 v_6
17 v_18
18 v_23
19 v_21
20 v_22
21 v_14
var_0 -1000000001
var_1 [v_10|v_11]
var_2 1
var_3 [2,3,4]
var_4 []
var_5 v_7
var_6 [v_18|v_19]
var_7 v_12
var_8 2
var_9 [3,4]
var_10 1
var_11 [3,4]
var_12 2
var_13 [3,4]
var_14 [v_23|v_24]
var_15 1
var_16 [3,4]
var_17 [v_5|v_4]
var_18 v_20
var_19 -1000000001
var_20 -1000000001
var_21 3
var_22 [4]
var_23 1
var_24 -1000000001 inc_choice (1,6)
success get_choice (1,6) ch=1
success get_choice (1,6) ch=1
 push_recur (1,6) SP=26 AC=30000027
nodiag[v_17,v_18,1][[2],3,1]allfail pop_recur (1,7)
 get_arg (1,6) 
 get_vp (1,6) 
 get_np (1,6) 
 get_choice (1,6) ch=1
qdelete[v_23,v_20,v_21,v_19][1,3,3,v_19] release (1,6) SP=22 AC=30000025

0 v_2
1 v_3
2 v_4
3 X
4 v_5
5 v_10
6 v_8
7 v_9
8 v_1
9 v_7
10 v_12
11 v_13
12 v_11
13 v_15
14 v_16
15 v_17
16 v_6
17 v_18
18 v_23
19 v_21
20 v_22
21 v_14
var_0 -1000000001
var_1 [v_10|v_11]
var_2 1
var_3 [2,3,4]
var_4 []
var_5 v_7
var_6 [v_18|v_19]
var_7 v_12
var_8 2
var_9 [3,4]
var_10 1
var_11 [3,4]
var_12 2
var_13 [3,4]
var_14 [v_23|v_24]
var_15 1
var_16 [3,4]
var_17 [v_5|v_4]
var_18 v_20
var_19 -1000000001
var_20 -1000000001
var_21 3
var_22 [4]
var_23 1
var_24 -1000000001 inc_choice (1,6)
allfail pop_recur (1,6)
 get_arg (1,5) 
 get_vp (1,5) 
 get_np (1,5) 
allfail pop_recur (1,5)
 get_arg (1,4) 
 get_vp (1,4) 
 get_np (1,4) 
allfail pop_recur (1,4)
 get_arg (1,3) 
 get_vp (1,3) 
 get_np (1,3) 
allfail pop_recur (1,3)
 get_arg (1,2) 
 get_vp (1,2) 
 get_np (1,2) 
 get_choice (1,2) ch=1
qdelete[v_10,v_7,v_8,v_6][1,2,2,[v_28|v_19]] release (1,2) SP=9 AC=30000012

0 v_2
1 v_3
2 v_4
3 X
4 v_5
5 v_10
6 v_8
7 v_9
8 v_1
var_0 -1000000001
var_1 [v_10|v_11]
var_2 1
var_3 [2,3,4]
var_4 []
var_5 v_7
var_6 -1000000001
var_7 -1000000001
var_8 2
var_9 [3,4]
var_10 1
var_11 -1000000001 inc_choice (1,2)
allfail pop_recur (1,2)
 get_arg (1,1) 
 get_vp (1,1) 
 get_np (1,1) 
allfail pop_recur (1,1)
 get_arg (1,0) 
 get_vp (1,0) 
 get_np (1,0) 
allfail discard_conj (1,0)
no
?- 
*/