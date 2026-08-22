
test :-
    write(1);write(2).


mbetween(Low, High, Low) :-
    Low =< High.

mbetween(Low, High, X) :-
    Low < High,
    Low1 is Low + 1,
    mbetween(Low1, High, X).
