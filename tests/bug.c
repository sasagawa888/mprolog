#include "jump.h"
static int b_p(int arglist, int rest, int th);
static int b_p(int arglist, int rest, int th){
int arg1,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jlength(arglist);
if(rest != NIL){
save1 = Jget_wp(th);
save2 = Jget_sp(th);
save3 = Jget_ac(th);
}else{
save1 = Jget_back_wp(th);
save2 = Jget_back_sp(th);
save3 = Jget_back_ac(th);
clause = Jget_back_choice(th);}
if(n == 1){
arg1 = Jnth(arglist,1);
if(rest == NIL){
Jset_ac(save3,th);
Junbind(save2,th);
clause = Jget_back_choice(th);
switch(clause){
case 0: goto clause_1_0;
case 1: goto clause_1_1;
default: goto allfail;
}}loop1:
clause_1_0:
if(rest == NIL){
Jset_ac(save3,th);
Junbind(save2,th);
Jinc_back_choice(th);
arg1 = Jnth(arglist,1);
}
if(Junify_int(arg1,Jmakeint(1),th) == YES && 1)
if(rest!=NIL){
if(Jprove_all(rest,Jget_sp(th),th) == YES) return(YES);}
else return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
clause_1_1:
if(rest == NIL){
Jset_ac(save3,th);
Junbind(save2,th);
Jinc_back_choice(th);
arg1 = Jnth(arglist,1);
}
if(Junify_int(arg1,Jmakeint(2),th) == YES && 1)
if(rest!=NIL){
if(Jprove_all(rest,Jget_sp(th),th) == YES) return(YES);}
else return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
allfail:
Jpop_back(th);
//Jset_wp(save1,th);
Junbind(save2,th);
Jset_ac(save3,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("p"),arglist);
return(NO);}
static int b_foo(int arglist, int rest, int th);
static int b_foo(int arglist, int rest, int th){
int varX,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jlength(arglist);
if(rest != NIL){
save1 = Jget_wp(th); printf("foo%d",save1);
save2 = Jget_sp(th);
save3 = Jget_ac(th);
}else{
save1 = Jget_back_wp(th);
save2 = Jget_back_sp(th);
save3 = Jget_back_ac(th);
clause = Jget_back_choice(th);}
if(n == 0){
if(rest == NIL){
Jset_ac(save3,th);
Junbind(save2,th);
clause = Jget_back_choice(th);
switch(clause){
case 0: goto clause_0_0;
case 1: goto clause_0_1;
default: goto allfail;
}}loop0:
clause_0_0:
varX = Jmakevariant(th);
if(rest == NIL){
Jset_ac(save3,th);
Junbind(save2,th);
Jinc_back_choice(th);
}
printf("foo2%d",Jget_wp(th));
Jpush_back(Jget_sp(th),0,Jget_wp(th),Jget_ac(th),th);
retry_0_0_0:
printf("foo3%d",Jget_wp(th));
if (Jcall_nondet(Jmakecomp("p"),Jwlistcons(varX,NIL,th),th) == YES){
if (Jcall_det(Jmakesys("write"),Jwlistcons(varX,NIL,th),th) == YES){
if(Jcall_det(Jmakesys("fail"),NIL,th) == YES){
if(rest != NIL) Jprove_all(body,Jget_sp(th),th);else return(YES);}else goto retry_0_0_0;
}else goto retry_0_0_0;
}
clause_0_1:
printf("exit0%d",Jget_wp(th));
if(rest == NIL){
Jset_ac(save3,th);
Junbind(save2,th);
Jinc_back_choice(th);
}
if(rest!=NIL){
    printf("exit%d",Jget_wp(th));
return(Jprove_all(rest,Jget_sp(th),th));}
else return(YES);
allfail:
Jpop_back(th);
Jset_wp(save1,th);
Junbind(save2,th);
Jset_ac(save3,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("foo"),arglist);
return(NO);}
void init_tpredicate(void){(deftpred)("p",b_p,1,2);
(deftpred)("foo",b_foo,1,2);
}
void init_declare(void){int body,th; th=0;
}