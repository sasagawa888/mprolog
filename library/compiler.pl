
%:- module(jump,[compile_file/1,compile_file1/1,compile_file/2,type/2,mode/3]).

%type(f,a,t).  (functor,arity,type) nondet det tail dyn mut
%mode(f,1,[+]).  (functor,arity,modelist)

option(non,non). % for GCC option 

% main
compile_file(X) :-
    pass1(X),
    pass2(X),
    pass3(X),
    invoke_gcc(X).

compile_file(X,c) :-
    compile_file1(X).
    
compile_file(X,o) :-
    compile_file2(X).

compile_file(X,a) :-
    compile_file3(X).

compile_file(X,d) :-
    compile_file4(X).



% genrate only c code 
compile_file1(X) :-
    pass1(X),
    pass2(X),
    pass3(X).

% generate object from c code
compile_file2(X) :-
    invoke_gcc_not_remove(X).

% only analize
compile_file3(X) :-
    pass1(X),
    pass2(X).

% debug print 
compile_file4(X) :-
    assertz(option(debug,on)),
    pass1(X),
    pass2(X),
    pass3(X),
    retract(option(debug,on)),
    invoke_gcc(X).

pass1(X) :-
    assertz((type(dummy,dummy,dummy))),
	write(user_output,'phase pass1'),
    nl(user_output),
    reconsult(X,compiler),
    analize.

pass2(_) :-
    write(user_output,'phase pass2'),
    nl(user_output),
    analize,
    retype_halt.

retype_halt :-
    retract(type(P,A,halt)),
    asserta(type(P,A,nondet)),
    fail.
retype_halt.


pass3(X) :-
	write(user_output,'phase pass3'),nl(user_output),
	n_filename(X,F),
    atom_concat(F,'.c',Cfile),
	tell(Cfile),
	write('#include "jump.h"'),nl,
    gen_protopype,
    gen_predicate,
    gen_definition,
    gen_execution,
    n_reconsult_abolish,
    told.

/*
when OS is Linux
system builtin predicate invoke GCC
gcc -O3 -w -shared -fPIC -o <filenam>.c <filename>.o <option>
*/
invoke_gcc(X) :-
	write(user_output,'invoke GCC'),nl(user_output),
	n_filename(X,F),
    atom_concat(F,'.c ',Cfile),
    atom_concat(F,'.o ',Ofile),
    atom_concat(Ofile,Cfile,Files),
    atom_concat('gcc -O3 -flto -w -shared -fPIC -I$HOME/mprolog -o ',Files,Gen1),
    (option(library,Opt1),atom_string(Opt,Opt1),atom_concat(Gen1,Opt,Gen) ; Gen = Gen1),
    shell(Gen),
    atom_concat('rm ',Cfile,Del),
    shell(Del).

invoke_gcc_not_remove(X) :-
	write(user_output,'invoke GCC'),
    nl(user_output),
	n_filename(X,F),
    atom_concat(F,'.c ',Cfile),
    atom_concat(F,'.o ',Ofile),
    atom_concat(Ofile,Cfile,Files),
    atom_concat('gcc -O3 -flto -w -shared -fPIC -I$HOME/mprolog -o ',Files,Gen),
    shell(Gen).


/*
void init_tpredicate(void){
(deftpred)("p",c_p,1,1);
(deftpred)("foo",c_foo,0,1);
}
*/
% define compiled predicate
gen_definition :-
	write('void init_tpredicate(void){'),nl,
    gen_definition1,
    write('}'),nl.

gen_definition1 :-
    n_reconsult_predicate(P),
    not(n_dynamic_predicate(P)),
    P \= cdeclare,
    P \= clibrary,
	gen_pred_def(P),
    fail.
gen_definition1.


% generate deftpred for normal predicate
gen_pred_def(P) :-
    n_defined_predicate(P),
    n_atom_convert(P,P1),
    type(P,A,T),
    pred_type(T,T1),
	write('(deftpred)("'),write(P),write('",'),write('c_'),write(P1),
    write(','),write(A),write(','),write(T1),write(');'),nl,!.

pred_type(nondet,1).
pred_type(det,2).
pred_type(tail,3).
pred_type(dyn,4).
pred_type(mut,5).
pred_type(recur,6).

% generate deftinfix for user op
gen_def(P) :-
    n_defined_userop(P),
    n_atom_convert(P,P1),
    current_op(W,S,P),
    spec_to_c(S,S1),
	write('(deftinfix)("'),write(P),write('",'),write('c_'),write(P1),write(','),
    write(W),write(','),write(S1),write(');'),nl,!.

/*
last C code to make direct execute
void init_declare(void){
    execute code...
}
*/
gen_execution :-
	write('void init_declare(void){'),nl,
    gen_dyn_exec,
    gen_det_exec,
    write('}').


/* generate execute definition of dynamic clause*/
gen_dyn_exec :-
    write('int body,th; th=0;'),nl,
    n_get_dynamic(X),
    gen_dyn_exec1(X).

gen_dyn_exec1([]).
gen_dyn_exec1([L|Ls]) :-
    write(L),
    write('();'),nl,
    gen_dyn_exec1(Ls).



/*
e.g. :- op(...)
generate execution 
*/
gen_det_exec :-
    n_get_execute(X),
    gen_det_exec1(X).

gen_det_exec1([]).
gen_det_exec1([L|Ls]) :-
    gen_det_exec2(L),
    nl,
    gen_det_exec1(Ls).


gen_det_exec2(X) :-
    write('body = '),gen_dyn_elt(X),write(';'),nl,
    write('Jprove_all(body,Jget_sp(th),th);'),!.



spec_to_c(fx,'FX').
spec_to_c(fy,'FY').
spec_to_c(xfx,'XFX').
spec_to_c(xfy,'XFY').
spec_to_c(yfx,'YFX').
spec_to_c(xf,'XF').
spec_to_c(yf,'YF').
spec_to_c(fx_xfx,'FX_XFX').
spec_to_c(fy_xfx,'FY_XFX').
spec_to_c(fx_yfx,'FX_YFX').
spec_to_c(fy_yfx,'FY_YFX').
spec_to_c(fx_xf,'FX_XF').
spec_to_c(fx_yf,'FX_YF').
spec_to_c(fy_xf,'FY_XF').
spec_to_c(fy_yf,'FY_YF').

% generate all function prototype
gen_protopype :-
    n_reconsult_predicate(P),
    gen_type_declare(P),
    fail.
gen_protopype.

% generate all predicate code
gen_predicate :-
    n_reconsult_predicate(P),
    P = cdeclare,
    gen_cdeclare(P),
    fail.
gen_predicate :-
    n_reconsult_predicate(P),
    P = clibrary,
    gen_clibrary(P),
    fail.
gen_predicate :-
    n_reconsult_predicate(P),
    gen_a_pred(P),
    fail.
gen_predicate.

% generate predicate P
gen_a_pred(P) :- 
    type(P,_,nondet),gen_nondet_pred(P).  
gen_a_pred(P) :- 
    type(P,_,recur),gen_recur_pred(P).     
gen_a_pred(P) :- 
    type(P,_,det),gen_det_pred(P).
gen_a_pred(P) :- 
    type(P,_,tail),gen_tail_pred(P).
gen_a_pred(P) :- 
    type(P,_,dyn),gen_dyn_pred(P).
gen_a_pred(P) :- 
    type(P,_,mut),gen_mut_pred(P).


/*
parts for gen_predicate
C type declare.
static int c_foo(int arglist, int rest);
*/
gen_type_declare(P) :-
    n_atom_convert(P,P1),
	write('static int c_'),write(P1),write('(int arglist, int rest, int th);'),nl.
/*
C variable declare.
generate following code
int(int arg1,arg2,...,argN){
int arg1,arg2 ... argN,body,save1,save2...;

*/
gen_var_declare(P) :-
    n_arity_count(P,L),
    max_list(L,E),
    n_generate_all_variable(P,V),
    write('int '),
    gen_var_declare1(1,E),
    gen_all_var(V),
    write('n,body,save1,save2,save3,goal,cont,clause,res;'),nl,!.

max_list([N],N).
max_list([X|Xs],X) :-
    max_list(Xs,Y),
    X >= Y.
max_list([X|Xs],Y) :-
    max_list(Xs,Y),
    X < Y.

% arg1,arg2,...argN
gen_var_declare1(S,E) :-
	S > E.
gen_var_declare1(S,E) :-
	write(arg),write(S),write(','),
    S1 is S+1,
    gen_var_declare1(S1,E).


% arg1 = Jcar(arglist);
% arg2 = Jnth(arglist,2);
% argn = Jnth(artglist,n);
gen_var_assign(S,E) :-
	S > E.
gen_var_assign(1,E) :-
    write('arg1 = Jcar(arglist);'),nl,
    S1 is 2,
    gen_var_assign(S1,E).
gen_var_assign(S,E) :-
	write(arg),
    write(S),
    write(' = Jnth(arglist,'),
    write(S),
    write(');'),nl,
    S1 is S+1,
    gen_var_assign(S1,E).


gen_jump_switch(P,A):-
    n_clause_count_with_arity(P,A,M),
    write('clause = Jget_choice(th);'),nl,
    write('switch(clause){'),nl,
    gen_jump_switch1(A,0,M),
    write('}'),nl.

gen_jump_switch1(A,M,M) :-
    write('default: goto allfail;'),nl.
gen_jump_switch1(A,M,N) :-
    write('case '),write(M),write(': '),
    write('goto '),write('clause_'),write(A),write('_'),write(M),write(';'),nl,
    S is M+10000,
    write('case '),write(S),write(': '),
    write('goto '),write('skip_'),write(A),write('_'),write(M),write(';'),nl,
    M1 is M+1,
    gen_jump_switch1(A,M1,N).


gen_disj_jump_switch(X,A,M,N):-
    write('int disj = Jget_disj_choice(th);'),nl,
    write('switch(disj){'),nl,
    gen_disj_jump_switch1(X,A,M,N,0),
    write('}'),nl.

