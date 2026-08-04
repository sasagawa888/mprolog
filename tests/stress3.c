#include "jump.h"
static int c_color(int arglist, int rest, int th);
static int c_first_color(int arglist, int rest, int th);
static int user_scbm(int pred, int arity, int clause, int arglist, int rest, int th);
static int c_color(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Jsave_arg(arglist,th);
return(user_scbm(0,n,0,arglist,rest,th));
}

static int c_first_color(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Jsave_arg(arglist,th);
return(user_scbm(1,n,0,arglist,rest,th));
}

void init_tpredicate(void){
(deftpred)("color",c_color,1,1);
(deftpred)("first_color",c_first_color,1,1);
}
void init_declare(void){
int body,th; th=0;
}
static int user_scbm(int pred, int arity, int clause, int arglist, int rest, int th){
void *next;
int arg1,arg2,arg3,arg4,arg5,aeg6,arg7,arg8,arg9,arg10,varX;
np[Jget_scp(CONJ,th)][th] = 0; vp[th] = 0;
Jpush_next(&&success,th);
switch(pred){
case 0: goto color;
case 1: goto first_color;
}
color:
switch(arity){
case 1: goto color_1;
default: goto allfail;
}
first_color:
switch(arity){
case 1: goto first_color_1;
default: goto allfail;
}
color_1:
switch(clause){
case 0: goto color_1_0;
case 1: goto color_1_1;
case 2: goto color_1_2;
default: goto allfail;
}
first_color_1:
switch(clause){
case 0: goto first_color_1_0;
default: goto allfail;
}
color_1_0:
arg1 = Jcar(arglist);
Jrelease(th);
Jinc_choice(th);
Jset_back(&&color_1_1,th);
if(Junify_atom(arg1,Jmakeconst("red"),th) == YES)
{
goto success;
}
color_1_1:
arg1 = Jcar(arglist);
Jrelease(th);
Jinc_choice(th);
Jset_back(&&color_1_2,th);
if(Junify_atom(arg1,Jmakeconst("green"),th) == YES)
{
goto success;
}
color_1_2:
arg1 = Jcar(arglist);
Jrelease(th);
Jinc_choice(th);
Jset_back(&&color_1_3,th);
if(Junify_atom(arg1,Jmakeconst("blue"),th) == YES)
{
goto success;
}
color_1_3:
Jpop_back(th);
goto allfail;

first_color_1_0:
arg1 = Jcar(arglist);
Jrelease(th);
varX = Jmakevariant(th);
Jinc_choice(th);
Jset_back(&&first_color_1_1,th);
if(Junify_var(arg1,varX,th) == YES)
{
first_color_1_0_0:
arglist = Jwlistcons(varX,NIL,th);
Jpush_var(varX,th);
Jpush_back(&&first_color_1_1,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
first_color_1_0_0back:
Jpush_next(&&first_color_1_0_1,th);
clause = Jget_choice(th);
goto color_1;
first_color_1_0_1:
Jset_back(&&allfail,th);goto success;
}
first_color_1_1:
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
