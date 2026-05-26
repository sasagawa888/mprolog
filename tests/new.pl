

% inline C language
gen_body(cinline(X),_) :-
    write('{'),
    write(X),
    write('}'),
    nl.

gen_body(X,_) :-
    optimize(det),
    gen_det_body(X).

gen_body(X,_) :-
    optimize(nondet),
    gen_nondet_body(X).

gen_nondet_body((!,Y),N,M,B) :-
    gen_nondet_body(Y,N,M,[]).
gen_nondet_body((X,Y),N,M,B) :-
    gen_a_nondet_body(X,N,M,B),
    gen_nondet_body(Y,N,M,B).
gen_nondet_body((X;Y),N,M,B) :-
    gen_nondet_body(X,N,M,B),
    gen_nondet_body(Y,N,M,B).
gen_nondet_body(X,N,M,B) :-
    gen_a_nondet_body(X,N,M,B).