gen_disj_jump_switch1((X;Y),A,M,N,L) :-
    write('case '),write(L),write(': '),
    write('goto '),write('disj_'),write(A),write('_'),
    write(M),write('_'),write(N),write('_'),write(L),write(';'),nl,
    L1 is L+1,
    gen_disj_jump_switch1(Y,A,M,N,L1).
gen_disj_jump_switch1(end_of_disjunction,A,M,N,L) :-
    M1 is M+1,
    write('default: Jreset_disj_choice(th);'),nl,
    write('goto clause_'),write(A),write('_'),write(M1),write(';'),nl.
gen_disj_jump_switch1(X,A,M,N,L) :-
    gen_disj_jump_switch1((X;end_of_disjunction),A,M,N,L).


/* --------------------nondet-----------------------------------
*/
gen_nondet_pred(P) :-
	atom_concat('compiling ',P,M),
    write(user_output,M),
	write('static int c_'),
    n_atom_convert(P,P1),
    write(P1),
    write('(int arglist, int rest, int th){'),nl,
    gen_var_declare(P),
    write('n = Jarity_count(arglist);'),nl,
    ifthenelse(option(debug,on),gen_debug(P),true),
    n_arity_count(P,L),
    gen_nondet_pred1(P,L),
    write('}'),nl.

gen_nondet_pred1(P,[]) :-
    nl,
    write('Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("'),
    write(P),
    write('"),arglist);'),nl,
	write('return(NO);').

gen_nondet_pred1(P,[A|As]) :-
    write(user_output,$/$),write(user_output,A),
    write(user_output,' nondet'),nl(user_output),
    gen_nondet_arity(P,A),
    gen_nondet_pred1(P,As).

gen_nondet_arity(P,A) :-
	write('if(n == '),
    write(A),
    write('){'),nl,
    gen_nondet_clause(P,A),
    write('allfail:'),nl,
    write('Jdiscard_conj(th);'),nl,
    write('return(NO);}'),nl,!.

% select all clauses that arity is A
gen_nondet_clause(P,A) :-
    gen_var_assign(1,A),
    gen_jump_switch(P,A),
    write('clause_'),write(A),write('_0:'),nl,
	n_clause_with_arity(P,A,C),
    gen_nondet_clause1(C,A,0).

% generate each clause 
gen_nondet_clause1([],_,_).
gen_nondet_clause1([C|Cs],A,M) :-
	n_variable_convert(C,X),
    n_generate_variable(X,V),
    gen_var(V),
    gen_a_nondet_clause(X,A,M),
    M1 is M+1,
    gen_nondet_clause1(Cs,A,M1).


% N is arity , M is Mth clause from 0.
% clause

gen_a_nondet_clause((Head :- Body),A,M) :-
    write('Jinc_choice(th);'),nl,
	gen_head(Head),write('{'),nl,
    write('skip_'),write(A),write('_'),write(M),write(':;'),nl,
    gen_nondet_body(Body,A,ret,M,Head),write('}'),nl,
    M1 is M+1,
    write('clause_'),write(A),write('_'),write(M1),write(':'),nl,
    write('Jrelease(th);'),nl.

% predicate with no arity
gen_a_nondet_clause(P,A,M) :-
	n_property(P,predicate),
    functor(P,_,0),
    write('Jinc_choice(th);'),nl,
    write('{skip_'),write(A),write('_'),write(M),write(':'),nl,
    write('return(YES);}'),nl.

% nondet predicate
gen_a_nondet_clause(P,A,M) :-
	n_property(P,predicate),
    P =.. [P1|_],
    write('Jinc_choice(th);'),nl,
	gen_head(P),
    write('{skip_'),write(A),write('_'),write(M),write(':'),nl,
    write('return(YES);}'),nl,
    M1 is M+1,
    write('clause_'),write(A),write('_'),write(M1),write(':'),nl,
    write('Jrelease(th);'),nl.

gen_a_nondet_clause(P,_,M) :-
	n_property(P,userop),
	gen_head(P),
    write('{Jinc_choice(th);'),nl,
    write('skip_'),write(A),write('_'),write(M),write(':'),nl,
    write('return(YES);}'),nl,
    M1 is M+1,
    write('clause_'),write(A),write('_'),write(M1),write(':'),nl,
    write('Jrelease(th);'),nl.




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


% X=body A=arity O=ret/res/rec L=disjunction-number H=Head
gen_nondet_body(X,A,O,M,H) :-
    gen_nondet_body1(X,A,M,0,[],O,0,H).

% A is arith Mth clause, Nth body B-retry[A,M,N] Option L-disjuncion-num Head
gen_nondet_body1((!,Y),A,M,N,B,O,L,H) :-
    gen_nondet_body1(Y,A,M,N,[],O,L,H).
gen_nondet_body1((fail,Y),A,M,N,[],O,L,H) :-
    gen_nondet_body_fail([A,M]),nl,
    N1 is N+1,
    gen_nondet_body1(Y,A,M,N1,[],O,L,H).
gen_nondet_body1((fail,Y),A,M,N,B,O,L,H) :-
    gen_nondet_body_fail_retry(B),nl,
    N1 is N+1,
    gen_nondet_body1(Y,A,M,N1,B,O,L,H).
gen_nondet_body1((X,Y),A,M,N,B,O,L,H) :-
    n_property(X,builtin),
    X =.. [P|Args],
    write('if (Jcall_det(Jmakesys("'),write(P),write('"),'),gen_a_argument(Args),write(',th) == YES){'),nl,
    N1 is N+1,
    gen_nondet_body1(Y,A,M,N1,B,O,L,H),
    write('}'),
    gen_nondet_body_retry(B),nl.
gen_nondet_body1((X,Y),A,M,N,B,O,L,H) :-
     n_property(X,predicate),
    X =.. [P|Args],
    functor(X,_,Arity),
    type(P,Arity,det),
    write('if (Jcall_det(Jmakecomp("'),write(P),write('"),'),gen_a_argument(Args),write(',th) == YES){'),nl,
     N1 is N+1,
    gen_nondet_body1(Y,A,M,N1,B,O,L,H),
    write('}'),
    gen_nondet_body_retry(B),nl.

gen_nondet_body1((X,Y),A,M,N,B,O,L,H) :-
    n_property(X,predicate),
    X =.. [P|Args],
    functor(X,_,Arity),
    type(P,Arity,recur),
    gen_nondet_body_argument(X,A,M,N),
    write('Jpush_recur(th);'),nl,
    gen_nondet_body_label([A,M,N]),
    write('if (c_'),write(P),write('(arg_'),write(A),write('_'),write(M),write('_'),write(N),
    write(',NIL,th) == YES){'),nl,
    write('Jpop_recur(th);'),nl,
    N1 is N+1,
    gen_nondet_body1(Y,A,M,N1,[A,M,N],rec,L,H),
    write('}'),
    gen_nondet_body_retry(B),nl.

gen_nondet_body1((X,Y),A,M,N,B,O,L,H) :-
     n_property(X,predicate),
    X =.. [P|Args],
    functor(X,_,Arity),
    type(P,Arity,nondet),
    write('Jpush_conj(th);'),nl,
    gen_nondet_body_label([A,M,N]),
    gen_nondet_body_argument(X,A,M,N),
    write('if (c_'),write(P),write('(arg_'),write(A),write('_'),write(M),write('_'),write(N),
    write(',NIL,th) == YES){'),nl,
    N1 is N+1,
    gen_nondet_body1(Y,A,M,N1,[A,M,N],O,L,H),
    write('}'),
    gen_nondet_body_retry(B),nl.
gen_nondet_body1(((X1;X2),Y),A,M,N,B,O,L,H) :-
    write('res = NIL;'),nl,
    ifthenelse(L=:=0,gen_disj_jump_switch((X1;X2),A,M,N),true),
    gen_nondet_body_disj_label([A,M,N,L]),
    write('Jinc_disj_choice(th);'),nl,
    gen_nondet_body1(X1,A,M,N,B,res,L,H),
    write('if(res == YES) goto '),gen_nondet_body_exit([A,M,N]),nl,
    L1 is L+1,
    gen_nondet_body_disj_label([A,M,N,L1]),
    write('Jinc_disj_choice(th);'),nl,
    write('Jrelease(th);'),nl,
    gen_nondet_body1(X2,A,M,N,B,res,L1,H),
    ifthenelse(L=:=0,gen_nondet_body_exit_label([A,M,N]),true),
    N1 is N+1,
    gen_nondet_body1(Y,A,M,N,B,O,L,H),
    ifthenelse(L=:=0,(write('if(rest!=NIL) Jreset_disj(th);'),nl),true).
gen_nondet_body1(!,A,M,N,[],O,L,H) :-
    write('{Jmax_choice(th); return(YES);}'),nl.    
gen_nondet_body1(end_of_body,A,M,N,B,ret,L,H) :-
    write('{Jsuccess(arglist,th); return(YES);}'),nl.
gen_nondet_body1(end_of_body,A,M,N,B,res,L,H) :-
    write('res = YES;'),nl.
gen_nondet_body1(end_of_body,A,M,N,B,rec,L,H) :-
    write('return(YES);'),nl.
gen_nondet_body1(X,A,M,N,B,O,L,H) :-
    gen_nondet_body1((X,end_of_body),A,M,N,B,O,L,H).


gen_nondet_body_label([A,M,N]) :-
    write('retry_'),write(A),write('_'),write(M),write('_'),write(N),write(':;'),nl.

gen_nondet_body_disj_label([A,M,N,L]) :-
    write('disj_'),write(A),write('_'),write(M),write('_'),write(N),write('_'),write(L),write(':'),nl.

gen_nondet_body_exit_label([A,M,N]) :-
    write('exit_'),write(A),write('_'),write(M),write('_'),write(N),write(':'),nl.

gen_nondet_body_exit([A,M,N]) :-
    write('exit_'),write(A),write('_'),write(M),write('_'),write(N),write(';'),nl.


