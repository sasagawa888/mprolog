#include "jump.h"
static int c_mbetween(int arglist, int rest, int th);
static int user_scbm(int pred, int arity, int clause, int arglist, int rest, int th);
static int c_mbetween(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Ssave_arg(arglist,th);
return(user_scbm(0,n,0,arglist,rest,th));
}

void init_tpredicate(void){
(deftpred)("mbetween",c_mbetween,3,1);
}
void init_declare(void){
int body,th; th=0;
}
static int user_scbm(int pred, int arity, int clause, int arglist, int rest, int th){
void *next;
int arg1,arg2,arg3,arg4,arg5,aeg6,arg7,arg8,arg9,arg10,subr_number,varX_,varY_,varZ_,varA_,varA_,varX_,varY_,varZ_;
np[th] = 0; rp[th] = 0; back_stack[0][AC_SCBM][th] = Jget_ac(th);
Spush_next(&&success,th);
switch(pred){
case 0: goto mbetween;
}
mbetween:
switch(arity){
case 3: goto mbetween_3;
default: goto allfail;
}
mbetween_3:
Jinc_proof(th);
switch(clause){
case 0: goto mbetween_3_0;
case 1: goto mbetween_3_1;
case 2: goto mbetween_3_2;
default: goto allfail;
}
mbetween_3_0:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
Srelease(th);
varY_ = Jmakevariant(th);
varX_ = Jmakevariant(th);
Sinc_choice(th);
Sset_back(&&mbetween_3_1,th);
if(Junify_var(arg1,varX_,th) == YES && Junify_var(arg2,varY_,th) == YES && Junify_var(arg3,varX_,th) == YES)
{
mbetween_3_0_0:
arglist = Jwlistcons(varX_,Jwlistcons(varY_,NIL,th),th);
next_stack[np[th]+1][1][th] = varY_;
next_stack[np[th]+1][2][th] = varX_;
Spush_next(&&mbetween_3_0_1,th);subr_number = 88;
goto builtin_call;
mbetween_3_0_1:
goto success;
}
mbetween_3_1:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
Srelease(th);
varA_ = Jmakevariant(th);
varX_ = Jmakevariant(th);
varY_ = Jmakevariant(th);
varZ_ = Jmakevariant(th);
Sinc_choice(th);
Sset_back(&&mbetween_3_2,th);
if(Junify_var(arg1,varX_,th) == YES && Junify_var(arg2,varY_,th) == YES && Junify_var(arg3,varZ_,th) == YES)
{
mbetween_3_1_0:
arglist = Jwlistcons(varX_,Jwlistcons(varY_,NIL,th),th);
next_stack[np[th]+1][1][th] = varA_;
next_stack[np[th]+1][2][th] = varX_;
next_stack[np[th]+1][3][th] = varY_;
next_stack[np[th]+1][4][th] = varZ_;
Spush_next(&&mbetween_3_1_1,th);
subr_number = 77;
goto builtin_call;
mbetween_3_1_1:
varA_= next_stack[np[th]+1][1][th];
varX_= next_stack[np[th]+1][2][th];
varY_= next_stack[np[th]+1][3][th];
varZ_= next_stack[np[th]+1][4][th];
arglist = Jwlistcons(varA_,Jwlistcons(Jwcons(2179,Jwcons(varX_,Jwcons(Jmakeint(1),NIL,th),th),th),NIL,th),th);
next_stack[np[th]+1][1][th] = varA_;
next_stack[np[th]+1][2][th] = varX_;
next_stack[np[th]+1][3][th] = varY_;
next_stack[np[th]+1][4][th] = varZ_;
Spush_next(&&mbetween_3_1_2,th);
subr_number = 187;
goto builtin_call;
mbetween_3_1_2:
varA_= next_stack[np[th]+1][1][th];
varX_= next_stack[np[th]+1][2][th];
varY_= next_stack[np[th]+1][3][th];
varZ_= next_stack[np[th]+1][4][th];
arglist = Jwlistcons(varA_,Jwlistcons(varY_,Jwlistcons(varZ_,NIL,th),th),th);
goto mbetween_3_1_2join;
mbetween_3_1_2back:
varA_= next_stack[np[th]+1][1][th];
varX_= next_stack[np[th]+1][2][th];
varY_= next_stack[np[th]+1][3][th];
varZ_= next_stack[np[th]+1][4][th];
mbetween_3_1_2join:
next_stack[np[th]+1][1][th] = varA_;
next_stack[np[th]+1][2][th] = varX_;
next_stack[np[th]+1][3][th] = varY_;
next_stack[np[th]+1][4][th] = varZ_;
Spush_next(&&mbetween_3_1_3,th);
clause = Sget_choice(th);
goto mbetween_3;
mbetween_3_1_3:
goto success;
}
mbetween_3_2:
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
