#include "jump.h"
static int c_rtest(int arglist, int rest, int th);
static int c_choose(int arglist, int rest, int th);
static int user_scbm(int pred, int arity, int clause, int arglist, int rest, int th);
static int c_rtest(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Jsave_arg(arglist,th);
return(user_scbm(0,n,0,arglist,rest,th));
}

static int c_choose(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Jsave_arg(arglist,th);
return(user_scbm(1,n,0,arglist,rest,th));
}

void init_tpredicate(void){
(deftpred)("rtest",c_rtest,2,1);
(deftpred)("choose",c_choose,1,1);
}
void init_declare(void){
int body,th; th=0;
}
static int user_scbm(int pred, int arity, int clause, int arglist, int rest, int th){
void *next;
int arg1,arg2,arg3,arg4,arg5,aeg6,arg7,arg8,arg9,arg10,subr_number,base,ano_1,varX,varXs,varYs;
np[Jget_scp(CONJ,th)][th] = 0; vp[th] = 0;
Jpush_next(&&success,th);
switch(pred){
case 0: goto rtest;
case 1: goto choose;
}
rtest:
switch(arity){
case 2: goto rtest_2;
default: goto allfail;
}
choose:
switch(arity){
case 1: goto choose_1;
default: goto allfail;
}
rtest_2:
switch(clause){
case 0: goto rtest_2_0;
case 1: goto rtest_2_1;
case 2: goto rtest_2_2;
default: goto allfail;
}
choose_1:
switch(clause){
case 0: goto choose_1_0;
case 1: goto choose_1_1;
case 2: goto choose_1_2;
default: goto allfail;
}
rtest_2_0:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
Jrelease(th);
Jinc_choice(th);
Jset_back(&&rtest_2_1,th);
if(Junify_nil(arg1,th) == YES && Junify_nil(arg2,th) == YES)
{
goto success;
}
rtest_2_1:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
Jrelease(th);
ano_1 = Jmakevariant(th);
varXs = Jmakevariant(th);
varX = Jmakevariant(th);
varYs = Jmakevariant(th);
Jinc_choice(th);
Jset_back(&&rtest_2_2,th);
if(Junify_pair(arg1,Jwlistcons(ano_1,varXs,th),th) == YES && Junify_pair(arg2,Jwlistcons(varX,varYs,th),th) == YES)
{
rtest_2_1_0:
arglist = Jwlistcons(varX,NIL,th);
Jpush_back(&&rtest_2_2,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
rtest_2_1_0back:
Jpush_next(&&rtest_2_1_1,th);
clause = Jget_choice(th);
goto choose_1;
rtest_2_1_1:
base = next_stack1[np[Jget_scp(CONJ,th)][th]+1][th];
ano_1 = base - 4;
varXs = base - 3;
varX = base - 2;
varYs = base - 1;
arglist = Jwlistcons(varXs,Jwlistcons(varYs,NIL,th),th);
Jpush_back(&&rtest_2_1_0back,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
rtest_2_1_1back:
Jpush_next(&&rtest_2_1_2,th);
clause = Jget_choice(th);
goto rtest_2;
rtest_2_1_2:
goto success;
}
rtest_2_2:
Jpop_back(th);
goto allfail;

choose_1_0:
arg1 = Jcar(arglist);
Jrelease(th);
Jinc_choice(th);
Jset_back(&&choose_1_1,th);
if(Junify_atom(arg1,Jmakeconst("a"),th) == YES)
{
goto success;
}
choose_1_1:
arg1 = Jcar(arglist);
Jrelease(th);
Jinc_choice(th);
Jset_back(&&choose_1_2,th);
if(Junify_atom(arg1,Jmakeconst("b"),th) == YES)
{
goto success;
}
choose_1_2:
Jpop_back(th);
goto allfail;

success:
if(np[Jget_scp(CONJ,th)][th] == 0){
if(Jprove_all(rest,Jget_sp(th),th) == YES) return(YES);
next = back_stack[Jget_scp(RECUR,th)][Jget_scp(CONJ,th)][th];
clause = Jget_choice(th);
arglist = Jget_arg(th);
Jpush_next(&&success,th);
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
