/*

ack(0,N,A) :- 
    A is N+1,!.
ack(M,0,A) :- 
    M1 is M-1,ack(M1,1,A).
ack(M,N,A) :- 
    M1 is M-1,N1 is N-1,
    ack(M,N1,A1), ack(M1,A1,A).

*/

/* incomplete trying mode */
ack(M,N,A) :-
cinline($ //ack
          int exec1(int a1, int a2){
            int a,m1,n1;
            Jinc_proof(th);
            a = Jmakevariant(th);
            m1 = Jmakevariant(th);
            n1 =  Jmakevariant(th);
              if(a1 == Jmakeint(0)){
                  Jcall_det(Jmakesym("is"),Jwcons(a,Jplus(x,l1,l2,th),th),th);
                  r1 =Jcar(exec1(Jderef(l2,th),r0));
                  r2 =Jcar(exec1(Jderef(l1,th),Jwlistcons(x,r1,th)));
                  return(Jwlist1(r2,th));
              }
              else if(a1 == NIL){
                  return(Jwlist1(r0,th));
          }}
          int m = Jderef(varM,th);
          int n = Jderef(varN,th);
          int res = Jcar(exec1(m,n));
          Junify(varA,res,th);
          return(Jprove_all(rest,Jget_sp(th),th)); $).

