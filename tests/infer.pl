% mode-inferencer
:- use_module(list).
% test case
foo(X,Y) :- true,X is Y.
% Partition list for quicksort
partition([X|L], Y, [X|L1], L2) :-
    X < Y, !, partition(L, Y, L1, L2).
partition([X|L], Y, L1, [X|L2]) :-
    !,partition(L, Y, L1, L2).
partition([], _ , [], []) :- !.

qsort([X|L], R, R0) :-
    partition(L, X, L1, L2),
    qsort(L2, R1, R0),
    qsort(L1, R, [X|R1]).
qsort([], R, R) :- !.

mode(_,[]).
%-----------------------------

test(P) :-
    n_arity_count(P,L),
    test1(P,L).

testc(P) :-
    abolish(mode/2),
    assert(mode(_,[])),
    n_arity_count(P,L),
    test1(P,L).

test1(_,[]).

test1(P,[N|Ls]) :-
    n_clause_with_arity(P,N,C),
    n_variable_convert(C,C1),
    infer_clause(C1,State,Env),
    gen_mode(P,State).
    test1(P,Ls).

gen_mode(P,State) :-
    infer_mode(State,Mode),
    mode_pick(Mode,A,B),
    assert(mode(P,A)),
    ifthenelse(
        A == B,
        true,
        assert(mode(P,B))).

mode_pick(S, M1, M2) :-
    pick_cols(S, Pairs),
    split_pairs(Pairs, M1, M2).

pick_cols([[]|_], []) :- !.
pick_cols(S, [P|Ps]) :-
    pick_col(S, P, Rest),
    pick_cols(Rest, Ps).

pick_col([], ?, []).
pick_col([[X|Xs]|Rows], P, [Xs|Rest]) :-
    pick_col(Rows, P0, Rest),
    pick_pair(X, P0, P).

pick_pair(?, P, P) :- !.
pick_pair(X, _, X).

split_pairs([], [], []).
split_pairs(['?'|Xs], ['?'|As], ['?'|Bs]) :-
    split_pairs(Xs, As, Bs).
split_pairs([[A,B]|Xs], [A|As], [B|Bs]) :-
    split_pairs(Xs, As, Bs).

infer_mode([],[]).
infer_mode([S|Ss], [M1|M2]) :-
    infer_mode1(1, S, M1),!,
    infer_mode(Ss,M2).

infer_mode1(N, State, [M|Ms]) :-
    connect_arg(N, State, Arg),!,
    infer_arg_mode(N, Arg, State, M),
    N1 is N + 1,
    infer_mode1(N1, State, Ms).
infer_mode1(_, _, []).

connect_arg(N, [c(N,Arg)|_], Arg) :- !.
connect_arg(N, [_|Xs], Arg) :-
    connect_arg(N, Xs, Arg).

infer_arg_mode(N,Arg,State,['+','-']) :-
    member(e(N,M),State),!.
infer_arg_mode(N,Arg,State,['-','+']) :-
    member(e(M,N),State),!.    
infer_arg_mode(_, Arg, State, ['+','+']) :-
    n_compiler_variable(Arg),
    member(s(Arg,'+'), State),!.
infer_arg_mode(_, Arg, State, ['-','-']) :-
    n_compiler_variable(Arg),
    member(s(Arg,'-'), State),!.
infer_arg_mode(N,[X|Xs], State, M) :- !,
    infer_arg_mode(N,X, State, M1),
    infer_arg_mode(N,Xs, State, M2),
    same_mode(M1, M2, M).
infer_arg_mode(_, _, _, '?').

same_mode(['+','+'], ['+','+'], ['+','+']).
same_mode(['-','-'], ['-','-'], ['-','-']).
same_mode(_, _, ?).

has_input_var(Term, State) :-
    n_compiler_variable(Term),!,
    member(s(Term,+), State).

infer_clause([],[],[]).
infer_clause([C|Cs],[S1|S2],[E1|E2]) :-
    infer_a_clause(C,S1,E1),
    infer_clause(Cs,S2,E2).


infer_a_clause((Head :- Body), State2, Env2) :- 
    term_variables(Head,Env0),
    Head =.. [_|Args],
    infer_head(Args,[],Env0,State1,Env1),
    infer_body(Body,State1,Env1,State2,Env2).

infer_a_clause(Head, State1, Env1) :-
    term_variables(Head,Env0),
    infer_head(Head,[],Env0,State1,Env1).


%infer_head(Args,State,Env,State,Env).
infer_head(Args,State,Env,State2,Env2) :-
    connect_head(Args,State,Env,State1,Env1),
    exclusive_head(Args,State1,Env1,State2,Env2,1).

connect_head(Args,State,Env,State1,Env1) :-
    connect_head1(Args,State,Env,State1,Env1,1).

connect_head1([],State,Env,State,Env,N).
connect_head1([A|As],State,Env,State1,Env1,N) :-
    State2 = [c(N,A)|State],
    N1 is N+1,
    connect_head1(As,State2,Env,State1,Env1,N1).

exclusive_head([A],State,Env,State,Env,N).
exclusive_head([A|As],State,Env,State2,Env2,N) :-
    N1 is N+1,
    exclusive_head1(A,As,State,Env,State1,Env1,N,N1),
    exclusive_head(As,State1,Env1,State2,Env2,N1).

