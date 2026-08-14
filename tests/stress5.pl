%インタプリタにおいてmappendが機能するかのテスト　OK

% mappendを利用するテスト
test_append(X) :-
    mappend([a,b], [c,d], X).

% mappendのバックトラックも利用するテスト
test_split(X, Y) :-
    mappend(X, Y, [a,b,c]).