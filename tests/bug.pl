mbetween(X_,Y_,X_) :-
    X_ =< Y_.
mbetween(X_,Y_,Z_) :-
    X_ < Y_,
    A_ is X_ + 1,
    mbetween(A_,Y_,Z_).

