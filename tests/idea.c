/*
M-Prolog Ver 0.01 [30M cells]
?- ['./tests/idea.o'].
yes
?- foo.
12no
?- 

p(1).
p(2).

foo :- p(X),write(X),fail.
*/


#include "jump.h"
static int b_p(int arglist, int rest, int th);
static int b_p(int arglist, int rest, int th){
int arg1,n,body,save1,save2,save3,goal,cont,clause,res;

if(rest != NIL){
save1 = Jget_wp(th);
save2 = Jget_sp(th);
save3 = Jget_ac(th);
} else {
save1 = Jget_back_wp(th);
save2 = Jget_back_sp(th);
save3 = Jget_back_ac(th);
clause = Jget_back_choice(th);
}
n = Jlength(arglist);
if(n == 1){
arg1 = Jnth(arglist,1);
if(rest == NIL){
switch(clause){
    case 0: goto clause0;
    case 1: goto clause1;
    default: goto allfail;
}}
loop1:
clause0:
Jinc_back_choice(th);
if(Junify_int(arg1,Jmakeint(1),th) == YES && 1)
if(rest != NIL){
if(Jprove_all(rest,Jget_sp(th),th) == YES) return(YES);
} else return(YES);

clause1:
Jset_ac(save3,th);
Junbind(save2,th);
if(rest == NIL){
Jinc_back_choice(th);
arg1 = Jnth(arglist,1);
}
Jdebug();
if(Junify_int(arg1,Jmakeint(2),th) == YES && 1){
if(rest != NIL){
if(Jprove_all(rest,Jget_sp(th),th) == YES) return(YES);
} else {return(YES);}
}
allfail:
Jpop_back(th);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("p"),arglist);
return(NO);}



static int b_foo(int arglist, int rest, int th);
static int b_foo(int arglist, int rest, int th){
int varX,n,body,save1,save2,save3,goal,cont,clause,res;
if(rest != NIL){
save1 = Jget_wp(th);
save2 = Jget_sp(th);
save3 = Jget_ac(th);
} else {
save1 = Jget_back_wp(th);
save2 = Jget_back_sp(th);
save3 = Jget_back_ac(th);
clause = Jget_back_choice(th);
}
n = Jlength(arglist);
if(n == 0){
if(rest == NIL){
switch(clause){
    case 0: goto clause0;
    default: goto allfail;
}}
loop0:
clause0:
varX = Jmakevariant(th);
Jpush_back(Jget_sp(th),0,Jget_wp(th),Jget_ac(th),th);
retry_p:
res = Jcall_nondet(Jmakecomp("p"),Jwcons(varX,NIL,th),th);
if(res == YES){
    if(Jcall_det(Jmakesys("write"),Jwcons(varX,NIL,th),th) == YES){
        if(Jcall_det(Jmakesys("fail"),NIL,th) == YES)
            return(YES);
        else
            goto retry_p;
    } else {
        goto retry_p;
    }
}

allfail:
Jpop_back(th);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("foo"),arglist);
return(NO);}
void init_tpredicate(void){(deftpred)("p",b_p,1,2);
(deftpred)("foo",b_foo,1,2);
}
void init_declare(void){int body,th; th=0;
}