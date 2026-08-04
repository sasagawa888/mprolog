#include "jump.h"
static int c_plus(int arglist, int rest, int th);
static int c_times(int arglist, int rest, int th);
static int user_scbm(int pred, int arity, int clause, int arglist, int rest, int th);
static int c_plus(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Jsave_arg(arglist,th);
return(user_scbm(0,n,0,arglist,rest,th));
}

static int c_times(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Jsave_arg(arglist,th);
return(user_scbm(1,n,0,arglist,rest,th));
}

void init_tpredicate(void){
(deftpred)("plus",c_plus,3,1);
(deftpred)("times",c_times,3,1);
}
void init_declare(void){
int body,th; th=0;
}
static int user_scbm(int pred, int arity, int clause, int arglist, int rest, int th){
void *next;
int arg1,arg2,arg3,arg4,arg5,aeg6,arg7,arg8,arg9,arg10,ano_1,varX,varY,varZ,varZ1;
np[Jget_scp(CONJ,th)][th] = 0; vp[th] = 0;
Jpush_next(&&success,th);
switch(pred){
case 0: goto color;
case 1: goto plus;
case 2: goto times;
}
color:
switch(arity){
case 1: goto color_1;
default: goto allfail;
}
plus:
switch(arity){
case 3: goto plus_3;
default: goto allfail;
}
times:
switch(arity){
case 3: goto times_3;
default: goto allfail;
}
color_1:
switch(clause){
default: goto allfail;
}
plus_3:
switch(clause){
case 0: goto plus_3_0;
case 1: goto plus_3_1;
default: goto allfail;
}
times_3:
switch(clause){
case 0: goto times_3_0;
case 1: goto times_3_1;
default: goto allfail;
}
color_1_0:
Jpop_back(th);
goto allfail;

plus_3_0:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
Jrelease(th);
varY = Jmakevariant(th);
Jinc_choice(th);
Jset_back(&&plus_3_1,th);
if(Junify_int(arg1,Jmakeint(0),th) == YES && Junify_var(arg2,varY,th) == YES && Junify_var(arg3,varY,th) == YES)
{
goto success;
}
plus_3_1:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
Jrelease(th);
varX = Jmakevariant(th);
varY = Jmakevariant(th);
varZ = Jmakevariant(th);
Jinc_choice(th);
Jset_back(&&plus_3_2,th);
if(Junify(arg1,Jwcons(Jmakepred("s"),Jwcons(varX,NIL,th),th),th) == YES && Junify_var(arg2,varY,th) == YES && Junify(arg3,Jwcons(Jmakepred("s"),Jwcons(varZ,NIL,th),th),th) == YES)
{
plus_3_1_0:
arglist = Jwlistcons(varX,Jwlistcons(varY,Jwlistcons(varZ,NIL,th),th),th);
Jpush_back(&&plus_3_2,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
plus_3_1_0back:
Jpush_next(&&plus_3_1_1,th);
clause = Jget_choice(th);
goto plus_3;
plus_3_1_1:
goto success;
}
plus_3_2:
Jpop_back(th);
goto allfail;

times_3_0:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
Jrelease(th);
ano_1 = Jmakevariant(th);
Jinc_choice(th);
Jset_back(&&times_3_1,th);
if(Junify_int(arg1,Jmakeint(0),th) == YES && Junify_var(arg2,ano_1,th) == YES && Junify_int(arg3,Jmakeint(0),th) == YES)
{
goto success;
}
times_3_1:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
Jrelease(th);
varZ1 = Jmakevariant(th);
varX = Jmakevariant(th);
varY = Jmakevariant(th);
varZ = Jmakevariant(th);
Jinc_choice(th);
Jset_back(&&times_3_2,th);
if(Junify(arg1,Jwcons(Jmakepred("s"),Jwcons(varX,NIL,th),th),th) == YES && Junify_var(arg2,varY,th) == YES && Junify_var(arg3,varZ,th) == YES)
{
times_3_1_0:
arglist = Jwlistcons(varX,Jwlistcons(varY,Jwlistcons(varZ1,NIL,th),th),th);
Jpush_var(varZ1,th);
Jpush_var(varX,th);
Jpush_var(varY,th);
Jpush_var(varZ,th);
Jpush_back(&&times_3_2,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
times_3_1_0back:
Jpush_next(&&times_3_1_1,th);
clause = Jget_choice(th);
goto times_3;
times_3_1_1:
varZ = Jpop_var(th);
varY = Jpop_var(th);
varX = Jpop_var(th);
varZ1 = Jpop_var(th);
arglist = Jwlistcons(varZ1,Jwlistcons(varY,Jwlistcons(varZ,NIL,th),th),th);
Jpush_back(&&times_3_1_0back,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
times_3_1_1back:
Jpush_next(&&times_3_1_2,th);
clause = Jget_choice(th);
goto plus_3;
times_3_1_2:
goto success;
}
times_3_2:
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
clause = Jget_choice(th);
arglist = Jget_arg(th);
vp[th] = Jget_vp(th);
np[Jget_scp(CONJ,th)][th] = Jget_np(th);
goto *next;
}
