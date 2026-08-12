#include "jump.h"
static int c_test16(int arglist, int rest, int th);
static int c_test(int arglist, int rest, int th);
static int c_test1(int arglist, int rest, int th);
static int c_queen(int arglist, int rest, int th);
static int c_queen2(int arglist, int rest, int th);
static int c_qdelete(int arglist, int rest, int th);
static int c_nodiag(int arglist, int rest, int th);
static int user_scbm(int pred, int arity, int clause, int arglist, int rest, int th);
static int c_test16(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Jsave_arg(arglist,th);
return(user_scbm(0,n,0,arglist,rest,th));
}

static int c_test(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Jsave_arg(arglist,th);
return(user_scbm(1,n,0,arglist,rest,th));
}

static int c_test1(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Jsave_arg(arglist,th);
return(user_scbm(2,n,0,arglist,rest,th));
}

static int c_queen(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Jsave_arg(arglist,th);
return(user_scbm(3,n,0,arglist,rest,th));
}

static int c_queen2(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Jsave_arg(arglist,th);
return(user_scbm(4,n,0,arglist,rest,th));
}

static int c_qdelete(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Jsave_arg(arglist,th);
return(user_scbm(5,n,0,arglist,rest,th));
}

static int c_nodiag(int arglist, int rest, int th){
int arg1,arg2,arg3,varD1,varN,varL,varB,varD,ano_2,ano_1,n,body,save1,save2,save3,goal,cont,clause,res;
save1 = Jget_wp(th);
save2 = Jget_sp(th);
save3 = Jget_ac(th);
Jinc_proof(th);
n = Jarity_count(arglist);
if(n == 3){
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
loop3:
ano_2 = Jmakevariant(th);
ano_1 = Jmakevariant(th);
if(Junify_nil(arg1,th) == YES && Junify_var(arg2,ano_2,th) == YES && Junify_var(arg3,ano_1,th) == YES)
{Junbind(save2,th);
Jset_ac(save3,th);
return(YES);}
varD1 = Jmakevariant(th);
varN = Jmakevariant(th);
varL = Jmakevariant(th);
varB = Jmakevariant(th);
varD = Jmakevariant(th);
if(Junify_pair(arg1,Jwlistcons(varN,varL,th),th) == YES && Junify_var(arg2,varB,th) == YES && Junify_var(arg3,varD,th) == YES)
if(Jnot_numeqp(Jderef(varD,th),Jminus(Jderef(varN,th),Jderef(varB,th),th)))
if(Jnot_numeqp(Jderef(varD,th),Jminus(Jderef(varB,th),Jderef(varN,th),th)))
if(Junify(varD1,Jplus(Jderef(varD,th),Jmakeint(1),th),th)==YES)
{
arg1 = Jcopy_work(Jderef(varL,th),th);
arg2 = Jcopy_work(Jderef(varB,th),th);
arg3 = Jcopy_work(Jderef(varD1,th),th);
Junbind(save2,th);
Jset_ac(save3,th);
goto loop3;
}
else return(NO);}
}
void init_tpredicate(void){
(deftpred)("test16",c_test16,0,1);
(deftpred)("test",c_test,0,1);
(deftpred)("test1",c_test1,0,1);
(deftpred)("queen",c_queen,2,1);
(deftpred)("queen2",c_queen2,3,1);
(deftpred)("qdelete",c_qdelete,4,1);
(deftpred)("nodiag",c_nodiag,3,3);
}
void init_declare(void){
int body,th; th=0;
}
static int user_scbm(int pred, int arity, int clause, int arglist, int rest, int th){
void *next;
int arg1,arg2,arg3,arg4,arg5,aeg6,arg7,arg8,arg9,arg10,subr_number,base,ano_1,varA,varData,varH,varHistory,varL,varL1,varM,varOut,varQ,varR,varT,varX;
np[Jget_scp(CONJ,th)][th] = 0; vp[th] = 0;
Jpush_next(&&success,Jget_ac(th),th);
switch(pred){
case 0: goto test16;
case 1: goto test;
case 2: goto test1;
case 3: goto queen;
case 4: goto queen2;
case 5: goto qdelete;
}
test16:
switch(arity){
case 0: goto test16_0;
default: goto allfail;
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
queen:
switch(arity){
case 2: goto queen_2;
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
test16_0:
switch(clause){
case 0: goto test16_0_0;
case 1: goto test16_0_1;
default: goto allfail;
}
test_0:
switch(clause){
case 0: goto test_0_0;
case 1: goto test_0_1;
default: goto allfail;
}
test1_0:
switch(clause){
case 0: goto test1_0_0;
case 1: goto test1_0_1;
default: goto allfail;
}
queen_2:
switch(clause){
case 0: goto queen_2_0;
case 1: goto queen_2_1;
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
test16_0_0:
Jrelease(th);
varX = Jmakevariant(th);
Jinc_choice(th);
Jset_back(&&test16_0_1,th);
{
test16_0_0_0:
arglist = Jwlistcons(Jmakeint(1),Jwlistcons(Jmakeint(16),Jwlistcons(varX,NIL,th),th),th);
Jpush_next(&&test16_0_0_1,Jget_ac(th),th);
subr_number = 1244;
goto builtin_call;
test16_0_0_1:
base = next_stack1[np[Jget_scp(CONJ,th)][th]+1][th];
varX = base - 1;
arglist = NIL;
goto test16_0_0_1join;
test16_0_0_1back:
base = Jget_ac(th);
varX = base - 1;
arglist = NIL;
test16_0_0_1join:
Jpush_next(&&test16_0_0_2,next_stack1[np[Jget_scp(CONJ,th)][th]+1][th],th);
clause = Jget_choice(th);
goto test1_0;
test16_0_0_2:
Jpush_back(&&test16_0_0_1back,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
goto allfail;
}
test16_0_1:
Jpop_back(th);
goto allfail;

test_0_0:
Jrelease(th);
varX = Jmakevariant(th);
Jinc_choice(th);
Jset_back(&&test_0_1,th);
{
test_0_0_0:
arglist = Jwlistcons(Jwlistcons(Jmakeint(1),Jwlistcons(Jmakeint(2),Jwlistcons(Jmakeint(3),Jwlistcons(Jmakeint(4),Jwlistcons(Jmakeint(5),Jwlistcons(Jmakeint(6),Jwlistcons(Jmakeint(7),Jwlistcons(Jmakeint(8),Jwlistcons(Jmakeint(9),NIL,th),th),th),th),th),th),th),th),th),Jwlistcons(varX,NIL,th),th);
Jpush_back(&&test_0_1,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
goto test_0_0_0join;
test_0_0_0back:
base = Jget_ac(th);
varX = base - 1;
arglist = Jwlistcons(Jwlistcons(Jmakeint(1),Jwlistcons(Jmakeint(2),Jwlistcons(Jmakeint(3),Jwlistcons(Jmakeint(4),Jwlistcons(Jmakeint(5),Jwlistcons(Jmakeint(6),Jwlistcons(Jmakeint(7),Jwlistcons(Jmakeint(8),Jwlistcons(Jmakeint(9),NIL,th),th),th),th),th),th),th),th),th),Jwlistcons(varX,NIL,th),th);
test_0_0_0join:
Jpush_next(&&test_0_0_1,Jget_ac(th),th);
clause = Jget_choice(th);
goto queen_2;
test_0_0_1:
base = next_stack1[np[Jget_scp(CONJ,th)][th]+1][th];
varX = base - 1;
arglist = Jwlistcons(varX,NIL,th);
Jpush_back(&&test_0_0_0back,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
Jpush_next(&&test_0_0_2,next_stack1[np[Jget_scp(CONJ,th)][th]+1][th],th);
subr_number = 1204;
goto builtin_call;
test_0_0_2:
base = next_stack1[np[Jget_scp(CONJ,th)][th]+1][th];
varX = base - 1;
arglist = NIL;
Jpush_next(&&test_0_0_3,next_stack1[np[Jget_scp(CONJ,th)][th]+1][th],th);
subr_number = 808;
goto builtin_call;
test_0_0_3:
goto allfail;
}
test_0_1:
Jpop_back(th);
goto allfail;

test1_0_0:
Jrelease(th);
varX = Jmakevariant(th);
Jinc_choice(th);
Jset_back(&&test1_0_1,th);
{
test1_0_0_0:
arglist = Jwlistcons(Jwlistcons(Jmakeint(1),Jwlistcons(Jmakeint(2),Jwlistcons(Jmakeint(3),Jwlistcons(Jmakeint(4),Jwlistcons(Jmakeint(5),Jwlistcons(Jmakeint(6),Jwlistcons(Jmakeint(7),Jwlistcons(Jmakeint(8),Jwlistcons(Jmakeint(9),NIL,th),th),th),th),th),th),th),th),th),Jwlistcons(varX,NIL,th),th);
Jpush_back(&&test1_0_1,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
goto test1_0_0_0join;
test1_0_0_0back:
base = Jget_ac(th);
varX = base - 1;
arglist = Jwlistcons(Jwlistcons(Jmakeint(1),Jwlistcons(Jmakeint(2),Jwlistcons(Jmakeint(3),Jwlistcons(Jmakeint(4),Jwlistcons(Jmakeint(5),Jwlistcons(Jmakeint(6),Jwlistcons(Jmakeint(7),Jwlistcons(Jmakeint(8),Jwlistcons(Jmakeint(9),NIL,th),th),th),th),th),th),th),th),th),Jwlistcons(varX,NIL,th),th);
test1_0_0_0join:
Jpush_next(&&test1_0_0_1,Jget_ac(th),th);
clause = Jget_choice(th);
goto queen_2;
test1_0_0_1:
Jpush_back(&&test1_0_0_0back,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
goto allfail;
}
test1_0_1:
Jpop_back(th);
goto allfail;

queen_2_0:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
Jrelease(th);
varData = Jmakevariant(th);
varOut = Jmakevariant(th);
Jinc_choice(th);
Jset_back(&&queen_2_1,th);
if(Junify_var(arg1,varData,th) == YES && Junify_var(arg2,varOut,th) == YES)
{
queen_2_0_0:
arglist = Jwlistcons(varData,Jwlistcons(NIL,Jwlistcons(varOut,NIL,th),th),th);
Jpush_back(&&queen_2_1,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
goto queen_2_0_0join;
queen_2_0_0back:
base = Jget_ac(th);
varData = base - 2;
varOut = base - 1;
arglist = Jwlistcons(varData,Jwlistcons(NIL,Jwlistcons(varOut,NIL,th),th),th);
queen_2_0_0join:
Jpush_next(&&queen_2_0_1,Jget_ac(th),th);
clause = Jget_choice(th);
goto queen2_3;
queen_2_0_1:
goto success;
}
queen_2_1:
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
arglist = Jwlistcons(varQ,Jwlistcons(varH,Jwlistcons(varT,Jwlistcons(varL1,NIL,th),th),th),th);
Jpush_back(&&queen2_3_2,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
goto queen2_3_1_0join;
queen2_3_1_0back:
base = Jget_ac(th);
varL1 = base - 6;
varH = base - 5;
varT = base - 4;
varHistory = base - 3;
varQ = base - 2;
varM = base - 1;
arglist = Jwlistcons(varQ,Jwlistcons(varH,Jwlistcons(varT,Jwlistcons(varL1,NIL,th),th),th),th);
queen2_3_1_0join:
Jpush_next(&&queen2_3_1_1,Jget_ac(th),th);
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
arglist = Jwlistcons(Jwcons(Jmakepred("dt"),Jwcons(varQ,Jwcons(varH,Jwcons(varT,Jwcons(varL1,NIL,th),th),th),th),th),NIL,th);
Jpush_back(&&queen2_3_1_0back,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
Jpush_next(&&queen2_3_1_2,next_stack1[np[Jget_scp(CONJ,th)][th]+1][th],th);
subr_number = 1204;
goto builtin_call;
queen2_3_1_2:
base = next_stack1[np[Jget_scp(CONJ,th)][th]+1][th];
varL1 = base - 6;
varH = base - 5;
varT = base - 4;
varHistory = base - 3;
varQ = base - 2;
varM = base - 1;
arglist = Jwlistcons(varHistory,Jwlistcons(varQ,Jwlistcons(Jmakeint(1),NIL,th),th),th);
Jpush_next(&&queen2_3_1_3,next_stack1[np[Jget_scp(CONJ,th)][th]+1][th],th);
subr_number = Jmakecomp("nodiag");
goto builtin_call;
queen2_3_1_3:
base = next_stack1[np[Jget_scp(CONJ,th)][th]+1][th];
varL1 = base - 6;
varH = base - 5;
varT = base - 4;
varHistory = base - 3;
varQ = base - 2;
varM = base - 1;
arglist = Jwlistcons(varL1,Jwlistcons(Jwlistcons(varQ,varHistory,th),Jwlistcons(varM,NIL,th),th),th);
goto queen2_3_1_3join;
queen2_3_1_3back:
base = Jget_ac(th);
varL1 = base - 6;
varH = base - 5;
varT = base - 4;
varHistory = base - 3;
varQ = base - 2;
varM = base - 1;
arglist = Jwlistcons(varL1,Jwlistcons(Jwlistcons(varQ,varHistory,th),Jwlistcons(varM,NIL,th),th),th);
queen2_3_1_3join:
Jpush_next(&&queen2_3_1_4,next_stack1[np[Jget_scp(CONJ,th)][th]+1][th],th);
clause = Jget_choice(th);
goto queen2_3;
queen2_3_1_4:
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
arglist = Jwlistcons(varX,Jwlistcons(varH,Jwlistcons(varT,Jwlistcons(varR,NIL,th),th),th),th);
Jpush_back(&&qdelete_4_2,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
goto qdelete_4_1_0join;
qdelete_4_1_0back:
base = Jget_ac(th);
varX = base - 5;
varH = base - 4;
varT = base - 3;
varA = base - 2;
varR = base - 1;
arglist = Jwlistcons(varX,Jwlistcons(varH,Jwlistcons(varT,Jwlistcons(varR,NIL,th),th),th),th);
qdelete_4_1_0join:
Jpush_next(&&qdelete_4_1_1,Jget_ac(th),th);
clause = Jget_choice(th);
goto qdelete_4;
qdelete_4_1_1:
goto success;
}
qdelete_4_2:
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
vp[th] = Jget_vp(th);
np[Jget_scp(CONJ,th)][th] = Jget_np(th);
goto *next;
builtin_call:
if(Jcallsubr(subr_number,arglist,NIL,th) == YES)
goto success;
else goto allfail;
}
