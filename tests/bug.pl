

mmember(X_, [X_|_]).
mmember(X_, [_|Y_]) :-
    mmember(X_, Y_).