#include "jump.h"
static int b_p(int arglist, int rest, int th);
static int b_p(int arglist, int rest, int th){
int arg1,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_wp(th);
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 1){
arg1 = Jnth(arglist,1);
loop1:
save1 = Jget_wp(th);
if(Junify_int(arg1,Jmakeint(1),th) == YES && 1)
if(Jprove_all(rest,Jget_sp(th),th) == YES) return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
save1 = Jget_wp(th);
if(Junify_int(arg1,Jmakeint(2),th) == YES && 1)
if(Jprove_all(rest,Jget_sp(th),th) == YES) return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
allfail:return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("p"),arglist);
return(NO);}
void init_tpredicate(void){(deftpred)("p",b_p);
}
void init_declare(void){int body,th; th=0;
}