% new compiler nondet

% clause as tail recursive
gen_a_pred5((Head :- Body),N) :-
    tail_body(Head,Body),
    Head =.. [P|Args],
    length(Args,L),
    pred_data(P,L,tail),
    write('save1 = Jget_wp(th);'),nl,
	gen_head(Head),
    gen_tail_body(Body,N).


% clause
gen_a_pred5((Head :- Body),N) :-
    write('save1 = Jget_wp(th);'),nl,
	gen_head(Head),
    gen_body(Body,N).

% predicate with no arity
gen_a_pred5(P,_) :-
	n_property(P,predicate),
    functor(P,_,0),
    not(n_dynamic_predicate(P)),
    write('return(Jprove_all(rest,Jget_sp(th),th));'),nl.

gen_a_pred5(P,_) :-
    n_property(P,predicate),
    functor(P,_,0),
    n_dynamic_predicate(P),
    write('Jmakepred("'),
    write(P),
    write(')'),nl.

% predicate
gen_a_pred5(P,_) :-
	n_property(P,predicate),
    P =.. [P1|_],
    not(n_dynamic_predicate(P1)),
    write('save1 = Jget_wp(th);'),nl,
	gen_head(P),
    write('if(Jprove_all(rest,Jget_sp(th),th) == YES) return(YES);'),nl,
    write('Jset_ac(save3,th);'),nl,
    write('Junbind(save2,th);'),nl,
    write('Jset_wp(save1,th);'),nl.

gen_a_pred5(P,_) :-
    n_property(P,predicate),
    P =.. [P1|L],
    n_dynamic_predicate(P),
    write('Jwcons(Jmakepred("'),
    write(P1),
    write('"),'),
    gen_argument(L),
    write(')').



% user ope
gen_a_pred5(P,_) :-
	n_property(P,userop),
    write('save1 = Jget_wp(th);'),nl,
	gen_head(P),
    write('if(Jprove_all(rest,Jget_sp(th),th) == YES) return(YES);'),nl,
    write('Jset_ac(save3,th);'),nl,
    write('Junbind(save2,th);'),nl,
    write('Jset_wp(save1,th);'),nl.



% varA,varB,...
gen_all_var([]).
gen_all_var([L|Ls]) :-
    n_atom_convert(L,L1),
	write(L1),
    write(','),
    gen_all_var(Ls).

% varA = Jmakevariant(th), varB = Jmakevariant(th);
gen_var([]).
gen_var([L|Ls]) :-
    n_atom_convert(L,L1),
    write(L1),
    write(' = Jmakevariant(th);'),nl,
    gen_var(Ls).


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
gen_nondet_body((X->Y;Z),N,N,B) :-
    true.
gen_nondet_body((X;(Y1;Y2)),N,M,B) :-
    true.
gen_nondet_body((X;Y),N,M,B) :-
    gen_nondet_body(X,N,M,B),
    gen_nondet_body(Y,N,M,B).
gen_nondet_body(X,N,M,B) :-
    gen_a_nondet_body(X,N,M,B).

% case
% transform if-then-else / if-then 
% to argument of case/1
case_arg((Cond -> Then ; Else), [Cond -> Then1 | Else1]) :-
    case_body(Then, Then1),
    case_body(Else, Else1).

case_arg((Cond -> Then), [Cond -> Then1 | true]) :-
    case_body(Then, Then1).

% parse body recursively
case_body((P,Q), (P1,Q1)) :-
    case_body(P, P1),
    case_body(Q, Q1).

% nested if-then-else transform case/1 
case_body((Cond -> Then ; Else), Case) :-
    case_arg((Cond -> Then ; Else), L),
    Case =.. [case, L].

% nested if-then transform to case/1.
case_body((Cond -> Then), Case) :-
    case_arg((Cond -> Then), L),
    Case =.. [case, L].

case_body(X, X).


gen_a_nondet_body((X->Y;Z)) :-
    write('Jcall_det(Jmakesys("case"),'),
    case_arg((X->Y;Z),L),
    gen_argument_list(L),
    write(',th)').

gen_a_nondet_body(X) :-
    n_defined_predicate(X),
    functor(X,P,0),
    n_dynamic_predicate(P),
    write('Jcall_det(Jmakepred("'),
    write(P),
    write('"),th)').


% atom compiled predicate in module 
gen_a_nondet_body(X) :-
    functor(X,P,0),
    n_property(P,compiled),
    write('Jcall_det(Jmakecomp("'),
    write(P),
    write('"),th)').

% atom predicate in module
gen_a_nondet_body(X) :-
    functor(X,P,0),
    n_property(P,predicate),
    n_imported_predicate(P),
    write('Jcall_det(Jmakepred("'),
    write(P),
    write('"),th)').

% compound compiled predicate in module
gen_a_nondet_body(X) :-
    X =.. [P|L],
    n_property(P,compiled),
    write('Jcall_det(Jmakecomp("'),
    write(P),
    write('"),'),
    gen_argument(L),
    write(',th)').

