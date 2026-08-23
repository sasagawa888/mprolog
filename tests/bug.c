#include "jump.h"
static int c_test(int arglist, int rest, int th);
static int c_test1(int arglist, int rest, int th);
static int c_between1(int arglist, int rest, int th);
static int c_select1(int arglist, int rest, int th);
static int c_perm1(int arglist, int rest, int th);
static int user_scbm(int pred, int arity, int clause, int arglist, int rest, int th);
static int c_test(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Ssave_arg(arglist,th);
return(user_scbm(0,n,0,arglist,rest,th));
}

static int c_test1(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Ssave_arg(arglist,th);
return(user_scbm(1,n,0,arglist,rest,th));
}

static int c_between1(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Ssave_arg(arglist,th);
return(user_scbm(2,n,0,arglist,rest,th));
}

static int c_select1(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Ssave_arg(arglist,th);
return(user_scbm(3,n,0,arglist,rest,th));
}

static int c_perm1(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Ssave_arg(arglist,th);
return(user_scbm(4,n,0,arglist,rest,th));
}

void init_tpredicate(void){
(deftpred)("test",c_test,0,1);
(deftpred)("test1",c_test1,0,1);
(deftpred)("between1",c_between1,3,1);
(deftpred)("select1",c_select1,3,1);
(deftpred)("perm1",c_perm1,2,1);
}
void init_declare(void){
int body,th; th=0;
}
static int user_scbm(int pred, int arity, int clause, int arglist, int rest, int th){
void *next;
int arg1,arg2,arg3,arg4,arg5,aeg6,arg7,arg8,arg9,arg10,subr_number,varX_,varY_,varZ_,varA_,varH,varL,varL1,varX,varXs,varY,varYs,varZs;
np[th] = 0; rp[th] = 0; back_stack[0][AC_SCBM][th] = Jget_ac(th);
Spush_next(&&success,th);
switch(pred){
case 0: goto test;
case 1: goto test1;
case 2: goto between1;
case 3: goto select1;
case 4: goto perm1;
}
test:
switch(arity){
case 0: goto test_0;
default: goto allfail;
}
test1:
switch(arity){
case 0: goto test1_0;
default: goto allfail;
}
between1:
switch(arity){
case 3: goto between1_3;
default: goto allfail;
}
select1:
switch(arity){
case 3: goto select1_3;
default: goto allfail;
}
perm1:
switch(arity){
case 2: goto perm1_2;
default: goto allfail;
}
test_0:
Jinc_proof(th);
switch(clause){
case 0: goto test_0_0;
case 1: goto test_0_1;
default: goto allfail;
}
test1_0:
Jinc_proof(th);
switch(clause){
case 0: goto test1_0_0;
case 1: goto test1_0_1;
default: goto allfail;
}
between1_3:
Jinc_proof(th);
switch(clause){
case 0: goto between1_3_0;
case 1: goto between1_3_1;
case 2: goto between1_3_2;
default: goto allfail;
}
select1_3:
Jinc_proof(th);
switch(clause){
case 0: goto select1_3_0;
case 1: goto select1_3_1;
case 2: goto select1_3_2;
default: goto allfail;
}
perm1_2:
Jinc_proof(th);
switch(clause){
case 0: goto perm1_2_0;
case 1: goto perm1_2_1;
case 2: goto perm1_2_2;
default: goto allfail;
}
test_0_0:
Srelease(th);
Sinc_choice(th);
Sset_back(&&test_0_1,th);
{
test_0_0_0_1:
goto allfail;
test_0_0_0_2:
arglist = Jwlistcons(Jmakeint(2),NIL,th);
Spush_back(&&test_0_1,arglist,th);
Spush_next(&&test_0_0_1_2,th);subr_number = 1204;
goto builtin_call;
test_0_0_1_2:
goto test_0_0_1;
test_0_0_1:
goto success;
}
test_0_1:
Sreset_back(th);
goto allfail;

test1_0_0:
Srelease(th);
varX = Jmakevariant(th);
Sinc_choice(th);
Sset_back(&&test1_0_1,th);
{
test1_0_0_0:
arglist = Jwlistcons(Jmakeint(1),Jwlistcons(Jmakeint(10),Jwlistcons(varX,NIL,th),th),th);
back_stack[rp[th]+1][1][th] = varX;
Spush_back(&&test1_0_1,arglist,th);
goto test1_0_0_0join;
test1_0_0_0back:
varX= back_stack[rp[th]+1][1][th];
test1_0_0_0join:
next_stack[np[th]+1][1][th] = varX;
Spush_next(&&test1_0_0_1,th);
clause = Sget_choice(th);
goto between1_3;
test1_0_0_1:
varX= next_stack[np[th]+1][1][th];
arglist = Jwlistcons(varX,NIL,th);
back_stack[rp[th]+1][1][th] = varX;
Spush_back(&&test1_0_0_0back,arglist,th);
next_stack[np[th]+1][1][th] = varX;
Spush_next(&&test1_0_0_2,th);
subr_number = 1204;
goto builtin_call;
test1_0_0_2:
goto allfail;
}
test1_0_1:
Sreset_back(th);
goto allfail;

between1_3_0:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
Srelease(th);
varH = Jmakevariant(th);
varL = Jmakevariant(th);
Sinc_choice(th);
Sset_back(&&between1_3_1,th);
if(Junify_var(arg1,varL,th) == YES && Junify_var(arg2,varH,th) == YES && Junify_var(arg3,varL,th) == YES)
{
between1_3_0_0:
arglist = Jwlistcons(varL,Jwlistcons(varH,NIL,th),th);
back_stack[rp[th]+1][1][th] = varH;
back_stack[rp[th]+1][2][th] = varL;
Spush_back(&&between1_3_1,arglist,th);
next_stack[np[th]+1][1][th] = varH;
next_stack[np[th]+1][2][th] = varL;
Spush_next(&&between1_3_0_1,th);subr_number = 88;
goto builtin_call;
between1_3_0_1:
goto success;
}
between1_3_1:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
Srelease(th);
varL1 = Jmakevariant(th);
varL = Jmakevariant(th);
varH = Jmakevariant(th);
varX = Jmakevariant(th);
Sinc_choice(th);
Sset_back(&&between1_3_2,th);
if(Junify_var(arg1,varL,th) == YES && Junify_var(arg2,varH,th) == YES && Junify_var(arg3,varX,th) == YES)
{
between1_3_1_0:
arglist = Jwlistcons(varL,Jwlistcons(varH,NIL,th),th);
back_stack[rp[th]+1][1][th] = varL1;
back_stack[rp[th]+1][2][th] = varL;
back_stack[rp[th]+1][3][th] = varH;
back_stack[rp[th]+1][4][th] = varX;
Spush_back(&&between1_3_2,arglist,th);
next_stack[np[th]+1][1][th] = varL1;
next_stack[np[th]+1][2][th] = varL;
next_stack[np[th]+1][3][th] = varH;
next_stack[np[th]+1][4][th] = varX;
Spush_next(&&between1_3_1_1,th);
subr_number = 77;
goto builtin_call;
between1_3_1_1:
varL1= next_stack[np[th]+1][1][th];
varL= next_stack[np[th]+1][2][th];
varH= next_stack[np[th]+1][3][th];
varX= next_stack[np[th]+1][4][th];
arglist = Jwlistcons(varL1,Jwlistcons(Jwcons(2179,Jwcons(varL,Jwcons(Jmakeint(1),NIL,th),th),th),NIL,th),th);
Spush_back(&&between1_3_2,arglist,th);
next_stack[np[th]+1][1][th] = varL1;
next_stack[np[th]+1][2][th] = varL;
next_stack[np[th]+1][3][th] = varH;
next_stack[np[th]+1][4][th] = varX;
Spush_next(&&between1_3_1_2,th);
subr_number = 187;
goto builtin_call;
between1_3_1_2:
varL1= next_stack[np[th]+1][1][th];
varL= next_stack[np[th]+1][2][th];
varH= next_stack[np[th]+1][3][th];
varX= next_stack[np[th]+1][4][th];
arglist = Jwlistcons(varL1,Jwlistcons(varH,Jwlistcons(varX,NIL,th),th),th);
Spush_back(&&between1_3_2,arglist,th);
goto between1_3_1_2join;
between1_3_1_2back:
varL1= back_stack[rp[th]+1][1][th];
varL= back_stack[rp[th]+1][2][th];
varH= back_stack[rp[th]+1][3][th];
varX= back_stack[rp[th]+1][4][th];
between1_3_1_2join:
next_stack[np[th]+1][1][th] = varL1;
next_stack[np[th]+1][2][th] = varL;
next_stack[np[th]+1][3][th] = varH;
next_stack[np[th]+1][4][th] = varX;
Spush_next(&&between1_3_1_3,th);
clause = Sget_choice(th);
goto between1_3;
between1_3_1_3:
goto success;
}
between1_3_2:
Sreset_back(th);
goto allfail;

select1_3_0:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
Srelease(th);
varX = Jmakevariant(th);
varXs = Jmakevariant(th);
Sinc_choice(th);
Sset_back(&&select1_3_1,th);
if(Junify_var(arg1,varX,th) == YES && Junify_pair(arg2,Jwlistcons(varX,varXs,th),th) == YES && Junify_var(arg3,varXs,th) == YES)
{
goto success;
}
select1_3_1:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
Srelease(th);
varX = Jmakevariant(th);
varYs = Jmakevariant(th);
varY = Jmakevariant(th);
varZs = Jmakevariant(th);
Sinc_choice(th);
Sset_back(&&select1_3_2,th);
if(Junify_var(arg1,varX,th) == YES && Junify_pair(arg2,Jwlistcons(varY,varYs,th),th) == YES && Junify_pair(arg3,Jwlistcons(varY,varZs,th),th) == YES)
{
select1_3_1_0:
arglist = Jwlistcons(varX,Jwlistcons(varYs,Jwlistcons(varZs,NIL,th),th),th);
back_stack[rp[th]+1][1][th] = varX;
back_stack[rp[th]+1][2][th] = varYs;
back_stack[rp[th]+1][3][th] = varY;
back_stack[rp[th]+1][4][th] = varZs;
Spush_back(&&select1_3_2,arglist,th);
goto select1_3_1_0join;
select1_3_1_0back:
varX= back_stack[rp[th]+1][1][th];
varYs= back_stack[rp[th]+1][2][th];
varY= back_stack[rp[th]+1][3][th];
varZs= back_stack[rp[th]+1][4][th];
select1_3_1_0join:
next_stack[np[th]+1][1][th] = varX;
next_stack[np[th]+1][2][th] = varYs;
next_stack[np[th]+1][3][th] = varY;
next_stack[np[th]+1][4][th] = varZs;
Spush_next(&&select1_3_1_1,th);
clause = Sget_choice(th);
goto select1_3;
select1_3_1_1:
goto success;
}
select1_3_2:
Sreset_back(th);
goto allfail;

perm1_2_0:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
Srelease(th);
Sinc_choice(th);
Sset_back(&&perm1_2_1,th);
if(Junify_nil(arg1,th) == YES && Junify_nil(arg2,th) == YES)
{
goto success;
}
perm1_2_1:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
Srelease(th);
varZs = Jmakevariant(th);
varXs = Jmakevariant(th);
varX = Jmakevariant(th);
varYs = Jmakevariant(th);
Sinc_choice(th);
Sset_back(&&perm1_2_2,th);
if(Junify_var(arg1,varXs,th) == YES && Junify_pair(arg2,Jwlistcons(varX,varYs,th),th) == YES)
{
perm1_2_1_0:
arglist = Jwlistcons(varX,Jwlistcons(varXs,Jwlistcons(varZs,NIL,th),th),th);
back_stack[rp[th]+1][1][th] = varZs;
back_stack[rp[th]+1][2][th] = varXs;
back_stack[rp[th]+1][3][th] = varX;
back_stack[rp[th]+1][4][th] = varYs;
Spush_back(&&perm1_2_2,arglist,th);
goto perm1_2_1_0join;
perm1_2_1_0back:
varZs= back_stack[rp[th]+1][1][th];
varXs= back_stack[rp[th]+1][2][th];
varX= back_stack[rp[th]+1][3][th];
varYs= back_stack[rp[th]+1][4][th];
perm1_2_1_0join:
next_stack[np[th]+1][1][th] = varZs;
next_stack[np[th]+1][2][th] = varXs;
next_stack[np[th]+1][3][th] = varX;
next_stack[np[th]+1][4][th] = varYs;
Spush_next(&&perm1_2_1_1,th);
clause = Sget_choice(th);
goto select1_3;
perm1_2_1_1:
varZs= next_stack[np[th]+1][1][th];
varXs= next_stack[np[th]+1][2][th];
varX= next_stack[np[th]+1][3][th];
varYs= next_stack[np[th]+1][4][th];
arglist = Jwlistcons(varZs,Jwlistcons(varYs,NIL,th),th);
back_stack[rp[th]+1][1][th] = varZs;
back_stack[rp[th]+1][2][th] = varXs;
back_stack[rp[th]+1][3][th] = varX;
back_stack[rp[th]+1][4][th] = varYs;
Spush_back(&&perm1_2_1_0back,arglist,th);
goto perm1_2_1_1join;
perm1_2_1_1back:
varZs= back_stack[rp[th]+1][1][th];
varXs= back_stack[rp[th]+1][2][th];
varX= back_stack[rp[th]+1][3][th];
varYs= back_stack[rp[th]+1][4][th];
perm1_2_1_1join:
next_stack[np[th]+1][1][th] = varZs;
next_stack[np[th]+1][2][th] = varXs;
next_stack[np[th]+1][3][th] = varX;
next_stack[np[th]+1][4][th] = varYs;
Spush_next(&&perm1_2_1_2,th);
clause = Sget_choice(th);
goto perm1_2;
perm1_2_1_2:
goto success;
}
perm1_2_2:
Sreset_back(th);
goto allfail;

success:
if(np[th] == 0){
if(Jprove_all(rest,Jget_sp(th),th) == YES) return(YES);
next = back_goto[rp[th]][th];
clause = Sget_choice(th);
arglist = Sget_arg(th);
np[th] = Sget_np(th);
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
}
