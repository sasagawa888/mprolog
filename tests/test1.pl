% test_light.pl

% 1. 単純 fact
color(red).
color(green).
color(blue).


% 2. 2引数 fact
likes(taro, apple).
likes(taro, banana).
likes(hanako, orange).


% 3. 単純な連言
warm(red).
warm(orange).

warm_color(X) :-
    color(X),
    warm(X).


% 4. 1段だけ再帰
nat(0).
nat(s(X)) :-
    nat(X).


% 5. 単純 member
member1(X, [X|_]).
member1(X, [_|Xs]) :-
    member1(X, Xs).


% 6. 連言 + nondet
pair(X, Y) :-
    color(X),
    color(Y).


% 7. 再帰 + 基底節
len([], 0).
len([_|Xs], s(N)) :-
    len(Xs, N).


% 8. nondet のあとに det
small(1).
small(2).
small(3).

positive(1).
positive(2).
positive(3).

small_positive(X) :-
    small(X),
    positive(X).