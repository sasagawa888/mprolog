#include "jump.h"
static int b_p(int arglist, int rest, int th);
static int b_p(int arglist, int rest, int th){
int arg1,n,body,save1,save2,save3,goal,cont,clause,res;
if(rest != NIL){
save1 = Jget_wp(th);
save2 = Jget_sp(th);
save3 = Jget_ac(th);
Jpop_back(th);
} else {
save1 = Jget_back_wp(th);
save2 = Jget_back_sp(th);
save3 = Jget_back_ac(th);
clause = Jget_back_clause(th);
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
if(Junify_int(arg1,Jmakeint(1),th) == YES && 1)
if(rest != NIL){
if(Jprove_all(rest,Jget_sp(th),th) == YES) return(YES);
} else return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
save1 = Jget_wp(th);
inc_back_choice(th);
clause1:
if(Junify_int(arg1,Jmakeint(2),th) == YES && 1)
if(rest != NIL){
if(Jprove_all(rest,Jget_sp(th),th) == YES) return(YES);
} else return(YES);
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
Jpop_back(th);
} else {
save1 = Jget_back_wp(th);
save2 = Jget_back_sp(th);
save3 = Jget_back_ac(th);
clause = Jget_back_clause(th);
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
push_back(Jget_sp(th),0,Jget_wp(th),Jget_ac(th),th);
retry_p:
res = Jcall(Jmakecomp("p"),Jwcons(varX,NIL,th),th);
if(res == YES){
    if(Jcall(Jsystem("write"),Jwcons(varX,NIL,th),th) == YES){
        if(Jcall(Jsystem("fail"),NIL,th) == YES)
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
void init_tpredicate(void){(deftpred)("p",b_p);
(deftpred)("foo",b_foo);
}
void init_declare(void){int body,th; th=0;
}