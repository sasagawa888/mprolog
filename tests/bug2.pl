
check([], 3).
check([3], 2).
check([2,3], 1).

queen2([], _, []).
queen2([H|T], History, [Q|M]) :-
    qdelete(Q, H, T, L1),
    check(History, Q),
    queen2(L1, [Q|History], M).

qdelete(A, A, L, L).
qdelete(X, A, [H|T], [A|R]) :-
    qdelete(X, H, T, R).

test(X) :-
    qdelete(X,1,[2,3],_),
    check1(X).

check1(3).