
test :-
    fail;write(2).

between1(L, H, L) :-
    L =< H.

between1(L, H, X) :-
    L < H,
    L1 is L + 1,
    between1(L1, H, X).