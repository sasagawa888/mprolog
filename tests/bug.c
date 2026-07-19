#include "jump.h"
static int c_mappend(int arglist, int rest, int th);
static int recur_scbm(int pred, int arity, int clause, int arglist, int th);
static int c_mappend(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
return(recur_scbm(0,n,Jget_choice(th),arglist,th));
}
void init_tpredicate(void){
(deftpred)("mappend",c_mappend,3,6);
}
void init_declare(void){
int body,th; th=0;
}
static int recur_scbm(int pred, int arity, int clause, int arglist, int th){
void *next;
int index,arg1,arg2,arg3,arg4,arg5,aeg6,arg7,arg8,arg9,arg10,varA,varX,varY,varZ;
np[Jget_scp(CONJ,th)][th] = 0;
switch(pred){
case 0: goto mappend;
}
mappend:
switch(arity){
case 3: goto mappend_3;
}
mappend_3:
switch(clause){
case 0: goto mappend_3_0;
case 1: goto mappend_3_1;
default: goto allfail;
}
mappend_3_0:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
varX = Jmakevariant(th);
Jinc_choice(th);
if(Junify_nil(arg1,th) == YES && Junify_var(arg2,varX,th) == YES && Junify_var(arg3,varX,th) == YES)
{
goto success;
}
Jrelease(th);
mappend_3_1:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
varX = Jmakevariant(th);
varY = Jmakevariant(th);
varA = Jmakevariant(th);
varZ = Jmakevariant(th);
Jinc_choice(th);
Jset_next_clause(&&mappend_3_2,th);
if(Junify_pair(arg1,Jwlistcons(varA,varX,th),th) == YES && Junify_var(arg2,varY,th) == YES && Junify_pair(arg3,Jwlistcons(varA,varZ,th),th) == YES)
{
arglist = Jwlistcons(varX,Jwlistcons(varY,Jwlistcons(varZ,NIL,th),th),th);
mappend_3_1_0:
Jpush_recur(NIL,th);
Jget_choice(th);
goto mappend_3;
}
Jrelease(th);
mappend_3_2:
goto allfail;

success:
if(np[Jget_scp(CONJ,th)][th] == 0) return(YES);
else{
next = next_stack[np[Jget_scp(CONJ,th)][th]][Jget_scp(CONJ,th)][th];
Jpop_next(th);
goto *next;}
allfail:
Jpop_recur(th);
Jpop_next(th);
index = Jget_cont(th);
if(index == 0) {
next = next_clause[th];
if(next == NIL) return(NO);
goto *next;
}
else{
next = next_stack[index][Jget_scp(CONJ,th)][th];
Jset_mode(1,th);
clause = Jget_choice(th);
goto *next;}
}
