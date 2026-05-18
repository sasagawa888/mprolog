
gen_free_state([],Vers,[]) :-!.
gen_free_state([F|Fs],Vers,[a(N,'-')|Ss]) :-
    nth_var(F,Vers,N),
    gen_free_state(Fs,Vers,Ss).

nth_var(F,[F|Vs],1) :-!..
nth_var(F,[V|Vs],N) :-
    nth_var(F,Vs,N1),!,
    N is N1+1.