gen_nondet_body_retry([]).
gen_nondet_body_retry([A,M,N]) :-
    write('else goto retry_'),write(A),write('_'),write(M),write('_'),write(N),write(';').

gen_nondet_body_fail_retry([A,M,N]) :-
    write('goto retry_'),write(A),write('_'),write(M),write('_'),write(N),write(';').

gen_nondet_body_fail([A,M]) :-
    write('goto clause_'),write(A),write('_'),write(M1),write(';').


gen_nondet_body_argument(X,A,M,N) :-
    X =.. [_|Args],
    write('int '),write('arg_'),write(A),write('_'),write(M),write('_'),write(N),write(' = '),
    gen_a_argument(Args),write(';'),nl.

recur_body(X,H) :-
    functor(X,P,A),
    functor(H,P,A).

/*
generate_unify of head
e.g.  foo(X) -> if(Junify(arg1,varX,th) == YES)
anonymous variable generate 1 as true.
e.g   foo(_) -> if(1)
*/

gen_head(X) :-
    functor(X,_,0).
gen_head(X) :-
    X =.. [_|Y],
    write('if('),
    gen_head1(Y,1),
    write(')\n').

gen_head1([],_).

gen_head1([[]|Xs],N) :-
    write('Junify_nil('),
    write('arg'),
    write(N),
    write(','),
    write(th),
    write(') == YES'),
    ifthenelse(Xs \= [],write(' && '),true),
    N1 is N + 1,
    gen_head1(Xs,N1).

gen_head1([X|Xs],N) :-
    n_compiler_anonymous(X),
    write('Junify_var(arg'),
    write(N),
    write(','),
    gen_a_argument(X),
    write(',th) == YES'),
    ifthenelse(Xs \= [],write(' && '),true),
    N1 is N + 1,
    gen_head1(Xs,N1).  

gen_head1([X|Xs],N) :-
    n_compiler_variable(X),
    write('Junify_var(arg'),
    write(N),
    write(','),
    gen_a_argument(X),
    write(',th) == YES'),
    ifthenelse(Xs \= [],write(' && '),true),
    N1 is N + 1,
    gen_head1(Xs,N1). 


gen_head1([X|Xs],N) :-
    n_pair_list(X),
    write('Junify_pair(arg'),
    write(N),
    write(','),
    gen_a_argument(X),
    write(',th) == YES'),
    ifthenelse(Xs \= [],write(' && '),true),
    N1 is N + 1,
    gen_head1(Xs,N1). 


gen_head1([X|Xs],N) :-
    atom(X),
    write('Junify_atom(arg'),
    write(N),
    write(','),
    gen_a_argument(X),
    write(',th) == YES'),
    ifthenelse(Xs \= [],write(' && '),true),
    N1 is N + 1,
    gen_head1(Xs,N1). 


gen_head1([X|Xs],N) :-
    integer(X),
    write('Junify_int(arg'),
    write(N),
    write(','),
    gen_a_argument(X),
    write(',th) == YES'),
    ifthenelse(Xs \= [],write(' && '),true),
    N1 is N + 1,
    gen_head1(Xs,N1). 


gen_head1([X|Xs],N) :-
    n_longnum(X),
    write('Junify_long(arg'),
    write(N),
    write(','),
    gen_a_argument(X),
    write(',th) == YES'),
    ifthenelse(Xs \= [],write(' && '),true),
    N1 is N + 1,
    gen_head1(Xs,N1). 


gen_head1([X|Xs],N) :-
    n_bignum(X),
    write('Junify_big(arg'),
    write(N),
    write(','),
    gen_a_argument(X),
    write(',th) == YES'),
    ifthenelse(Xs \= [],write(' && '),true),
    N1 is N + 1,
    gen_head1(Xs,N1). 


gen_head1([X|Xs],N) :-
    string(X),
    write('Junify_str(arg'),
    write(N),
    write(','),
    gen_a_argument(X),
    write(',th) == YES'),
    ifthenelse(Xs \= [],write(' && '),true),
    N1 is N + 1,
    gen_head1(Xs,N1). 

gen_head1([X|Xs],N) :-
    write('Junify(arg'),
    write(N),
    write(','),
    gen_a_argument(X),
    write(',th) == YES'),
    ifthenelse(Xs \= [],write(' && '),true),
    N1 is N + 1,
    gen_head1(Xs,N1).


/* --------------------recursion-----------------------------------
*/
gen_recur_pred(P) :-
	atom_concat('compiling ',P,M),
    write(user_output,M),
	write('static int c_'),
    n_atom_convert(P,P1),
    write(P1),
    write('(int arglist, int rest, int th){'),nl,
    gen_var_declare(P),
    write('n = Jarity_count(arglist);'),nl,
    write('arglist = Jprepare(arglist,th);'),nl,
    ifthenelse(option(debug,on),gen_debug(P),true),
    n_arity_count(P,L),
    gen_recur_pred1(P,L),
    write('}'),nl.

gen_recur_pred1(P,[]) :-
    nl,
    write('Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("'),
    write(P),
    write('"),arglist);'),nl,
	write('return(NO);').

gen_recur_pred1(P,[A|As]) :-
    write(user_output,$/$),write(user_output,A),
    write(user_output,' recur'),nl(user_output),
    gen_recur_arity(P,A),
    gen_recur_pred1(P,As).

gen_recur_arity(P,A) :-
	write('if(n == '),
    write(A),
    write('){'),nl,
    gen_recur_clause(P,A),
    write('allfail:'),nl,
    write('Jdiscard_recur(th);'),nl,
    write('if(rest != NIL) Jdiscard_conj(th);'),nl,
    write('return(NO);}'),nl,!.

% select all clauses that arity is A
gen_recur_clause(P,A) :-
    gen_var_assign(1,A),
    gen_jump_switch(P,A),
    write('clause_'),write(A),write('_0:'),nl,
	n_clause_with_arity(P,A,C),
    gen_recur_clause1(C,A,0).

% generate each clause 
gen_recur_clause1([],_,_).
gen_recur_clause1([C|Cs],A,M) :-
	n_variable_convert(C,X),
    n_generate_variable(X,V),
    gen_var(V),
    gen_a_recur_clause(X,A,M),
    M1 is M+1,
    gen_recur_clause1(Cs,A,M1).


% N is arity , M is Mth clause from 0.
% clause

gen_a_recur_clause((Head :- Body),A,M) :-
    write('Jinc_choice(th);'),nl,
	gen_head(Head),write('{'),nl,
    write('skip_'),write(A),write('_'),write(M),write(':;'),nl,
    gen_recur_body(Body,A,ret,M,Head),write('}'),nl,
    M1 is M+1,
    write('clause_'),write(A),write('_'),write(M1),write(':'),nl,
    write('Jrelease(th);'),nl.

% predicate with no arity
gen_a_recur_clause(P,A,M) :-
	n_property(P,predicate),
    functor(P,_,0),
    write('{Jinc_choice(th);'),nl,
    write('skip_'),write(A),write('_'),write(M),write(':'),nl,
    write('return(YES);}'),nl.

% nondet predicate
gen_a_recur_clause(P,A,M) :-
	n_property(P,predicate),
    P =.. [P1|_],
    write('Jinc_choice(th);'),nl,
	gen_head(P),
    write('{'),nl,
    write('skip_'),write(A),write('_'),write(M),write(':'),nl,
    write('Jsuccess(arglist,th); return(YES);}'),nl,
    M1 is M+1,
    write('clause_'),write(A),write('_'),write(M1),write(':'),nl,
    write('Jrelease(th);'),nl.

gen_a_recur_clause(P,_,M) :-
	n_property(P,userop),
	gen_head(P),
    write('{Jinc_choice(th);'),nl,
    write('skip_'),write(A),write('_'),write(M),write(':'),nl,
    write('return(YES);}'),nl,
    M1 is M+1,
    write('clause_'),write(A),write('_'),write(M1),write(':'),nl,
    write('Jrelease(th);'),nl.


gen_debug(P) :-
    write('printf("'),write(P),write('");'),
    write('Jprint(Jderef(arglist,th));').

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


% X=body A=arity O=ret/res/rec L=disjunction-number H=Head
gen_recur_body(X,A,O,M,H) :-
    gen_recur_body1(X,A,M,0,[],O,0,H).

% A is arith Mth clause, Nth body B-retry[A,M,N] Option L-disjuncion-num Head
gen_recur_body1((!,Y),A,M,N,B,O,L,H) :-
    gen_recur_body1(Y,A,M,N,[],O,L,H).
gen_recur_body1((fail,Y),A,M,N,[],O,L,H) :-
    gen_recur_body_fail([A,M]),nl,
    N1 is N+1,
    gen_recur_body1(Y,A,M,N1,[],O,L,H).
gen_recur_body1((fail,Y),A,M,N,B,O,L,H) :-
    gen_recur_body_fail_retry(B),nl,
    N1 is N+1,
    gen_recur_body1(Y,A,M,N1,B,O,L,H).
gen_recur_body1((X,Y),A,M,N,B,O,L,H) :-
    n_property(X,builtin),
    X =.. [P|Args],
    write('if (Jcall_det(Jmakesys("'),write(P),write('"),'),gen_a_argument(Args),write(',th) == YES){'),nl,
    N1 is N+1,
    gen_recur_body1(Y,A,M,N1,B,O,L,H),
    write('}'),
    gen_recur_body_retry(B),nl.
gen_recur_body1((X,Y),A,M,N,B,O,L,H) :-
     n_property(X,predicate),
    X =.. [P|Args],
    functor(X,_,Arity),
    type(P,Arity,det),
    write('if (Jcall_det(Jmakecomp("'),write(P),write('"),'),gen_a_argument(Args),write(',th) == YES){'),nl,
     N1 is N+1,
    gen_recur_body1(Y,A,M,N1,B,O,L,H),
    write('}'),
    gen_recur_body_retry(B),nl.

