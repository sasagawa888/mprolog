analize_pred1(P,N,C) :-
    not(n_dynamic_predicate(P)),
    nondet_recursive(C),
    P1 =.. [type,P,_,_],
    (retract(P1);true),
    asserta(type(P,N,recur)),!.


nondet_recursive([]) :- !,fail.
nondet_recursive([(Head :- Body)|Cs]) :-
    nondet_recursive1(Body,Head).
nondet_recursive([_|Cs]) :- 
    nondet_recursive(Cs).


nondet_recursive1((X,Y),H) :-
    functor(X,P,A),
    functor(H,P,A).
nondet_recursive1((X,Y),H) :-
    nondet_recursive1(Y,H).
nondet_recursive1(end_of_body,H) :- !,fail.
nondet_recursive1(X,H) :-
    nondet_recursive1((X,end_of_body),H).

