n(1).
n(2).
n(3).

bench_count :-
    n(X),
    n(Y),
    write(X-Y),
    nl,
    fail.
bench_count.