exclusive_head1(A,[],State,Env,State,Env,N,M).
exclusive_head1(A,[B|Bs],State,Env,State1,Env,N,M) :-
    same_struct(A,B),!,
    State2 = [e(N,M)|State],
    M1 is M+1,
    exclusive_head1(A,Bs,State2,Env,State1,Env,N,M1).
exclusive_head1(A,[B|Bs],State,Env,State1,Env,N,M) :-
    M1 is M+1,
    exclusive_head1(A,Bs,State,Env,State1,Env,N,M1).



infer_body(end,State,Env,State,Env).
infer_body((A,B),State,Env,States,Envs) :-
    infer_a_body(A,State,Env,State1,Env1),
    infer_body(B,State1,Env1,States,Envs).
infer_body(A,State,Env,State1,Env1) :- 
    infer_a_body(A,State,Env,State1,Env1),
    infer_body(end,State1,Env1,State1,Env1).


infer_a_body((X is Y),State,Env,[s(X,'-'),s(Y,'+')|State],Env).
infer_a_body((X > Y),State,Env,[s(X,'+'),s(Y,'+')|State],Env).
infer_a_body((X < Y),State,Env,[s(X,'+'),s(Y,'+')|State],Env).
infer_a_body(X,State,Env,State4,[Free|Env]) :-
    n_property(X,predicate),
    functor(X,P,_),
    mode(P,Mode),
    term_variables(X,Vars),
    free_variables(Vars,Env,Free),
    gen_free_state(Free,Vars,State1),
    append(State1,State,State2),
    gen_match(Vars,State2,Match),
    apply_match(Match,Mode,State3),
    append(State3,State2,State4).
infer_a_body(X,State,Env,State2,[Free|Env]) :-
    n_property(X,predicate),
    term_variables(X,Vars),
    free_variables(Vars,Env,Free),
    gen_free_state(Free,Vars,State1),
    append(State1,State,State2).   
infer_a_body(X,State,Env,State2,Env1) :-
    n_property(X,builtin),
    term_variables(X,Vars),
    free_variables(Vars,Env,Free),
    gen_free_state(Free,Vars,State1),
    append(State1,State,State2),
    append(Free,Env,Env1).
infer_a_body(A,State,Env,State,Env).


free_variables([],Env,[]).
free_variables([V|Vs],Env,Fs) :-
    member(V,Env),
    free_variables(Vs,Env,Fs).
free_variables([V|Vs],Env,[V|Fs]) :-
    free_variables(Vs,Env,Fs).

gen_free_state([],_,[]).
gen_free_state([V|Vs],Vars,[a(N,'-')|Fs]) :-
    nth_var(V,Vars,N),
    gen_free_state(Vs,Vars,Fs).

nth_var(F,[F|_],1).
nth_var(F,[_|Vs],N) :-
    nth_var(F,Vs,N1),
    N is N1+1.

gen_match([],State,[]).
gen_match([V|Vs],State,[X|Rs]) :-
    member(s(V,X),State),
    gen_match(Vs,State,Rs).
gen_match([V|Vs],State,[V|Rs]) :-
    gen_match(Vs,State,Rs).

apply_match([],[],State).
apply_match([V|Vs],[M|Ms],[s(V,M)|Ss]) :-
    n_compiler_variable(V),
    apply_match(Vs,Ms,Ss).
apply_match([X|Vs],[X|Ms],Ss) :-
    apply_match(Vs,Ms,Ss).

same_struct(X,Y) :-
    same_struct1(X,Y,0).
same_struct1([],[],N) :-
    N > 0.
same_struct1(X,Y,N) :-
    n_compiler_variable(X),
    n_compiler_variable(Y),
    N > 0.
same_struct1(X,X,_) :-
    n_compiler_variable(X).
same_struct1([X|Xs],[X|Ys],N) :-
    n_compiler_variable(X),
    N1 is N + 1,
    same_struct1(Xs,Ys,N1).
same_struct1([X|Xs],[Y|Ys],N) :-
    n_compiler_variable(X),
    n_compiler_variable(Y),
    same_struct1(Xs,Ys,N).


term_variables(Term, Vars) :-
    term_variables(Term, [], Rev),
    reverse(Rev, Vars).

term_variables(X, Vars, Vars) :-
    atomic(X),
    \+ n_compiler_variable(X), !.

term_variables(X, Vars, Vars) :-
    member_eq(X, Vars), !.

term_variables(X, Vars, [X|Vars]) :-
    n_compiler_variable(X), !.

term_variables(Term, Vars0, Vars) :-
    list(Term),
    term_variables_list(Term, Vars0, Vars).

term_variables(Term, Vars0, Vars) :-
    Term =.. [_|Args],
    term_variables_list(Args, Vars0, Vars).

term_variables_list([], Vars, Vars).


term_variables_list([X|Xs], Vars0, Vars) :-
    list(X),
    term_variables_list(X, Vars0, Vars1),
    term_variables_list(Xs, Vars1, Vars).

term_variables_list([X|Y], Vars0, Vars) :-
    atom(Y),
    term_variables(X, Vars0, Vars1),
    term_variables(Y, Vars1, Vars).

term_variables_list([X|Xs], Vars0, Vars) :-
    term_variables(X, Vars0, Vars1),
    term_variables_list(Xs, Vars1, Vars).


member_eq(X,[Y|_]) :-
    X == Y, !.
member_eq(X,[_|Ys]) :-
    member_eq(X,Ys).
