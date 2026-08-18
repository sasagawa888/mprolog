#include "jump.h"
static int c_partition(int arglist, int rest, int th);
static int user_scbm(int pred, int arity, int clause, int arglist, int rest, int th);
static int c_partition(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Ssave_arg(arglist,th);
return(user_scbm(0,n,0,arglist,rest,th));
}

void init_tpredicate(void){
(deftpred)("partition",c_partition,4,1);
}
void init_declare(void){
int body,th; th=0;
}
static int user_scbm(int pred, int arity, int clause, int arglist, int rest, int th){
void *next;
int arg1,arg2,arg3,arg4,arg5,aeg6,arg7,arg8,arg9,arg10,subr_number,varX_,varY_,varZ_,varA_,ano_1,varL,varL1,varL2,varX,varY;
np[th] = 0; rp[th] = 0; back_stack[0][AC_SCBM][th] = Jget_ac(th);
Spush_next(&&success,th);
switch(pred){
case 0: goto partition;
}
partition:
switch(arity){
case 4: goto partition_4;
default: goto allfail;
}
partition_4:
Jinc_proof(th);
switch(clause){
case 0: goto partition_4_0;
case 1: goto partition_4_1;
case 2: goto partition_4_2;
case 3: goto partition_4_3;
default: goto allfail;
}
partition_4_0:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
arg4 = Jnth(arglist,4);
Srelease(th);
varL = Jmakevariant(th);
varY = Jmakevariant(th);
varX = Jmakevariant(th);
varL1 = Jmakevariant(th);
varL2 = Jmakevariant(th);
Sinc_choice(th);
Sset_back(&&partition_4_1,th);
if(Junify_pair(arg1,Jwlistcons(varX,varL,th),th) == YES && Junify_var(arg2,varY,th) == YES && Junify_pair(arg3,Jwlistcons(varX,varL1,th),th) == YES && Junify_var(arg4,varL2,th) == YES)
{
partition_4_0_0:
arglist = Jwlistcons(varX,Jwlistcons(varY,NIL,th),th);
next_stack[np[th]+1][1][th] = varL;
next_stack[np[th]+1][2][th] = varY;
next_stack[np[th]+1][3][th] = varX;
next_stack[np[th]+1][4][th] = varL1;
next_stack[np[th]+1][5][th] = varL2;
Spush_next(&&partition_4_0_1,th);
subr_number = 77;
goto builtin_call;
partition_4_0_1:
varL= next_stack[np[th]+1][1][th];
varY= next_stack[np[th]+1][2][th];
varX= next_stack[np[th]+1][3][th];
varL1= next_stack[np[th]+1][4][th];
varL2= next_stack[np[th]+1][5][th];
arglist = Jwlistcons(varL,Jwlistcons(varY,Jwlistcons(varL1,Jwlistcons(varL2,NIL,th),th),th),th);
goto partition_4_0_1join;
partition_4_0_1back:
varL= next_stack[np[th]+1][1][th];
varY= next_stack[np[th]+1][2][th];
varX= next_stack[np[th]+1][3][th];
varL1= next_stack[np[th]+1][4][th];
varL2= next_stack[np[th]+1][5][th];
partition_4_0_1join:
next_stack[np[th]+1][1][th] = varL;
next_stack[np[th]+1][2][th] = varY;
next_stack[np[th]+1][3][th] = varX;
next_stack[np[th]+1][4][th] = varL1;
next_stack[np[th]+1][5][th] = varL2;
Spush_next(&&partition_4_0_2,th);
clause = Sget_choice(th);
goto partition_4;
partition_4_0_2:
goto success;
}
partition_4_1:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
arg4 = Jnth(arglist,4);
Srelease(th);
varL = Jmakevariant(th);
varY = Jmakevariant(th);
varL1 = Jmakevariant(th);
varX = Jmakevariant(th);
varL2 = Jmakevariant(th);
Sinc_choice(th);
Sset_back(&&partition_4_2,th);
if(Junify_pair(arg1,Jwlistcons(varX,varL,th),th) == YES && Junify_var(arg2,varY,th) == YES && Junify_var(arg3,varL1,th) == YES && Junify_pair(arg4,Jwlistcons(varX,varL2,th),th) == YES)
{
partition_4_1_0:
arglist = Jwlistcons(varL,Jwlistcons(varY,Jwlistcons(varL1,Jwlistcons(varL2,NIL,th),th),th),th);
Spush_back(&&partition_4_2,arglist,th);
goto partition_4_1_0join;
partition_4_1_0back:
varL= next_stack[np[th]+1][1][th];
varY= next_stack[np[th]+1][2][th];
varL1= next_stack[np[th]+1][3][th];
varX= next_stack[np[th]+1][4][th];
varL2= next_stack[np[th]+1][5][th];
partition_4_1_0join:
next_stack[np[th]+1][1][th] = varL;
next_stack[np[th]+1][2][th] = varY;
next_stack[np[th]+1][3][th] = varL1;
next_stack[np[th]+1][4][th] = varX;
next_stack[np[th]+1][5][th] = varL2;
Spush_next(&&partition_4_1_1,th);
clause = Sget_choice(th);
goto partition_4;
partition_4_1_1:
goto success;
}
partition_4_2:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
arg4 = Jnth(arglist,4);
Srelease(th);
ano_1 = Jmakevariant(th);
Sinc_choice(th);
Sset_back(&&partition_4_3,th);
if(Junify_nil(arg1,th) == YES && Junify_var(arg2,ano_1,th) == YES && Junify_nil(arg3,th) == YES && Junify_nil(arg4,th) == YES)
{
goto success;
}
partition_4_3:
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
if(Jcallsubr(subr_number,Jderef(arglist,th),NIL,th) == YES)
goto success;
else goto allfail;
#include "scbm.h"
}
