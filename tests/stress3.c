#include "jump.h"
static int c_color(int arglist, int rest, int th);
static int c_first_color(int arglist, int rest, int th);
static int c_num(int arglist, int rest, int th);
static int c_test_cut_fail(int arglist, int rest, int th);
static int c_test_no_cut(int arglist, int rest, int th);
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

static int c_num(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Jsave_arg(arglist,th);
return(user_scbm(2,n,0,arglist,rest,th));
}

static int c_test_cut_fail(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Jsave_arg(arglist,th);
return(user_scbm(3,n,0,arglist,rest,th));
}

static int c_test_no_cut(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Jsave_arg(arglist,th);
return(user_scbm(4,n,0,arglist,rest,th));
}

void init_tpredicate(void){
(deftpred)("color",c_color,1,1);
(deftpred)("first_color",c_first_color,1,1);
(deftpred)("num",c_num,1,1);
(deftpred)("test_cut_fail",c_test_cut_fail,1,1);
(deftpred)("test_no_cut",c_test_no_cut,1,1);
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
case 2: goto num;
case 3: goto test_cut_fail;
case 4: goto test_no_cut;
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
num:
switch(arity){
case 1: goto num_1;
default: goto allfail;
}
test_cut_fail:
switch(arity){
case 1: goto test_cut_fail_1;
default: goto allfail;
}
test_no_cut:
switch(arity){
case 1: goto test_no_cut_1;
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
num_1:
switch(clause){
case 0: goto num_1_0;
case 1: goto num_1_1;
case 2: goto num_1_2;
default: goto allfail;
}
test_cut_fail_1:
switch(clause){
case 0: goto test_cut_fail_1_0;
default: goto allfail;
}
test_no_cut_1:
switch(clause){
case 0: goto test_no_cut_1_0;
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

num_1_0:
arg1 = Jcar(arglist);
Jrelease(th);
Jinc_choice(th);
Jset_back(&&num_1_1,th);
if(Junify_int(arg1,Jmakeint(1),th) == YES)
{
goto success;
}
num_1_1:
arg1 = Jcar(arglist);
Jrelease(th);
Jinc_choice(th);
Jset_back(&&num_1_2,th);
if(Junify_int(arg1,Jmakeint(2),th) == YES)
{
goto success;
}
num_1_2:
arg1 = Jcar(arglist);
Jrelease(th);
Jinc_choice(th);
Jset_back(&&num_1_3,th);
if(Junify_int(arg1,Jmakeint(3),th) == YES)
{
goto success;
}
num_1_3:
Jpop_back(th);
goto allfail;

test_cut_fail_1_0:
arg1 = Jcar(arglist);
Jrelease(th);
varX = Jmakevariant(th);
Jinc_choice(th);
Jset_back(&&test_cut_fail_1_1,th);
if(Junify_var(arg1,varX,th) == YES)
{
test_cut_fail_1_0_0:
arglist = Jwlistcons(varX,NIL,th);
Jpush_var(varX,th);
Jpush_back(&&test_cut_fail_1_1,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
test_cut_fail_1_0_0back:
Jpush_next(&&test_cut_fail_1_0_1,th);
clause = Jget_choice(th);
goto num_1;
test_cut_fail_1_0_1:
if (Jcall_det(Jmakesys("="),Jwlistcons(varX,Jwlistcons(Jmakeint(2),NIL,th),th),th) == YES)
goto success;
else goto allfail;
}
test_cut_fail_1_1:
Jpop_back(th);
goto allfail;

test_no_cut_1_0:
arg1 = Jcar(arglist);
Jrelease(th);
varX = Jmakevariant(th);
Jinc_choice(th);
Jset_back(&&test_no_cut_1_1,th);
if(Junify_var(arg1,varX,th) == YES)
{
test_no_cut_1_0_0:
arglist = Jwlistcons(varX,NIL,th);
Jpush_var(varX,th);
Jpush_back(&&test_no_cut_1_1,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
test_no_cut_1_0_0back:
Jpush_next(&&test_no_cut_1_0_1,th);
clause = Jget_choice(th);
goto num_1;
test_no_cut_1_0_1:
varX = Jpop_var(th);
if (Jcall_det(Jmakesys("="),Jwlistcons(varX,Jwlistcons(Jmakeint(2),NIL,th),th),th) == YES)
goto success;
else goto allfail;
}
test_no_cut_1_1:
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
