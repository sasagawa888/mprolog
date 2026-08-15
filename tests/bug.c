#include "jump.h"
static int c_mappend(int arglist, int rest, int th);
static int user_scbm(int pred, int arity, int clause, int arglist, int rest, int th);
static int c_mappend(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Ssave_arg(arglist,th);
return(user_scbm(0,n,0,arglist,rest,th));
}

void init_tpredicate(void){
(deftpred)("mappend",c_mappend,3,1);
}
void init_declare(void){
int body,th; th=0;
}
static int user_scbm(int pred, int arity, int clause, int arglist, int rest, int th){
void *next;
int arg1,arg2,arg3,arg4,arg5,aeg6,arg7,arg8,arg9,arg10,subr_number,varA,varX,varY,varZ;
np[th] = 0; rp[th] = 0; back_stack[0][AC_SCBM][th] = Jget_ac(th);
Spush_next(&&success,th);
switch(pred){
case 0: goto mappend;
}
mappend:
switch(arity){
case 3: goto mappend_3;
default: goto allfail;
}
mappend_3:
Jinc_proof(th);
switch(clause){
case 0: goto mappend_3_0;
case 1: goto mappend_3_1;
case 2: goto mappend_3_2;
default: goto allfail;
}
mappend_3_0:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
Srelease(th);
varX = Jmakevariant(th);
Sinc_choice(th);
Sset_back(&&mappend_3_1,th);
if(Junify_nil(arg1,th) == YES && Junify_var(arg2,varX,th) == YES && Junify_var(arg3,varX,th) == YES)
{
goto success;
}
mappend_3_1:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
Srelease(th);
varX = Jmakevariant(th);
varY = Jmakevariant(th);
varA = Jmakevariant(th);
varZ = Jmakevariant(th);
Sinc_choice(th);
Sset_back(&&mappend_3_2,th);
if(Junify_pair(arg1,Jwlistcons(varA,varX,th),th) == YES && Junify_var(arg2,varY,th) == YES && Junify_pair(arg3,Jwlistcons(varA,varZ,th),th) == YES)
{
mappend_3_1_0:
arglist = Jwlistcons(varX,Jwlistcons(varY,Jwlistcons(varZ,NIL,th),th),th);
Spush_back(&&mappend_3_2,arglist,th);
goto mappend_3_1_0join;
mappend_3_1_0back:
varX= next_stack[np[th]+1][1][th];
varY= next_stack[np[th]+1][2][th];
varA= next_stack[np[th]+1][3][th];
varZ= next_stack[np[th]+1][4][th];
mappend_3_1_0join:
next_stack[np[th]+1][1][th] = varX;
next_stack[np[th]+1][2][th] = varY;
next_stack[np[th]+1][3][th] = varA;
next_stack[np[th]+1][4][th] = varZ;
Spush_next(&&mappend_3_1_1,th);
clause = Sget_choice(th);
goto mappend_3;
mappend_3_1_1:
goto success;
}
mappend_3_2:
Sreset_back(th);
goto allfail;

success:
if(np[th] == 0){
if(Jprove_all(rest,Jget_sp(th),th) == YES) return(YES);
next = back_goto[rp[th]][th];
clause = Sget_choice(th);
arglist = Sget_arg(th);
Spush_next(&&success,th);
goto *next;
}else{
next = next_goto[np[th]][th];
Spop_next(th);
clause = Sget_choice(th);
goto *next;}
allfail:
if(rp[th]==0) {return(NO);}
next = back_goto[rp[th]][th];
np[th] = Sget_np(th);
Spop_back(th);
arglist = Sget_arg(th);
goto *next;
builtin_call:
if(Jcallsubr(subr_number,arglist,NIL,th) == YES)
goto success;
else goto allfail;
}
