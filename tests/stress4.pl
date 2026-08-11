% ============================================================
% nondet stress test
% ============================================================

member1(X,[X|_]).
member1(X,[_|Xs]) :-
    member1(X,Xs).


select1(X,[X|Xs],Xs).
select1(X,[Y|Ys],[Y|Zs]) :-
    select1(X,Ys,Zs).


perm1([],[]).
perm1(Xs,[X|Ys]) :-
    select1(X,Xs,Zs),
    perm1(Zs,Ys).

ptest(X,Y) :-
    select1(X,[a,b],_),
    select1(Y,[1,2],_).

ptest2([],[]).
ptest2([_|Xs],[X|Ys]) :-
    choose(X),
    ptest2(Xs,Ys).

gen([1]).
gen([2]).

ptest3(X) :-
    gen(Z),
    ptest2(Z,X).

ptest4(X,Y) :-
    select1(X,[1,2,3],Z),
    ptest2(Z,Y).

ordered([]).
ordered([_]).
ordered([X,Y|Xs]) :-
    X =< Y,
    ordered([Y|Xs]).


sort_test(Xs,Ys) :-
    perm1(Xs,Ys),
    ordered(Ys).

p1(X,Y) :-
    select1(X,[1,2,3],Z),
    select1(Y,Z,_).

rtest([],[]).
rtest([_|Xs],[X|Ys]) :-
    choose(X),
    rtest(Xs,Ys).

choose(a).
choose(b).

rtest2([],[]).
rtest2([_|Xs],[X|Ys]) :-
    choose(X),
    write(X),
    rtest2(Xs,Ys).


% ============================================================
% Test 1: simple nondet recursion
%
% ?- member1(X,[1,2,3]).
%
% Expected:
%
% X = 1 ;
% X = 2 ;
% X = 3 ;
% no
% ============================================================


% ============================================================
% Test 2: nondet recursion with shared variables
%
% ?- select1(X,[1,2,3],Y).
%
% Expected:
%
% X = 1
% Y = [2,3] ;
%
% X = 2
% Y = [1,3] ;
%
% X = 3
% Y = [1,2] ;
%
% no
% ============================================================


% ============================================================
% Test 3: nested nondet recursion
%
% ?- perm1([1,2,3],X).
%
% Expected:
%
% X = [1,2,3] ;
% X = [1,3,2] ;
% X = [2,1,3] ;
% X = [2,3,1] ;
% X = [3,1,2] ;
% X = [3,2,1] ;
% no
%
% This tests nested choice points.
% Failure in inner perm1/2 must eventually return to
% the choice point of the outer select1/3.
% ============================================================


% ============================================================
% Test 4: generate and test
%
% ?- sort_test([3,1,2],X).
%
% Expected:
%
% X = [1,2,3] ;
% no
%
% perm1/2 generates permutations.
% ordered/1 rejects incorrect permutations.
%
% This exercises:
%
%   nondet generation
%       ->
%   recursive call
%       ->
%   builtin (=<) failure
%       ->
%   backtracking into perm1/2
%       ->
%   generation of the next solution
%
% Useful for detecting incorrect restoration of:
%
%   arglist
%   vp
%   variable bindings
%   choice points
%   failure continuations
% ============================================================


% ============================================================
% Test 5: 24 solutions
%
% ?- perm1([1,2,3,4],X).
%
% Expected:
%
% Exactly 24 solutions followed by:
%
% no
%
% Each solution must be a different permutation of
% [1,2,3,4].
% ============================================================


% ============================================================
% Stress test
%
% permtest enumerates all 5! = 120 permutations and then fails.
% ============================================================
/*
permtest :-
    perm1([1,2,3,4,5],_),
    fail.
*/

% ?- permtest.
%
% Expected:
%
% no
%
% Internally perm1/2 must generate exactly 120 solutions.
%
%
% Performance test:
%
% ?- measure((between(1,1000,_),permtest,fail)).
%
% Expected:
%
% yes
%
% No crash, no stack corruption, no incorrect success.
% ============================================================