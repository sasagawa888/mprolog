% M-Prolog test 

second([],[]).
second([_,X|_],X).


last([],[]).
last([X],X).
last([X|Xs],Y) :-
    last(Xs,Y).


last([],[]).
last([X],X).
last([X|Xs],Y) :-
    last(Xs,Y).

butlast([],[]).
butlast([X],[]).
butlast([X|Xs],[X|Y]) :-
    butlast(Xs,Y).



cons(X,[],[X]).
cons(X,Y,[X|Y]).

second([],[]).
second([_,X|_],X).

nth(N,[],[]).
nth(1,[X|Xs],X).
nth(N,[X|Xs],Y) :-
    N1 is N-1,
    nth(N1,Xs,Y).

nth0(N,[],[]).
nth0(0,[X|Xs],X).
nth0(N,[X|Xs],Y) :-
    N1 is N-1,
    nth0(N1,Xs,Y).

iota(S,S,[S]).
iota(S,E,[S|L]) :-
    S1 is S+1,
    iota(S1,E,L).

take(0,L,[]).
take(N,[L|Ls],[L|Y]) :-
    N1 is N-1,
    take(N1,Ls,Y).

drop(0,L,L).
drop(N,[L|Ls],Y) :-
    N1 is N-1,
    drop(N1,Ls,Y).


make_list(0,X,[]).
make_list(N,X,[X|Y]) :-
    N1 is N-1,
    make_list(N1,X,Y).

reverse([],[]).
reverse([X|Xs],Y) :-
    reverse(Xs,Y1),
    append(Y1,[X],Y).

remove_at(0,[X|Xs],Xs).
remove_at(N,[X|Xs],[X|Y]) :-
    N1 is N-1,
    remove_at(N1,Xs,Y).

insert_at(0,X,L,[X|L]).
insert_at(N,X,[L|Ls],[L|Y]) :-
    N1 is N-1,
    insert_at(N1,X,Ls,Y).


nodiag([], _, _).
nodiag([N|L], B, D) :-
    D =\= N - B,
    D =\= B - N,
    D1 is D + 1,
    nodiag(L, B, D1).

bar(X) :- write(X).


p(1).
p(2).
p(3).

cut(X) :-
    p(X),
    !,
    write(X).

cuttest :- cut(X).


disj :-
    write(a)
 ;
    write(b).

disjtest :-
    disj,
    fail.


f(1,Y) :- Y is 2.
f(2,Y) :- Y is 3.


