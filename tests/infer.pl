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
%-----------------------------

test(P) :-
    n_arity_count(P,L),
    test1(P,L).

test1(_,[]).

test1(P,[N|Ls]) :-
    n_clause_with_arity(P,N,C),
    n_variable_convert(C,C1),
    write('clause = '), write(C1), nl,
    infer_clause(C1,State,Env),
    write('State = '),write(State),nl,
    infer_mode(State,Mode),
    write('Mode = '),write(Mode),nl,
    test1(P,Ls).

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
    member(s(Arg,'+'), State),!.
infer_arg_mode(_, Arg, State, ['-','-']) :-
    member(s(Arg,'-'), State),!.
infer_arg_mode(_, _, _, ?).

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
infer_a_body((X > Y),State,Env,[s(X,'+'),s(Y,'-')|State],Env).
infer_a_body((X < Y),State,Env,[s(X,'+'),s(Y,'-')|State],Env).
infer_a_body(A,State,Env,State,Env).

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