gen_recur_body1((X,Y),A,M,N,B,O,L,H) :-
    n_property(X,predicate),
    X =.. [P|Args],
    functor(X,_,Arity),
    type(P,Arity,recur),
    gen_recur_body_argument(X,A,M,N),
    write('Jpush_recur(th);'),nl,
    gen_recur_body_label([A,M,N]),
    write('if (c_'),write(P),write('(arg_'),write(A),write('_'),write(M),write('_'),write(N),
    write(',NIL,th) == YES){'),nl,
    write('Jpop_recur(th);'),nl,
    N1 is N+1,
    gen_recur_body1(Y,A,M,N1,[A,M,N],rec,L,H),
    write('}'),
    gen_recur_body_retry(B),nl.

gen_recur_body1((X,Y),A,M,N,B,O,L,H) :-
    n_property(X,predicate),
    recur_body(X,H),
    X =.. [P|Args],
    functor(X,_,Arity),
    type(P,Arity,nondet),
    gen_recur_body_argument(X,A,M,N),
    write('Jpush_recur(th);'),nl,
    gen_recur_body_label([A,M,N]),
    write('if (c_'),write(P),write('(arg_'),write(A),write('_'),write(M),write('_'),write(N),
    write(',NIL,th) == YES){'),nl,
    write('Jpop_recur(th);'),nl,
    N1 is N+1,
    gen_recur_body1(Y,A,M,N1,[A,M,N],rec,L,H),
    write('}'),
    gen_recur_body_retry(B),nl.
gen_recur_body1((X,Y),A,M,N,B,O,L,H) :-
     n_property(X,predicate),
    X =.. [P|Args],
    functor(X,_,Arity),
    type(P,Arity,nondet),
    write('Jpush_conj(th);'),nl,
    gen_recur_body_label([A,M,N]),
    gen_recur_body_argument(X,A,M,N),
    write('if (c_'),write(P),write('(arg_'),write(A),write('_'),write(M),write('_'),write(N),
    write(',NIL,th) == YES){'),nl,
    N1 is N+1,
    gen_recur_body1(Y,A,M,N1,[A,M,N],O,L,H),
    write('}'),
    gen_recur_body_retry(B),nl.
gen_recur_body1(((X1;X2),Y),A,M,N,B,O,L,H) :-
    write('res = NIL;'),nl,
    ifthenelse(L=:=0,gen_disj_jump_switch((X1;X2),A,M,N),true),
    gen_recur_body_disj_label([A,M,N,L]),
    write('Jinc_disj_choice(th);'),nl,
    gen_recur_body1(X1,A,M,N,B,res,L,H),
    write('if(res == YES) goto '),gen_recur_body_exit([A,M,N]),nl,
    L1 is L+1,
    gen_recur_body_disj_label([A,M,N,L1]),
    write('Jinc_disj_choice(th);'),nl,
    write('Jrelease(th);'),nl,
    gen_recur_body1(X2,A,M,N,B,res,L1,H),
    ifthenelse(L=:=0,gen_recur_body_exit_label([A,M,N]),true),
    N1 is N+1,
    gen_recur_body1(Y,A,M,N,B,O,L,H),
    ifthenelse(L=:=0,(write('if(rest!=NIL) Jreset_disj(th);'),nl),true).
gen_recur_body1(!,A,M,N,[],O,L,H) :-
    write('{Jmax_choice(th); return(YES);}'),nl.    
gen_recur_body1(end_of_body,A,M,N,B,ret,L,H) :-
    write('{Jsuccess(arglist,th); return(YES);}'),nl.
gen_recur_body1(end_of_body,A,M,N,B,res,L,H) :-
    write('res = YES;'),nl.
gen_recur_body1(end_of_body,A,M,N,B,rec,L,H) :-
    write('return(YES);'),nl.
gen_recur_body1(X,A,M,N,B,O,L,H) :-
    gen_recur_body1((X,end_of_body),A,M,N,B,O,L,H).


gen_recur_body_label([A,M,N]) :-
    write('retry_'),write(A),write('_'),write(M),write('_'),write(N),write(':;'),nl.

gen_recur_body_disj_label([A,M,N,L]) :-
    write('disj_'),write(A),write('_'),write(M),write('_'),write(N),write('_'),write(L),write(':'),nl.

gen_recur_body_exit_label([A,M,N]) :-
    write('exit_'),write(A),write('_'),write(M),write('_'),write(N),write(':'),nl.

gen_recur_body_exit([A,M,N]) :-
    write('exit_'),write(A),write('_'),write(M),write('_'),write(N),write(';'),nl.


gen_recur_body_retry([]).
gen_recur_body_retry([A,M,N]) :-
    write('else{Jset_mode(RETRY,th);'),nl,
    write('goto retry_'),write(A),write('_'),write(M),write('_'),write(N),write(';}').

gen_recur_body_fail_retry([A,M,N]) :-
    write('Jset_mode(RETRY,th);'),nl,
    write('goto retry_'),write(A),write('_'),write(M),write('_'),write(N),write(';').

gen_recur_body_fail([A,M]) :-
    write('goto clause_'),write(A),write('_'),write(M1),write(';').


gen_recur_body_argument(X,A,M,N) :-
    X =.. [_|Args],
    write('int '),write('arg_'),write(A),write('_'),write(M),write('_'),write(N),write(' = '),
    gen_a_argument(Args),write(';'),nl.

%---------------det determinant predicate-------------------
gen_det_pred(P) :-
	atom_concat('compiling ',P,M),
    write(user_output,M),
	write('static int c_'),
    n_atom_convert(P,P1),
    write(P1),
    write('(int arglist, int rest, int th){'),nl,
    gen_var_declare(P),
    write('Jinc_proof(th);'),nl,
    write('n = Jarity_count(arglist);'),nl,
    write('save1 = Jget_wp(th);'),nl,
    write('save2 = Jget_sp(th);'),nl,
    write('save3 = Jget_ac(th);'),nl,
    n_arity_count(P,L),
    gen_det_pred1(P,L),
    write('}'),nl.

gen_det_pred1(P,[]).
gen_det_pred1(P,[A|As]) :-
    write(user_output,$/$),write(user_output,A),
    write(user_output,' '),write(user_output,det),nl(user_output),
	gen_det_arity(P,A),
    gen_det_pred1(P,As).

gen_det_arity(P,A) :-
	write('if(n == '),write(A),write('){'),nl,
    gen_det_clause(P,A),
    write('return(NO);}'),nl,!.

gen_det_clause(P,A) :-
    gen_var_assign(1,A),
	n_clause_with_arity(P,A,C),
    gen_det_clause1(C,A,0).

gen_det_clause1([],_,_).
gen_det_clause1([C|Cs],A,M) :-
	n_variable_convert(C,X),
    n_generate_variable(X,V),
    gen_var(V),
    gen_var_assign(1,A),
    gen_a_det_clause(X,A,M),
    M1 is M+1,
    gen_det_clause1(Cs,A,M1).


gen_a_det_clause((Head :- Body),A,M) :-
	gen_head(Head),
    gen_det_body(Body).

gen_a_det_clause(P,_,M) :-
	n_property(P,predicate),
    functor(P,_,0),
    write('if(rest!=NIL){'),nl,
    write('return(Jprove_all(rest,Jget_sp(th),th));'),nl,
    write('else return(YES);}'),nl.


/*
generate evauation code
e.g.  X is 1+2.  X == 3*4.
*/
eval_form([]) :-
	write('NIL').
eval_form([X]) :-
	write('Jmakeconst("'),
    write(X),
    write('")').
eval_form(pi) :-
	write('Jmakestrflt("3.14159265358979")').
eval_form(random) :-
	write('Jrandom(th)').    
eval_form(X) :-
	n_bignum(X),
    write('Jmakebig("'),
    write(X),
    write('")').
eval_form(X) :-
	n_longnum(X),
    write('Jmakestrlong("'),
    write(X),
    write('")').
eval_form(X) :-
	integer(X),
    write('Jmakeint('),
    write(X),
    write(')').
eval_form(X) :-
	float(X),
    write('Jmakestrflt("'),
    write(X),
    write('")').
eval_form(X) :-
	atom(X),
    n_compiler_variable(X),
    n_atom_convert(X,X1),
    write('Jderef('),
    write(X1),
    write(','),
    write(th),
    write(')').
eval_form(X) :-
	atom(X),
    write('Jmakeconst("'),
    write(X),
    write('")').
eval_form(X) :-
    list(X),
    gen_a_argument(X).
eval_form(-X) :-
	write('Jminus('),
    eval_form(0),
    write(','),
    eval_form(X),
    write(',th)').
