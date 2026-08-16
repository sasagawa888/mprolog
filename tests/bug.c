#include "jump.h"
static int c_mmember(int arglist, int rest, int th);
static int user_scbm(int pred, int arity, int clause, int arglist, int rest, int th);
static int c_mmember(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Ssave_arg(arglist,th);
return(user_scbm(0,n,0,arglist,rest,th));
}

void init_tpredicate(void){
(deftpred)("mmember",c_mmember,2,1);
}
void init_declare(void){
int body,th; th=0;
}
static int user_scbm(int pred, int arity, int clause, int arglist, int rest, int th){
void *next;
int arg1,arg2,arg3,arg4,arg5,aeg6,arg7,arg8,arg9,arg10,subr_number,varX_,varY_,varZ_,varA_,ano_1,varX_,varY_;
np[th] = 0; rp[th] = 0; back_stack[0][AC_SCBM][th] = Jget_ac(th);
Spush_next(&&success,th);
switch(pred){
case 0: goto mmember;
}
mmember:
switch(arity){
case 2: goto mmember_2;
default: goto allfail;
}
mmember_2:
Jinc_proof(th);
switch(clause){
case 0: goto mmember_2_0;
case 1: goto mmember_2_1;
case 2: goto mmember_2_2;
default: goto allfail;
}
mmember_2_0:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
Srelease(th);
varX_ = Jmakevariant(th);
ano_1 = Jmakevariant(th);
Sinc_choice(th);
Sset_back(&&mmember_2_1,th);
if(Junify_var(arg1,varX_,th) == YES && Junify_pair(arg2,Jwlistcons(varX_,ano_1,th),th) == YES)
{
goto success;
}
mmember_2_1:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
Srelease(th);
varX_ = Jmakevariant(th);
ano_1 = Jmakevariant(th);
varY_ = Jmakevariant(th);
Sinc_choice(th);
Sset_back(&&mmember_2_2,th);
if(Junify_var(arg1,varX_,th) == YES && Junify_pair(arg2,Jwlistcons(ano_1,varY_,th),th) == YES)
{
mmember_2_1_0:
arglist = Jwlistcons(varX_,Jwlistcons(varY_,NIL,th),th);
Spush_back(&&mmember_2_2,arglist,th);
goto mmember_2_1_0join;
mmember_2_1_0back:
varX_= next_stack[np[th]+1][1][th];
ano_1= next_stack[np[th]+1][2][th];
varY_= next_stack[np[th]+1][3][th];
mmember_2_1_0join:
next_stack[np[th]+1][1][th] = varX_;
next_stack[np[th]+1][2][th] = ano_1;
next_stack[np[th]+1][3][th] = varY_;
Spush_next(&&mmember_2_1_1,th);
clause = Sget_choice(th);
goto mmember_2;
mmember_2_1_1:
goto success;
}
mmember_2_2:
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
#include "scbm.h"
}
