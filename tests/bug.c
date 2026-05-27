#include "jump.h"
static int b_p(int arglist, int rest, int th);
static int b_p(int arglist, int rest, int th){
int arg1,n,body,save1,save2,save3,goal,cont,res;
save1 = Jget_wp(th);
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 1){
arg1 = Jnth(arglist,1);
loop1:
if(Junify_int(arg1,Jmakeint(1),th) == YES && 1)
if(Jprove_all(rest,Jget_sp(th),th) == YES) return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
if(Junify_int(arg1,Jmakeint(2),th) == YES && 1)
if(Jprove_all(rest,Jget_sp(th),th) == YES) return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("p"),arglist);
return(NO);}
static int b_foo(int arglist, int rest, int th);
static int b_foo(int arglist, int rest, int th){
int varX,n,body,save1,save2,save3,goal,cont,res;
save1 = Jget_wp(th);
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 0){
loop0:
varX = Jmakevariant(th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("foo"),arglist);
return(NO);}
void init_tpredicate(void){(deftpred)("p",b_p);
(deftpred)("foo",b_foo);
}
void init_declare(void){int body,th; th=0;
}