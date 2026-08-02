% 1. 単純な自然数生成
nat(0).
nat(s(X)) :-
    nat(X).

% ?- nat(X).
% X = 0 ;
% X = s(0) ;
% X = s(s(0)) ;
% ...


% 2. 入力を一段ずつ削るだけ
down(0).
down(s(X)) :-
    down(X).

% ?- down(s(s(s(0)))).
% yes.


% 3. Peano数のコピー
copy_nat(0, 0).
copy_nat(s(X), s(Y)) :-
    copy_nat(X, Y).

% ?- copy_nat(s(s(0)), X).
% X = s(s(0)).
%
% ?- copy_nat(X, s(s(0))).
% X = s(s(0)).


% 4. リストの長さ
len([], 0).
len([_|Xs], s(N)) :-
    len(Xs, N).

% ?- len([a,b,c], X).
% X = s(s(s(0))).
%
% ?- len(X, s(s(0))).
% X = [_A,_B].


% 5. リストの最後までたどる
listp([]).
listp([_|Xs]) :-
    listp(Xs).

% ?- listp([a,b,c]).
% yes.
%
% ?- listp(X).
% X = [] ;
% X = [_A] ;
% X = [_A,_B] ;
% ...


% 6. 単純な member
mem(X, [X|_]).
mem(X, [_|Xs]) :-
    mem(X, Xs).

% ?- mem(X, [a,b,c]).
% X = a ;
% X = b ;
% X = c.