% compound predicate in module
gen_a_nondet_body(X) :-
    X =.. [P|L],
    n_property(P,predicate),
    n_imported_predicate(P),
    write('Jcall_det(Jmakepred("'),
    write(P),
    write('"),'),
    gen_argument(L),
    write(',th)').


% defined predicate will become compiled predicate
gen_a_nondet_body(X) :-
    n_defined_predicate(X),
    functor(X,P,0),
    not(n_dynamic_predicate(P)),
    write('Jmakecomp("'),
    write(P),
    write('")').

% defined predicate will become compiled predicate
gen_a_nondet_body(X) :-
    n_defined_predicate(X),
    X =.. [P|L],
    not(n_dynamic_predicate(P)),
    write('Jcall(Jmakecomp("'),
    write(P),
    write('"),'),
    gen_argument(L),
    write(',th)').

gen_a_nondet_body(X) :-
    n_property(X,predicate),
    X =.. [P|L],
    write('Jcall(Jmakepred("'),
    write(P),
    write('"),'),
    gen_argument(L),
    write(',th)').
% is/2 
gen_a_nondet_body(X is Y) :-
    n_findatom(is,builtin,A),
    write('Jwcons('),
    write(A),
    write(','),
    write('Jwlist2('),
    gen_form(X),
    write(','),
    gen_form(Y),
    write(',th),th)').
% </2 
gen_a_nondet_body(X < Y) :-
    n_findatom(<,builtin,A),
    write('Jwcons('),
    write(A),
    write(','),
    write('Jwlist2('),
    gen_form(X),
    write(','),
    gen_form(Y),
    write(',th),th)').

% >/2 
gen_a_nondet_body(X > Y) :-
    n_findatom(>,builtin,A),
    write('Jwcons('),
    write(A),
    write(','),
    write('Jwlist2('),
    gen_form(X),
    write(','),
    gen_form(Y),
    write(',th),th)').

% =</2 
gen_a_nondet_body(X =< Y) :-
    n_findatom(=<,builtin,A),
    write('Jwcons('),
    write(A),
    write(','),
    write('Jwlist2('),
    gen_form(X),
    write(','),
    gen_form(Y),
    write(',th),th)').

% >=/2 
gen_a_nondet_body(X >= Y) :-
    n_findatom(>=,builtin,A),
    write('Jwcons('),
    write(A),
    write(','),
    write('Jwlist2('),
    gen_form(X),
    write(','),
    gen_form(Y),
    write(',th),th)').

% ==/2 
gen_a_nondet_body(X == Y) :-
    n_findatom(==,builtin,A),
    write('Jwcons('),
    write(A),
    write(','),
    write('Jwlist2('),
    gen_form(X),
    write(','),
    gen_form(Y),
    write(',th),th)').

% =:=/2 
gen_a_nondet_body(X =:= Y) :-
    n_findatom(=:=,builtin,A),
    write('Jwcons('),
    write(A),
    write(','),
    write('Jwlist2('),
    gen_form(X),
    write(','),
    gen_form(Y),
    write(',th),th)').

% \=/2 
gen_a_nondet_body(X \= Y) :-
    n_findatom(\=,builtin,A),
    write('Jwcons('),
    write(A),
    write(','),
    write('Jwlist2('),
    gen_form(X),
    write(','),
    gen_form(Y),
    write(',th),th)').

% atom builtin e.g. nl fail
gen_a_nondet_body(X) :-
    n_property(X,builtin),
    functor(X,P,0),
    n_findatom(P,builtin,A),
    write(A).

gen_a_nondet_body(X) :-
    n_property(X,builtin),
    X =.. [P|L], 
    n_findatom(P,builtin,A),
    write('Jwcons('),
    write(A),
    write(','),
    gen_argument(L),
    write(',th)').
gen_a_nondet_body(X) :-
    n_property(X,operation),
    gen_body1(X,0).
gen_a_nondet_body(X) :-
    n_property(X,compiled),
    X =.. [P|L],
    write('Jwcons(Jmakecomp("'),
    write(P),
    write('"),'),
    gen_argument(L),
    write(',th)').
gen_a_nondet_body(X) :-
    n_property(X,userop),
    functor(X,P,0),
    write('Jmakeuser("'),
    write(P),
    write('")').
gen_a_nondet_body(X) :-
    n_defined_userop(X),
    not(n_imported_userop(X)),
    X =.. [P|L],
    write('Jwcons(Jmakecomp("'),
    write(P),
    write('"),'),
    gen_argument(L),
    write(',th)').
gen_a_nondet_body(X) :-
    n_property(X,userop),
    X =.. [P|L],
    write('Jwcons(Jmakeuser("'),
    write(P),
    write('"),'),
    gen_argument(L),
    write(',th)').
gen_a_nondet_body(X) :-
    atom(X),
    n_dynamic_predicate(X),
	write('Jmakepred("'),
    write(X),
    write('")').
% for FCG {} compile
gen_a_nondet_body(',') :-
    write('Jmakesys("n_exec_no_operation")').
gen_a_nondet_body(X) :-
    invoke_error('illegal body ',X).

