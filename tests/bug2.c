#include "jump.h"
static int c_check(int arglist, int rest, int th);
static int c_queen2(int arglist, int rest, int th);
static int c_qdelete(int arglist, int rest, int th);
static int c_test(int arglist, int rest, int th);
static int c_check1(int arglist, int rest, int th);
static int user_scbm(int pred, int arity, int clause, int arglist, int rest, int th);
static int c_check(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Jsave_arg(arglist,th);
return(user_scbm(0,n,0,arglist,rest,th));
}

static int c_queen2(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Jsave_arg(arglist,th);
return(user_scbm(1,n,0,arglist,rest,th));
}

static int c_qdelete(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Jsave_arg(arglist,th);
return(user_scbm(2,n,0,arglist,rest,th));
}

static int c_test(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Jsave_arg(arglist,th);
return(user_scbm(3,n,0,arglist,rest,th));
}

static int c_check1(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Jsave_arg(arglist,th);
return(user_scbm(4,n,0,arglist,rest,th));
}

void init_tpredicate(void){
(deftpred)("check",c_check,2,1);
(deftpred)("queen2",c_queen2,3,1);
(deftpred)("qdelete",c_qdelete,4,1);
(deftpred)("test",c_test,1,1);
(deftpred)("check1",c_check1,1,1);
}
void init_declare(void){
int body,th; th=0;
}
static int user_scbm(int pred, int arity, int clause, int arglist, int rest, int th){
void *next;
int arg1,arg2,arg3,arg4,arg5,aeg6,arg7,arg8,arg9,arg10,subr_number,base,pointer,ano_1,varA,varH,varHistory,varL,varL1,varM,varQ,varR,varT,varX;
np[Jget_scp(CONJ,th)][th] = 0; vp[th] = 0;
Jpush_next(&&success,Jget_ac(th),th);
switch(pred){
case 0: goto check;
case 1: goto queen2;
case 2: goto qdelete;
case 3: goto test;
case 4: goto check1;
}
check:
switch(arity){
case 2: goto check_2;
default: goto allfail;
}
queen2:
switch(arity){
case 3: goto queen2_3;
default: goto allfail;
}
qdelete:
switch(arity){
case 4: goto qdelete_4;
default: goto allfail;
}
test:
switch(arity){
case 1: goto test_1;
default: goto allfail;
}
check1:
switch(arity){
case 1: goto check1_1;
default: goto allfail;
}
check_2:
switch(clause){
case 0: goto check_2_0;
case 1: goto check_2_1;
case 2: goto check_2_2;
case 3: goto check_2_3;
default: goto allfail;
}
queen2_3:
switch(clause){
case 0: goto queen2_3_0;
case 1: goto queen2_3_1;
case 2: goto queen2_3_2;
default: goto allfail;
}
qdelete_4:
switch(clause){
case 0: goto qdelete_4_0;
case 1: goto qdelete_4_1;
case 2: goto qdelete_4_2;
default: goto allfail;
}
test_1:
switch(clause){
case 0: goto test_1_0;
case 1: goto test_1_1;
default: goto allfail;
}
check1_1:
switch(clause){
case 0: goto check1_1_0;
case 1: goto check1_1_1;
default: goto allfail;
}
check_2_0:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
Jrelease(th);
Jinc_choice(th);
Jset_back(&&check_2_1,th);
if(Junify_nil(arg1,th) == YES && Junify_int(arg2,Jmakeint(3),th) == YES)
{
goto success;
}
check_2_1:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
Jrelease(th);
Jinc_choice(th);
Jset_back(&&check_2_2,th);
if(Junify(arg1,Jwlistcons(Jmakeint(3),NIL,th),th) == YES && Junify_int(arg2,Jmakeint(2),th) == YES)
{
goto success;
}
check_2_2:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
Jrelease(th);
Jinc_choice(th);
Jset_back(&&check_2_3,th);
if(Junify(arg1,Jwlistcons(Jmakeint(2),Jwlistcons(Jmakeint(3),NIL,th),th),th) == YES && Junify_int(arg2,Jmakeint(1),th) == YES)
{
goto success;
}
check_2_3:
Jpop_back(th);
goto allfail;

queen2_3_0:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
Jrelease(th);
ano_1 = Jmakevariant(th);
Jinc_choice(th);
Jset_back(&&queen2_3_1,th);
if(Junify_nil(arg1,th) == YES && Junify_var(arg2,ano_1,th) == YES && Junify_nil(arg3,th) == YES)
{
goto success;
}
queen2_3_1:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
Jrelease(th);
varL1 = Jmakevariant(th);
varH = Jmakevariant(th);
varT = Jmakevariant(th);
varHistory = Jmakevariant(th);
varQ = Jmakevariant(th);
varM = Jmakevariant(th);
Jinc_choice(th);
Jset_back(&&queen2_3_2,th);
if(Junify_pair(arg1,Jwlistcons(varH,varT,th),th) == YES && Junify_var(arg2,varHistory,th) == YES && Junify_pair(arg3,Jwlistcons(varQ,varM,th),th) == YES)
{
queen2_3_1_0:
base = Jget_ac(th);
arglist = Jwlistcons(varQ,Jwlistcons(varH,Jwlistcons(varT,Jwlistcons(varL1,NIL,th),th),th),th);
pointer = Jcons(varL1,Jcons(varH,Jcons(varT,Jcons(varHistory,Jcons(varQ,Jcons(varM,NIL))))));
Jpush_back(&&queen2_3_2,arglist,np[Jget_scp(CONJ,th)][th],th);
goto queen2_3_1_0join;
queen2_3_1_0back:
base = Jget_ac(th);queen2_3_1_0join:
Jpush_next(&&queen2_3_1_1,base,th);
clause = Jget_choice(th);
goto qdelete_4;
queen2_3_1_1:
base = next_stack1[np[Jget_scp(CONJ,th)][th]+1][th];
varL1 = base - 6;
varH = base - 5;
varT = base - 4;
varHistory = base - 3;
varQ = base - 2;
varM = base - 1;
arglist = Jwlistcons(varHistory,Jwlistcons(varQ,NIL,th),th);
pointer = Jcons(varL1,Jcons(varH,Jcons(varT,Jcons(varHistory,Jcons(varQ,Jcons(varM,NIL))))));
Jpush_back(&&queen2_3_1_0back,arglist,np[Jget_scp(CONJ,th)][th],th);
goto queen2_3_1_1join;
queen2_3_1_1back:
base = Jget_ac(th);queen2_3_1_1join:
Jpush_next(&&queen2_3_1_2,base,th);
clause = Jget_choice(th);
goto check_2;
queen2_3_1_2:
base = next_stack1[np[Jget_scp(CONJ,th)][th]+1][th];
varL1 = base - 6;
varH = base - 5;
varT = base - 4;
varHistory = base - 3;
varQ = base - 2;
varM = base - 1;
arglist = Jwlistcons(varL1,Jwlistcons(Jwlistcons(varQ,varHistory,th),Jwlistcons(varM,NIL,th),th),th);
pointer = Jcons(varL1,Jcons(varH,Jcons(varT,Jcons(varHistory,Jcons(varQ,Jcons(varM,NIL))))));
Jpush_back(&&queen2_3_1_1back,arglist,np[Jget_scp(CONJ,th)][th],th);
goto queen2_3_1_2join;
queen2_3_1_2back:
base = Jget_ac(th);
queen2_3_1_2join:
Jpush_next(&&queen2_3_1_3,base,th);
clause = Jget_choice(th);
goto queen2_3;
queen2_3_1_3:
goto success;
}
queen2_3_2:
Jpop_back(th);
goto allfail;

qdelete_4_0:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
arg4 = Jnth(arglist,4);
Jrelease(th);
varA = Jmakevariant(th);
varL = Jmakevariant(th);
Jinc_choice(th);
Jset_back(&&qdelete_4_1,th);
if(Junify_var(arg1,varA,th) == YES && Junify_var(arg2,varA,th) == YES && Junify_var(arg3,varL,th) == YES && Junify_var(arg4,varL,th) == YES)
{
goto success;
}
qdelete_4_1:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
arg4 = Jnth(arglist,4);
Jrelease(th);
varX = Jmakevariant(th);
varH = Jmakevariant(th);
varT = Jmakevariant(th);
varA = Jmakevariant(th);
varR = Jmakevariant(th);
Jinc_choice(th);
Jset_back(&&qdelete_4_2,th);
if(Junify_var(arg1,varX,th) == YES && Junify_var(arg2,varA,th) == YES && Junify_pair(arg3,Jwlistcons(varH,varT,th),th) == YES && Junify_pair(arg4,Jwlistcons(varA,varR,th),th) == YES)
{
qdelete_4_1_0:
base = Jget_ac(th);
arglist = Jwlistcons(varX,Jwlistcons(varH,Jwlistcons(varT,Jwlistcons(varR,NIL,th),th),th),th);
pointer = Jcons(varX,Jcons(varH,Jcons(varT,Jcons(varA,Jcons(varR,NIL)))));
Jpush_back(&&qdelete_4_2,arglist,np[Jget_scp(CONJ,th)][th],th);
goto qdelete_4_1_0join;
qdelete_4_1_0back:
base = Jget_ac(th);
qdelete_4_1_0join:
Jpush_next(&&qdelete_4_1_1,base,th);
clause = Jget_choice(th);
goto qdelete_4;
qdelete_4_1_1:
goto success;
}
qdelete_4_2:
Jpop_back(th);
goto allfail;

test_1_0:
arg1 = Jcar(arglist);
Jrelease(th);
ano_1 = Jmakevariant(th);
varX = Jmakevariant(th);
Jinc_choice(th);
Jset_back(&&test_1_1,th);
if(Junify_var(arg1,varX,th) == YES)
{
test_1_0_0:
base = Jget_ac(th);
arglist = Jwlistcons(varX,Jwlistcons(Jmakeint(1),Jwlistcons(Jwlistcons(Jmakeint(2),Jwlistcons(Jmakeint(3),NIL,th),th),Jwlistcons(ano_1,NIL,th),th),th),th);
pointer = Jcons(ano_1,Jcons(varX,NIL));
Jpush_back(&&test_1_1,arglist,np[Jget_scp(CONJ,th)][th],th);
goto test_1_0_0join;
test_1_0_0back:
base = Jget_ac(th);test_1_0_0join:
Jpush_next(&&test_1_0_1,base,th);
clause = Jget_choice(th);
goto qdelete_4;
test_1_0_1:
base = next_stack1[np[Jget_scp(CONJ,th)][th]+1][th];
ano_1 = base - 2;
varX = base - 1;
arglist = Jwlistcons(varX,NIL,th);
pointer = Jcons(ano_1,Jcons(varX,NIL));
Jpush_back(&&test_1_0_0back,arglist,np[Jget_scp(CONJ,th)][th],th);
goto test_1_0_1join;
test_1_0_1back:
base = Jget_ac(th);
test_1_0_1join:
Jpush_next(&&test_1_0_2,base,th);
clause = Jget_choice(th);
goto check1_1;
test_1_0_2:
goto success;
}
test_1_1:
Jpop_back(th);
goto allfail;

check1_1_0:
arg1 = Jcar(arglist);
Jrelease(th);
Jinc_choice(th);
Jset_back(&&check1_1_1,th);
if(Junify_int(arg1,Jmakeint(3),th) == YES)
{
goto success;
}
check1_1_1:
Jpop_back(th);
goto allfail;

success:
if(np[Jget_scp(CONJ,th)][th] == 0){
if(Jprove_all(rest,Jget_sp(th),th) == YES) return(YES);
next = back_stack[Jget_scp(RECUR,th)][Jget_scp(CONJ,th)][th];
clause = Jget_choice(th);
arglist = Jget_arg(th);
Jpush_next(&&success,Jget_ac(th),th);
goto *next;
}else{
next = next_stack[np[Jget_scp(CONJ,th)][th]][Jget_scp(CONJ,th)][th];
Jpop_next(th);
clause = Jget_choice(th);
goto *next;}
allfail:
if(Jget_scp(RECUR,th)==0) {Jdiscard_conj(th); return(NO);}
next = back_stack[Jget_scp(RECUR,th)][Jget_scp(CONJ,th)][th];
Jpop_recur(th);
Jpop_next(th);
arglist = Jget_arg(th);
np[Jget_scp(CONJ,th)][th] = Jget_np(th);
goto *next;
builtin_call:
if(Jcallsubr(subr_number,arglist,NIL,th) == YES)
goto success;
else goto allfail;
}
