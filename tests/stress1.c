#include "jump.h"
static int c_warm(int arglist, int rest, int th);
static int c_is_warm(int arglist, int rest, int th);
static int recur_scbm(int pred, int arity, int clause, int arglist, int rest, int th);
static int c_warm(int arglist, int rest, int th){
int arg1,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
if(n == 1){
arg1 = Jcar(arglist);
clause = Jget_choice(th);
switch(clause){
case 0: goto clause_1_0;
case 1: goto clause_1_1;
default: goto allfail;
}
clause_1_0:
Jinc_choice(th);
if(Junify_atom(arg1,Jmakeconst("red"),th) == YES)
return(YES);
clause_1_1:
Jrelease(th);
Jinc_choice(th);
if(Junify_atom(arg1,Jmakeconst("orange"),th) == YES)
return(YES);
clause_1_2:
Jrelease(th);
allfail:
Jdiscard_conj(th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("warm"),arglist);
return(NO);

}
static int c_is_warm(int arglist, int rest, int th){
int arg1,varX,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
if(n == 1){
arg1 = Jcar(arglist);
clause = Jget_choice(th);
switch(clause){
case 0: goto clause_1_0;
default: goto allfail;
}
clause_1_0:
varX = Jmakevariant(th);
Jinc_choice(th);
if(Junify_var(arg1,varX,th) == YES)
{
Jpush_conj(th);
retry_1_0_0:;
int arg_1_0_0 = Jwlistcons(varX,NIL,th);
if (c_warm(arg_1_0_0,NIL,th) == YES){
{Jsuccess(arglist,th); return(YES);}
}
}
clause_1_1:
Jrelease(th);
allfail:
Jdiscard_conj(th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("is_warm"),arglist);
return(NO);

}
void init_tpredicate(void){
(deftpred)("warm",c_warm,1,1);
(deftpred)("is_warm",c_is_warm,1,1);
}
void init_declare(void){
int body,th; th=0;
}
static int recur_scbm(int pred, int arity, int clause, int arglist, int rest, int th){
void *next;
int arg1,arg2,arg3,arg4,arg5,aeg6,arg7,arg8,arg9,arg10no