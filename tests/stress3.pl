% cut_nondet_test.pl
% M-Prolog nondet CUT operator tests
%
% Test 1:
%   CUT should keep only the first solution.
%
% Test 2:
%   Failure after CUT must not retry earlier alternatives.
%
% Test 3:
%   Clause selection with CUT.
%
% Test 4:
%   CUT inside a called predicate must not remove
%   choice points belonging to its caller.


% ------------------------------------------------------------
% 1. Keep only the first solution
% ------------------------------------------------------------

color(red).
color(green).
color(blue).

first_color(X) :-
    color(X),
    !.

% Expected:
%
% ?- color(X).
% X = red ;
% X = green ;
% X = blue ;
% no
%
% ?- first_color(X).
% X = red .
% yes

/*
% ------------------------------------------------------------
% 2. Failure after CUT
% ------------------------------------------------------------

num(1).
num(2).
num(3).

test_cut_fail(X) :-
    num(X),
    !,
    X = 2.

test_no_cut(X) :-
    num(X),
    X = 2.

% Expected:
%
% ?- test_cut_fail(X).
% no
%
% The first solution X = 1 is selected and then CUT is executed.
% Since 1 = 2 fails, num/1 must not retry X = 2.
%
% ?- test_no_cut(X).
% X = 2 .
% yes


% ------------------------------------------------------------
% 3. Clause selection with CUT
% ------------------------------------------------------------

sign(X, positive) :-
    X > 0,
    !.
sign(0, zero) :-
    !.
sign(_, negative).

% Expected:
%
% ?- sign(3, X).
% X = positive .
% yes
%
% ?- sign(0, X).
% X = zero .
% yes
%
% ?- sign(-2, X).
% X = negative .
% yes


% ------------------------------------------------------------
% 4. Simple once-like behavior
% ------------------------------------------------------------

a(1).
a(2).
a(3).

once_a(X) :-
    a(X),
    !.

% Expected:
%
% ?- a(X).
% X = 1 ;
% X = 2 ;
% X = 3 ;
% no
%
% ?- once_a(X).
% X = 1 .
% yes


% ------------------------------------------------------------
% 5. CUT scope test
% ------------------------------------------------------------

left(a).
left(b).

right(1).
right(2).
right(3).

pair(X, Y) :-
    left(X),
    choose_right(Y).

choose_right(Y) :-
    right(Y),
    !.

% Expected:
%
% ?- pair(X, Y).
% X = a
% Y = 1 ;
%
% X = b
% Y = 1 ;
%
% no
%
% The CUT in choose_right/1 must remove only the alternatives
% created by right/1.  The caller's left/1 alternatives must remain.
*/