eval_form(X + Y) :-
	write('Jplus('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write(',th)').
eval_form(X - Y) :-
	write('Jminus('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write(',th)').
eval_form(X * Y) :-
	write('Jmult('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write(',th)').
eval_form(X / Y) :-
	write('Jdivide('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write(',th)').
eval_form(X//Y) :-
	write('Jdiv('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write(',th)').
eval_form(X div Y) :-
	write('Jdiv('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write(',th)').
eval_form(X ^ Y) :-
	write('Jexpt('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write(',th)').
eval_form(X mod Y) :-
	write('Jmod('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write(',th)').
eval_form(sqrt(X)) :-
	write('Jsqrt('),
    eval_form(X),
    write(',th)').
eval_form(sin(X)) :-
	write('Jsin('),
    eval_form(X),
    write(',th)').
eval_form(asin(X)) :-
	write('Jasin('),
    eval_form(X),
    write(',th)').
eval_form(cos(X)) :-
	write('Jcos('),
    eval_form(X),
    write(',th)').
eval_form(acos(X)) :-
	write('Jacos('),
    eval_form(X),
    write(',th)').
eval_form(tan(X)) :-
	write('Jtan('),
    eval_form(X),
    write(',th)').
eval_form(atan(X)) :-
	write('Jatan('),
    eval_form(X),
    write(',th)').
eval_form(exp(X)) :-
	write('Jexp('),
    eval_form(X),
    write(',th)').
eval_form(log(X)) :-
	write('Jlog('),
    eval_form(X),
    write(',th)').
eval_form(ln(X)) :-
	write('Jln('),
    eval_form(X),
    write(',th)').
eval_form(integer(X)) :-
	write('Jinteger('),
    eval_form(X),
    write(',th)').
eval_form(abs(X)) :-
	write('Jabs('),
    eval_form(X),
    write(',th)').
eval_form(X << Y) :-
	write('Jleftshift('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write(',th)').
eval_form(X >> Y) :-
	write('Jrightshift('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write(',th)').
eval_form(X xor Y) :-
	write('Jxor('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write(',th)').
eval_form(X /\ Y) :-
	write('Jlogicaland('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write(',th)').
eval_form(X \/ Y) :-
	write('Jlogicalor('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write(',th)').
eval_form(\ X) :-
	write('Jcomplement('),
    eval_form(X),
    write(',th)').
eval_form(randi(X)) :-
	write('Jrandi('),
    eval_form(X),
    write(',th)').
eval_form(round(X,Y)) :-
	  write('Jround('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write(',th)').


/*
generate evauation code
e.g.  X is 1+2.  X == 3*4.
*/
gen_form([]) :-
	write('NIL').
gen_form([X]) :-
	write('Jmakeconst("'),
    write(X),
    write('")').
gen_form(pi) :-
	write('Jmakestrflt("3.14159265358979")').
gen_form(random) :-
	write('Jrandom(th)').    
gen_form(X) :-
	n_bignum(X),
    write('Jmakebig("'),
    write(X),
    write('")').
gen_form(X) :-
	n_longnum(X),
    write('Jmakestrlong("'),
    write(X),
    write('")').
gen_form(X) :-
	integer(X),
    write('Jmakeint('),
    write(X),
    write(')').
gen_form(X) :-
	float(X),
    write('Jmakestrflt("'),
    write(X),
    write('")').
gen_form(X) :-
	atom(X),
    n_compiler_variable(X),
    n_atom_convert(X,X1),
    write(X1).
gen_form(X) :-
	atom(X),
    write('Jmakeconst("'),
    write(X),
    write('")').
gen_form(X) :-
    list(X),
    gen_a_argument(X).
gen_form(-X) :-
	write('Jwlist2(Jmakeope("-"),'),
    gen_form(X),
    write(',th)').
gen_form(X + Y) :-
	write('Jwlist3(Jmakeope("+"),'),
    gen_form(X),
    write(','),
    gen_form(Y),
    write(',th)').
gen_form(X - Y) :-
	write('Jwlist3(Jmakeope("-"),'),
    gen_form(X),
    write(','),
    gen_form(Y),
    write(',th)').
gen_form(X * Y) :-
	write('Jwlist3(Jmakeope("*"),'),
    gen_form(X),
    write(','),
    gen_form(Y),
    write(',th)').
gen_form(X / Y) :-
	write('Jwlist3(Jmakeope("/"),'),
    gen_form(X),
    write(','),
    gen_form(Y),
    write(',th)').
gen_form(X//Y) :-
	write('Jwlist3(Jmakeope("//"),'),
    gen_form(X),
    write(','),
    gen_form(Y),
    write(',th)').
gen_form(X div Y) :-
	write('Jwlist3(Jmakeope("div"),'),
    gen_form(X),
    write(','),
    gen_form(Y),
    write(',th)').
gen_form(X ^ Y) :-
	write('Jwlist3(Jmakeope("^"),'),
    gen_form(X),
    write(','),
    gen_form(Y),
    write(',th)').
gen_form(X mod Y) :-
	write('Jwlist3(Jmakeope("mod"),'),
    gen_form(X),
    write(','),
    gen_form(Y),
    write(',th)').
gen_form(sqrt(X)) :-
	write('Jwlist2(Jmakefun("sqrt"),'),
    gen_form(X),
    write(',th)').
gen_form(sin(X)) :-
	write('Jwlist2(Jmakefun("sin"),'),
    gen_form(X),
    write(',th)').
gen_form(asin(X)) :-
	write('Jwlist2(Jmakefun("asin"),'),
    gen_form(X),
    write(',th)').
gen_form(cos(X)) :-
	write('Jwlist2(Jmakefun("cos),'),
    gen_form(X),
    write(',th)').
gen_form(acos(X)) :-
	write('Jwlist2(Jmakefun("acos"),'),
    gen_form(X),
    write(',th)').
gen_form(tan(X)) :-
	write('Jwlist2(Jmakefun("tan"),'),
    gen_form(X),
    write(',th)').
gen_form(atan(X)) :-
	write('Jwlist2(Jmakefun("atan"),'),
    gen_form(X),
    write(',th)').
gen_form(exp(X)) :-
	write('Jwlist2(Jmakefun("exp"),'),
    gen_form(X),
    write(',th)').
gen_form(log(X)) :-
	write('Jwlist2(Jmakefun("log"),',),
    gen_form(X),
    write(',th)').
gen_form(ln(X)) :-
	write('Jwlist2(Jmakefun("ln"),'),
    gen_form(X),
    write(',th)').
gen_form(integer(X)) :-
	write('Jwlist2(Jmakesys("integer"),'),
    gen_form(X),
    write(',th)').
gen_form(abs(X)) :-
	write('Jwlist2(Jmakefun("abs"),'),
    gen_form(X),
    write(',th)').
gen_form(X << Y) :-
	write('Jwlist3(Jmakeope("<<"),'),
    gen_form(X),
    write(','),
    gen_form(Y),
    write(',th)').
gen_form(X >> Y) :-
	write('Jwlist3(Jmakeope(">>"),'),
    gen_form(X),
    write(','),
    gen_form(Y),
    write(',th)').
gen_form(X xor Y) :-
	write('Jwlist3(Jmakeope("xor"),'),
    gen_form(X),
    write(','),
    gen_form(Y),
    write(',th)').
gen_form(X /\ Y) :-
	write('Jwlist3(Jmakeope("/\\"),'),
    gen_form(X),
    write(','),
    gen_form(Y),
    write(',th)').
gen_form(X \/ Y) :-
	write('Jwlist3(Jmakeope("\\/"),'),
    gen_form(X),
    write(','),
    gen_form(Y),
    write(',th)').
gen_form(\ X) :-
	write('Jwlist2(Jmakeope("\"),'),
    gen_form(X),
    write(',th)').
gen_form(randi(X)) :-
	write('Jwlist2(Jmakefun("randi"),'),
    gen_form(X),
    write(',th)').
gen_form(round(X,Y)) :-
	write('Jwlist3(Jmakefun("round"),'),
    gen_form(X),
    write(','),
    gen_form(Y),
    write(',th)').


/*
generate arguments for pred ope fun.
arguments are provided by list.
e.g. [3,14,A,foo(2)]
*/
gen_argument([]) :-
    write('NIL').
gen_argument([X|Xs]) :-
	write('Jwcons('),
    gen_a_argument(X),
    write(','),
    gen_argument(Xs),
    write(',th)').
/*
generate one argument
there are all type of prolog object
*/
gen_a_argument([]) :-
	write('NIL').
gen_a_argument(X) :-
    n_compiler_anonymous(X),
    write(X).
gen_a_argument(X) :-
	n_compiler_variable(X),
    n_atom_convert(X,X1),
    write(X1).
gen_a_argument(pi) :-
	write('Jmakestrflt("3.14159265358979")').
gen_a_argument(X) :-
	n_bignum(X),
    write('Jmakebig("'),
    write(X),
    write('")').
gen_a_argument(X) :-
	n_longnum(X),
    write('Jmakestrlong("'),
    write(X),
    write('")').
gen_a_argument(X) :-
	integer(X),
    write('Jmakeint('),
    write(X),
    write(')').
gen_a_argument(X) :-
	float(X),
    write('Jmakestrflt("'),
    write(X),
    write('")').
gen_a_argument(X) :-
	string(X),
    write('Jmakestr("'),
    write(X),
    write('")').
gen_a_argument(X) :-
    n_defined_predicate(X),
    functor(X,Y,0),
    n_dynamic_predicate(Y),
    write('Jmakepred("'),
    write(Y),
    write('")').
gen_a_argument(X) :-
    n_defined_predicate(X),
    functor(X,Y,0),
    n_imported_predicate(Y),
    write('Jmakepred("'),
    write(Y),
    write('")').
gen_a_argument(X) :-
    n_defined_predicate(X),
    functor(X,Y,0),
    write('Jmakecomp("'),
    write(Y),
    write('")').
gen_a_argument(X) :-
    n_defined_predicate(X),
    X =.. [Y|Z],
    n_dynamic_predicate(Y),
    write('Jwcons(Jmakepred("'),
    write(Y),
    write('"),'),
    gen_argument(Z),
    write(',th)').
gen_a_argument(X) :-
    n_defined_predicate(X),
    X =.. [Y|Z],
    n_imported_predicate(Y),
    write('Jwcons(Jmakepred("'),
    write(Y),
    write('"),'),
    gen_argument(Z),
    write(',th)').
gen_a_argument(X) :-
    n_defined_predicate(X),
    X =.. [Y|Z],
    write('Jwcons(Jmakecomp("'),
    write(Y),
    write('"),'),
    gen_argument(Z),
    write(',th)').
gen_a_argument(X) :-
    n_property(X,predicate),
    functor(X,Y,0),
    write('Jmakepred("'),
    write(Y),
    write('")').
gen_a_argument(X) :-
    n_property(X,predicate),
    X =.. [Y|Z],
    write('Jwcons(Jmakepred("'),
    write(Y),
    write('"),'),
    gen_argument(Z),
    write(',th)').
gen_a_argument(X) :-
    n_property(X,builtin),
    functor(X,Y,0),
    n_findatom(Y,builtin,A),
    write(A).
gen_a_argument(X) :-
    n_property(X,builtin),
    X =.. [Y|Z],
    n_findatom(Y,builtin,A),
	write('Jwcons('),
    write(A),
    write(','),
    gen_argument(Z),
    write(',th)').
gen_a_argument(X) :-
    n_property(X,compiled),
    functor(X,Y,0),
    n_findatom(Y,compiled,A),
    write(A).
gen_a_argument(X) :-
    n_property(X,compiled),
    X =.. [Y|Z],
    n_findatom(Y,compiled,A),
    write('Jwcons('),
    write(A),
    write(','),
    gen_argument(Z),
    write(',th)').
gen_a_argument(X) :-
    n_property(X,operation),
    functor(X,Y,0),
    n_findatom(Y,operator,A),
    write(A).
gen_a_argument(X) :-
    n_property(X,operation),
    X =.. [Y|Z],
    n_findatom(Y,operator,A),
	write('Jwcons('),
    write(A),
    write(','),
    gen_argument(Z),
    write(',th)').
%predicate indicator  e.g. foo/1
gen_a_argument(A/B) :-
    atom(A),
    integer(B),
    write('Jwlist3(Jmakefun("/"),Jmakepred("'),
    write(A),
    write('"),'),
    gen_a_argument(B),
    write(',th)').
gen_a_argument(X) :-
    n_property(X,function),
    functor(X,F,0),
    write('Jmakefun("'),
    write(F),
    write('")').
gen_a_argument(X) :-
    n_property(X,function),
    X =.. [F|Z],
	write('Jwcons(Jmakefun("'),
    write(F),
    write('"),'),
    gen_argument(Z),
    write(',th)').
gen_a_argument(X) :-
    n_defined_userop(X),
    X =.. [Y|Z],
    write('Jwcons(Jmakecomp("'),
    write(Y),
    write('"),'),
    gen_argument(Z),
    write(',th)').
gen_a_argument(X) :-
    n_property(X,userop),
    functor(X,_,0),
    write('Jmakeuser("'),
    write(X),
    write('")').
gen_a_argument(X) :-
    n_property(X,userop),
    X =.. [Y|Z],
	write('Jwcons(Jmakeuser("'),
    write(Y),
    write('"),'),
    gen_argument(Z),
    write(',th)').
gen_a_argument(X) :-
	atom(X),
    write('Jmakeconst("'),
    write(X),
    write('")').
gen_a_argument(X) :-
	list(X),
    gen_argument_list(X).
gen_a_argument(X) :-
    invoke_error('illegal argument ',X).

gen_argument_list([X|Xs]) :-
	write('Jwlistcons('),
    gen_a_argument(X),
    write(','),
    gen_a_argument(Xs),
    write(','),
    write(th),
    write(')').

/*----------------------tail TCO--------------------------------------
generate predicate for not tail recursive
static int c_<name>(int arglist, int rest){
int varX,varY,...
save2 = Jget_sp(th);
save3 = Jget_ac(th);
if(n == N){
    ...main code...
}
return(NO);
}

*/

gen_tail_pred(P) :-
	atom_concat('compiling ',P,M),
    write(user_output,M),
    n_atom_convert(P,P1),
	write('static int c_'),write(P1),write('(int arglist, int rest, int th){'),nl,
    gen_var_declare(P),
    write('save1 = Jget_wp(th);'),nl,
    write('save2 = Jget_sp(th);'),nl,
    write('save3 = Jget_ac(th);'),nl,
    write('Jinc_proof(th);'),nl,
    write('n = Jarity_count(arglist);'),nl,
    n_arity_count(P,L),
    gen_tail_pred1(P,L),
    write('}'),nl.

gen_tail_pred1(P,[]).
gen_tail_pred1(P,[A|As]) :-
    write(user_output,$/$),write(user_output,A),
    write(user_output,' '),write(user_output,tail),nl(user_output),
	gen_tail_arity(P,A),
    gen_tail_pred1(P,As).

gen_tail_arity(P,A) :-
	write('if(n == '),write(A),write('){'),nl,
    gen_tail_clause(P,A),
    write('return(NO);}'),nl,!.

gen_tail_clause(P,A) :-
    gen_var_assign(1,A),
    write(loop),write(A),write(':'),nl,
	n_clause_with_arity(P,A,C),
    gen_tail_clause1(C,A,0).

gen_tail_clause1([],_,_).
gen_tail_clause1([C|Cs],A,M) :-
	n_variable_convert(C,X),
    n_generate_variable(X,V),
    gen_var(V),
    gen_a_tail_clause(X,A,M),
    M1 is M+1,
    gen_tail_clause1(Cs,A,M1).

gen_a_tail_clause(P,A,M) :-
	n_property(P,predicate),
    P =.. [P1|_],
	gen_head(P),
    write('if(Jprove_all(rest,Jget_sp(th),th) == YES) return(YES);'),nl.

gen_a_tail_clause((Head :- Body),A,M) :-
    tail_body(Head,Body),
    Head =.. [P|Args],
	gen_head(Head),
    gen_tail_body(Body,A).


gen_tail_body((X,Y),N) :-
    gen_a_det_body(X),
    gen_tail_body(Y,N).
gen_tail_body(X,N) :-
    X =.. [_|A],
    write('{'),nl,
    gen_tail_args(A,1),
    write('Junbind(save2,th);'),nl,
    write('Jset_ac(save3,th);'),nl,
    write('goto loop'),write(N),write(';'),nl,
    write('}'),nl.

gen_tail_args([],_).
gen_tail_args([A|As],N) :-
    write('arg'),write(N),write(' = '),
    write('Jcopy_work(Jderef('),
    gen_a_argument(A),
    write(',th),th);'),nl,
    N1 is N+1,
    gen_tail_args(As,N1).

    



/*-----------------------dynamic predicate----------------------------
assert dynamic predicate
:- dynamic(foo/1)
foo(X) :- ...
dynamic_clause = Jcons(Jmakesys(":-"),...;
Jadd_dynamic(dyn); 
*/

gen_dyn_pred(P) :-
    n_arity_count(P,L),
    write('void '),write(P),write('(void){'),nl,
    gen_dyn_pred1(P,L),
    write('}'),!.

gen_dyn_pred1(_,[]).
gen_dyn_pred1(P,[L|Ls]) :-
    atom_concat('compiling ',P,M),
    write(user_output,M),write(user_output,$/$),write(user_output,L),
    write(user_output,' dyn'),nl(user_output),
    gen_dyn_arity(P,L),
    gen_dyn_pred1(P,Ls).

gen_dyn_arity(P,A) :-
    n_clause_with_arity(P,A,C),
    n_variable_convert(C,X),
    gen_dyn_clause(X).


gen_dyn_clause([]).
gen_dyn_clause([X|Xs]) :-
    gen_a_dyn_clause(X),
    gen_dyn_clause(Xs).

gen_a_dyn_clause([]) :-
    write('NIL').
gen_a_dyn_clause(X) :-
    n_property(X,predicate),
    write('dynamic_clause = '),gen_a_dyn_elt(X),write(';'),nl,
    write('Jadd_dynamic(dynamic_clause);'),nl.
gen_a_dyn_clause(X) :-
    n_property(X,operation),
    write('dynamic_clause = '),gen_dyn_elt(X),write(';'),nl,
    write('Jadd_dynamic(dynamic_clause);'),nl.
gen_a_dyn_clause((X :- Y)) :-
    write('Jlist3(Jmakeope(":-"),'),
    gen_dyn_head(X),write(','),gen_dyn_body(Y),write(')').

gen_dyn_head(X) :- gen_dyn_elt(X).
gen_dyn_body(X) :- gen_dyn_elt(X).
gen_dyn_elt((X,Y)) :-
    write('Jlist3(Jmakeope(","),'),
    gen_dyn_elt(X),
    write(','),
    gen_dyn_elt(Y),
    write(')').


% ifthenelse
gen_dyn_elt((X->Y;Z)) :-
    n_findatom(ifthenelse,builtin,A),
    write('Jcons('),write(A),write(','),
    write('Jlist3('),gen_dyn_elt(X),write(','),gen_dyn_elt(Y),write(','),gen_dyn_elt(Z),write('))').


% ifthen
gen_dyn_elt(X->Y) :-
    n_findatom(ifthen,builtin,A),
    write('Jcons('),write(A),write(','),
    write('Jlist2('),gen_dyn_elt(X),write(','),gen_dyn_elt(Y),write('))').


gen_dyn_elt((X;Y)) :-
    write('Jlist3(Jmakeope(";")),'),gen_dyn_elt(X),write(','),gen_dyn_elt(Y),write(')').

gen_dyn_elt(X) :-
    compound(X),
    n_property(X,compiled),
    X =.. [P|L],
    write('Jcons(Jmakecomp("'),write(P),write('"),'),
    gen_dyn_argument(L),
    write(')').
    
gen_dyn_elt(X) :-
    compound(X),
    n_property(X,predicate),
    X =.. [P|L],
    write('Jcons(Jmakepred("'),write(P),write('"),'),
    gen_dyn_argument(L),
    write(')').

gen_dyn_elt(X) :-
    atom(X),
    n_property(X,compiled),
    write('Jmakecomp("'),write(X),write('")').

gen_dyn_elt(X) :-
    atom(X),
    n_property(X,predicate),
    write('Jmakepred("'),write(X),write('")').

gen_dyn_elt(X) :-
    atom(X),
    n_dynamic_predicate(X),
    write('Jmakepred("'),write(X),write('")').

gen_dyn_elt(X) :-
    n_property(X,builtin),
    functor(X,P,0),
    n_findatom(P,builtin,A),
    write(A).
gen_dyn_elt(X) :-
    n_property(X,builtin),
    X =.. [P|L],
    n_findatom(P,builtin,A),
    write('Jcons('),write(A),write(','),
    gen_dyn_argument(L),
    write(')').
gen_dyn_elt(X) :-
    n_property(X,operation),
    X =.. [P|L],
    n_findatom(P,operator,A),
    write('Jcons('),write(A),write(','),
    gen_dyn_argument(L),
    write(')').
gen_dyn_elt(X) :-
    n_property(X,userop),
    functor(X,P,0),
    write('Jmakeuser("'),write(P),
    write('")').
gen_dyn_elt(X) :-
    n_property(X,userop),
    X =.. [P|L],
    write('Jcons(Jmakeuser("'),write(P),write('"),'),
    gen_dyn_argument(L),
    write(')').
gen_dyn_elt(X) :-
    n_compiler_anonymous(X),
    write('Jmakeanony("'),write(X),write('")').
gen_dyn_elt(X) :-
    n_compiler_variable(X),
    write('Jmakevar("'),write(X),write('")').
gen_dyn_elt(X) :-
    n_bignum(X),
    write('Jbigx_to_parmanent(Jmakebig("'),write(X),write('"))').
gen_dyn_elt(X) :-
    n_longnum(X),
    write('Jmakestrlong("'),write(X),write('")').
gen_dyn_elt(X) :-
    integer(X),
    write('Jmakeint('),write(X),write(')').
gen_dyn_elt(X) :-
    float(X),
    write('Jmakestrflt("'),write(X),write('")').
gen_dyn_elt(X) :-
    list(X),
    gen_dyn_list(X).
gen_dyn_elt(X) :-
    atom(X),
	write('Jmakepred("'),write(X),write('")').
gen_dyn_elt(X) :-
    string(X),
	write('Jmakestr("'),write(X),write('")').
gen_dyn_elt(X) :-
    invoke_error('illegal clause ',X).

gen_dyn_argument([]) :-
    write('NIL').
gen_dyn_argument([X|Xs]) :-
    write('Jcons('),gen_dyn_elt(X),write(','),
    gen_dyn_argument(Xs),
    write(')').

gen_dyn_list([]) :-
    write('NIL').
gen_dyn_list(X) :-
    atom(X),
    gen_dyn_elt(X).
gen_dyn_list([L|Ls]) :-
    write('Jlistcons('),gen_dyn_elt(L),write(','),
    gen_dyn_list(Ls),
    write(')').

%---------------------------------------------


gen_cdeclare(P) :-
    n_clause_with_arity(P,1,X),
    gen_cdeclare1(X),!.

gen_cdeclare1([]).
gen_cdeclare1([X|Cs]) :-
    X =.. [_,Y],
    write(Y),nl,
    gen_cdeclare1(Cs).
    
gen_clibrary(P) :-
    n_clause_with_arity(P,1,X),
    gen_clibrary1(X),!.
    
gen_clibrary1([]).
gen_clibrary1([X|Cs]) :-
    X =.. [_,Y],
    asserta(option(library,Y)),
    gen_clibrary1(Cs).

/*
invoke error
display error message and error code.
and close output file, finaly abort to REPL
*/
invoke_error(Message,Code) :-
	write(user_output,Message),
    write(user_output,Code),nl(user_output),
    told,
    abort.

% deterministic body case. Each has cut or each is builtin or each is tail-recur 
% G is gournd_variable
det_body(Head,(_->_;_),_).       % a->b;c
det_body(_,(_;_),_) :- !,fail.
det_body(_,((_;_),_),_) :- !,fail.
det_body(Head,(V is _,Y),G) :-
    det_body(Head,Y,[V|G]).
det_body(Head,(X,Y),G) :-
    det_builtin(X,G),
    det_body(Head,Y,G).
det_body(Head,(X,Y),G) :-
    X = (((_->_),_);_),
    det_body(Head,Y,G).
det_body(Head,(X,Y),G) :-
    det_pass1(X),
    det_body(Head,Y,G).
det_body(Head,(X,Y),G) :-
    functor(Head,Pred1,Arity1),
    functor(X,Pred2,Arity2),
    Pred1 == Pred2,
    Arity1 == Arity2,
    type(Pred1,Arity1,halt),
    P =.. [type,Pred1,_,_],
    (retract(P);true),
    asserta(type(Pred1,Arity1,det)),
    det_body(Head,Y,G).
det_body(_,X,G) :-
    det_builtin(X,G).
det_body(_,X,_) :-
    det_pass1(X).
det_body(Head,X,_) :-
    functor(Head,Pred1,Arity1),
    functor(X,Pred2,Arity2),
    Pred1 == Pred2,
    Arity1 == Arity2,
    type(Pred1,Arity1,halt),
    P =.. [type,Pred1,_,_],
    (retract(P);true),
    asserta(type(Pred1,Arity1,det)).
det_pass1(X) :-
    functor(X,P,A),
    type(P,A,det).
det_pass1(X) :-
    functor(X,P,A),
    type(P,A,tail).


% generaly builtin is deterministic. but some cases is non deterministic.
det_builtin(length(X,Y),G) :-
    n_compiler_variable(X),
    not(member(X,G)),
    n_compiler_variable(Y),
    not(member(Y,G)),!,fail.

det_builtin(append(X,Y,_),G) :-
    n_compiler_variable(X),
    not(member(X,G)),
    n_compiler_variable(Y),
    not(member(Y,G)),!,fail.

det_builtin(member(X,_),G) :-
    n_compiler_variable(X),
    not(member(X,G)),!,fail.

det_builtin(between(_,_,X),G) :-
    n_compiler_variable(X),
    not(member(X,G)),!,fail.

det_builtin(repeat,G) :-
    !,fail.

det_builtin(select(_,_,_),G) :-
    !,fail.

det_builtin(length(X,Y),G) :-
    n_compiler_variable(X),
    n_compiler_variable(Y),
    not(member(X,G)),
    not(member(Y,G)),!,fail.

det_builtin(X,_) :-
    n_property(X,builtin).



% tail recursive
tail_body(Head,Body) :-
    last_body(Body,Last),
    functor(Head,Pred1,Arity1),
    functor(Last,Pred2,Arity2),
    Pred1 == Pred2,
    Arity1 == Arity2.

last_body((_,Body),Last) :-
    last_body(Body,Last).
last_body(Body,Body).

butlast_body((Body,Bs),Body) :-
    n_property(Bs,predicate).
butlast_body((Body,Bs),Body) :-
    n_property(Bs,builtin).
butlast_body((Body,Bs),(Body,Butlast)) :-
    butlast_body(Bs,Butlast).


/*
 a,b,c ->  if(a==YES) if(b==YES) if(c==YES) return(Jprove_all(rest,Jget_sp(th),th));
 /*
generate one operation,user,builtin or compiled predicate.
when except of above type, invoke error.
*/

gen_det_body((X,Y)) :-
    gen_a_det_body(X),
    nl,
    gen_det_body(Y).

gen_a_det_body((X;Y)) :-
	write('Jwlist3(Jmakeope(";"),'),
	gen_det_body(X),
    write(','),
    gen_det_body(Y),
    write(',th)').

gen_det_body(X) :-
    gen_a_det_body(X),
    nl,
    write('return(Jprove_all(rest,Jget_sp(th),th));'),nl,
    write('Jset_ac(save3,th);'),nl,
    write('Junbind(save2,th);'),nl,
    write('Jset_wp(save1,th);'),nl.

gen_a_det_body(!).

% inline C language
gen_a_det_body(cinline(X)) :-
    write('{'),
    write(X),
    write('}'),
    nl.

gen_a_det_body(X is Y) :-
    write('if(Junify('),
    gen_a_argument(X),
    write(','),
    eval_form(Y),
    write(','),
    write(th),
    write(')==YES)').

gen_a_det_body(X = Y) :-
    write('if(Junify('),
    gen_a_argument(X),
    write(','),
    gen_a_argument(Y),
    write(','),
    write(th),
    write(')==YES)').

gen_a_det_body(X =:= Y) :-
    write('if(Jnumeqp('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write('))').

gen_a_det_body(X =\= Y) :-
    write('if(Jnot_numeqp('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write('))').

gen_a_det_body(X < Y) :-
    write('if(Jsmallerp('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write('))').

gen_a_det_body(X =< Y) :-
    write('if(Jeqsmallerp('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write('))'),nl.

gen_a_det_body(X > Y) :-
    write('if(Jgreaterp('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write('))').

gen_a_det_body(X >= Y) :-
    write('if(Jeqgreaterp('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write('))').

gen_a_det_body((((X->Y),Y1);Z)) :-
    case_arg((((X->Y),Y1);Z),L),
    write('if (Jcall_det(Jmakesys("case"),Jwlist1('),
    gen_a_argument(L),
    write(',th),th) == YES)').

gen_a_det_body((X->Y;Z)) :-
    case_arg((X->Y;Z),L),
    write('if (Jcall_det(Jmakesys("case"),Jwlist1('),
    gen_a_argument(L),
    write(',th),th) == YES)').

gen_a_det_body((X->Y;Z)) :-
    n_findatom(case,builtin,A),
    write('Jwcons('),
    write(A),
    write(','),
    write('Jwlist1('),
    case_arg((X->Y;Z),L),
    gen_argument_list(L),
    write(',th),th)').


% use_module
gen_a_det_body(use_module(X)) :-
    n_findatom(use_module,builtin,A),
    write('Jwlist2('),
    write(A),
    write(','),
    write('Jmakeconst("'),
    write(X),
    write('"),th)').


% for FCG {} compile
gen_a_det_body(',') :-
    write('Jmakesys("n_exec_no_operation")').

gen_a_det_body(X) :-
    n_property(X,builtin),
    X =.. [P|A],
    write('if (Jcall_det(Jmakesys("'),
    write(P),
    write('"),'),
    gen_argument(A),
    write(',th) == YES)').


gen_a_det_body(X) :-
    n_property(X,predicate),
    X =.. [P|A],
    write('if (Jcall_det(Jmakecomp("'),
    write(P),
    write('"),'),
    gen_argument(A),
    write(',th) == YES)').

gen_a_det_body(X) :-
    invoke_error('illegal body ',X).


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




%------------------------analizer-------------------------

analize :-
    n_reconsult_predicate(P),
    analize_pred(P),
    fail.
analize.


analize_pred(P) :-
    n_arity_count(P,[N]),
	n_clause_with_arity(P,N,C),
    n_variable_convert(C,C1),
    analize_pred1(P,N,C1),!,
    fail.

analize_pred1(P,N,C) :-
    n_dynamic_predicate(P),
    length(C,M),
    P1 =.. [type,P,_,_],
    (retract(P1);true),
    asserta(type(P,N,dyn)),!.
analize_pred1(P,N,C) :-
    not(n_dynamic_predicate(P)),
    length(C,M),
    tail_recursive(C,0,0,0,M,N),
    P1 =.. [type,P,_,_],
    (retract(P1);true),
    asserta(type(P,N,tail)),!.
analize_pred1(P,N,C) :-
    not(n_dynamic_predicate(P)),
    length(C,M),
    deterministic(C,0,0,0,M),
    P1 =.. [type,P,_,_],
    (retract(P1);true),
    asserta(type(P,N,det)),!.
analize_pred1(P,N,C) :-
    not(n_dynamic_predicate(P)),
    nondet_recursive(C,0),
    P1 =.. [type,P,_,_],
    (retract(P1);true),
    asserta(type(P,N,recur)),!.
analize_pred1(P,N,C) :-
    not(n_dynamic_predicate(P)),
    length(C,M),
    halt_check(C,0,0,M),
    P1 =.. [type,P,_,_],
    (retract(P1);true),
    asserta(type(P,N,halt)),!.
analize_pred1(P,N,C) :-
    not(n_dynamic_predicate(P)),
    P1 =.. [type,P,_,_],
    (retract(P1);true),
    asserta(type(P,N,nondet)),!.


% arguments = [clauses],det_count,pred_count,halt_count,all_count
deterministic([],D,P,H,A) :-
    %write(user_output,D),write(user_output,P),write(user_output,H),write(user_output,A),
    P =< 1,
    H == 1,
    A =:= D+P+H,!.
deterministic([],D,P,H,A) :-
    %write(user_output,D),write(user_output,P),write(user_output,H),write(user_output,A),nl,
    P == 0,
    D == 1,
    A =:= D+P+H,!.
deterministic(_,_,P,_,_) :-
    %write(user_output,P),
    P > 1,
    !,fail.
deterministic([(_ :- !)|Cs],D,P,H,A) :-
    H1 is H+1,!,
    deterministic(Cs,D,P,H1,A).
deterministic([(Head :- Body)|Cs],D,P,H,A) :-
    det_body(Head,Body,[]),
    D1 is D+1,!,
    deterministic(Cs,D1,P,H,A).
deterministic([X|Cs],D,P,H,A) :-
    n_property(X,predicate),
    P1 is P+1,!,
    deterministic(Cs,D,P1,H,A).
deterministic([_|Cs],D,P,H,A) :-
    deterministic(Cs,D,P,H,A).

% arguments = [clauses],tail_count,pred_count, halt_base_count,all_count, arity
tail_recursive([],T,P,H,A,_) :-
    %write(user_output,T),write(user_output,P),write(user_output,H),write(user_output,A),nl,
    T >= 1,
    P == 1,
    A =:= T+P+H,!.
tail_recursive([],T,P,H,A,_) :-
    %write(user_output,T),write(user_output,P),write(user_output,H),write(user_output,A),nl,
    T == 1,
    P == 0,
    H >= 1,
    A =:= T+P+H,!.
tail_recursive(_,_,P,_,_,_) :-
    %write(user_output,P),nl,
    P > 1,
    !,fail.
tail_recursive([(Head :- !)|Cs],T,P,H,A,N) :-
    independ_head(Head),
    H1 is H+1,!,
    tail_recursive(Cs,T,P,H1,A,N).
tail_recursive([(Head :- Body)|Cs],T,P,H,A,N) :-
    independ_head(Head),
    not(tail_body(Head,Body)),
    det_body(Head,Body,[]),
    H1 is H+1,!,
    tail_recursive(Cs,T,P,H1,A,N).
tail_recursive([(Head :- Body)|Cs],T,P,H,A,N) :-
    %write(user_output,Head),nl,write(user_output,Body),nl,
    independ_head(Head),
    butlast_body(Body,Body1),
    independ_body(Head,Body1),
    det_body(Head,Body1,[]),
    tail_body(Head,Body),
    not(tail_body(Head,Body1)), % ...,qsort(),qsort(). not tco
    T1 is T+1,!,
    tail_recursive(Cs,T1,P,H,A,N).
tail_recursive([X|Cs],D,P,H,A,N) :-
    n_property(X,predicate),
    X =.. [_|Args],
    member([],Args),
    H1 = H+1,!,
    tail_recursive(Cs,D,P,H1,A,N).
tail_recursive([X|Cs],D,P,H,A,N) :-
    n_property(X,predicate),
    independ_head(X),
    P1 is P+1,!,
    tail_recursive(Cs,D,P1,H,A,N).
tail_recursive([_|Cs],D,P,H,A,N) :-
    tail_recursive(Cs,D,P,H,A,N).


independ_head(Head) :-
    extract_variable(Head,Args),
    independ_head1(Args).

independ_head1([]).
independ_head1([_]).
independ_head1([A|As]) :-
    member(A,As),!,fail.
independ_head1([_|As]) :-
    independ_head1(As).

extract_variable(Term,X) :-
    Term =.. [_|A],
    extract_variable1(A,X).

extract_variable1([],[]).

extract_variable1([L|Ls],[L|Y]) :-
    n_compiler_variable(L), !,
    extract_variable1(Ls,Y).
extract_variable1([L|Ls],Y) :-
    atomic(L), !,
    extract_variable1(Ls,Y).
extract_variable1([L|Ls],Z) :-
    list(L), !,
    extract_variable1(L,Y1),
    extract_variable1(Ls,Y2),
    append(Y1,Y2,Z).
extract_variable1([L|Ls],Z) :-
    n_property(L,predicate), !,
    L =.. [_|Args],
    extract_variable1(Args,Y1),
    extract_variable1(Ls,Y2),
    append(Y1,Y2,Z).
extract_variable1(L,[L]) :-
    n_compiler_variable(L), !.
extract_variable1(L,[]) :-
    atomic(L).

generated_variable((X;Y),L) :-
    generated_variable(X,L1),
    generated_variable(Y,L2),
    append(L1,L2,L),!.
generated_variable((X,Y),L) :-
    generated_variable(X,L1),
    generated_variable(Y,L2),
    append(L1,L2,L),!.
generated_variable(M is _,[M]) :-
    n_compiler_variable(M), !.
generated_variable(Term,V) :-
    n_property(Term,predicate),
    Term =.. [_|A],
    generated_variable1(A,V).
generated_variable(_,[]) :- !.

generated_variable1([],[]).
generated_variable1([V|Vs],[V|L]) :-
    n_compiler_variable(V),
    generated_variable1(Vs,L).
generated_variable1([V|Vs],L) :-
    list(V),
    generated_variable1(V,L1),
    generated_variable1(Vs,L2),
    append(L1,L2,L).
generated_variable1([V|Vs],L) :-
    n_property(V,predicate),
    V =.. [_|V1],
    generated_variable1(V1,L1),
    generated_variable1(Vs,L2),
    append(L1,L2,L).    
generated_variable1([_|Vs],L) :-
    generated_variable1(Vs,L).


independ_body(Head,Body) :-
    extract_variable(Head,A1),
    generated_variable(Body,V),!,
    independ_body1(A1,V).
independ_body1(A,[]) :- !.
independ_body1(A,[V|Vs]) :-
    not(member(V,A)),
    independ_body1(A,Vs).
independ_body1(A,[V|Vs]) :-
    member(V,A),!,fail.
    
% arguments = [clauses],det_count,pred_count,all_count
halt_check([],H,P,_) :-
    %write(user_output,H),write(user_output,P),write(user_output,A),
    P == 0,
    H == 1,!.
halt_check(_,_,P,_) :-
    P > 1,
    !,fail.
halt_check([(_ :- !)|Cs],H,P,A) :-
    H1 is H+1,!,
    halt_check(Cs,H1,P,A).
halt_check([(_ :- _)|Cs],H,P,A) :-
    halt_check(Cs,H,P,A).
halt_check([X|Cs],H,P,A) :-
    X =.. [_|Args],
    member([],Args),
    H1 is H+1,!,
    halt_check(Cs,H1,P,A).
halt_check([X|Cs],D,P,A) :-
    n_property(X,predicate),
    P1 is P+1,!,
    halt_check(Cs,D,P1,A).
halt_check([_|Cs],D,P,A) :-
    halt_check(Cs,D,P,A).


nondet_recursive([],R) :-
    %write(user_output,R),
    R >= 1,!.
nondet_recursive([],R) :-
    %write(user_output,R),
    R == 0,!,fail.    
nondet_recursive([(Head :- Body)|Cs],R) :-
    tail_body(Head,Body),
    R1 is R + 1,
    nondet_recursive(Cs,R1).
nondet_recursive([(Head :- Body)|Cs],R) :-
    nondet_recur_body(Head,Body),
    R1 is R + 1,
    nondet_recursive(Cs,R1).
nondet_recursive([_|Cs],R) :-
    nondet_recursive(Cs,R).

nondet_recur_body(Head,(B1,B2)) :-
    functor(Head,P,A),
    functor(B1,P,A).
nondet_recur_body(Head,(B1,B2)) :-
    functor(B1,P,A),
    type(P,A,recur).
nondet_recur_body(Head,(B1,B2)) :-
    nondet_recur_body(Head,B2).
nondet_recur_body(Head,Body) :-
    functor(Head,P,A),
    functor(Body,P,A).
nondet_recur_body(Head,Body) :-
    functor(Body,P,A),
    type(P,A,recur).

%---------------------------------------------------------
