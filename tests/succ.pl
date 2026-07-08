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

nodiag([], _, _).
nodiag([N|L], B, D) :-
    D =\= N - B,
    D =\= B - N,
    D1 is D + 1,
    nodiag(L, B, D1).

bar(X) :- write(X).