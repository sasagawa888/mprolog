#include "jump.h"
static int c_member1(int arglist, int rest, int th);
static int c_select1(int arglist, int rest, int th);
static int c_perm1(int arglist, int rest, int th);
static int c_ordered(int arglist, int rest, int th);
static int c_sort_test(int arglist, int rest, int th);
static int c_p1(int arglist, int rest, int th);
static int c_rtest(int arglist, int rest, int th);
static int c_choose(int arglist, int rest, int th);
static int c_permtest(int arglist, int rest, int th);
static int user_scbm(int pred, int arity, int clause, int arglist, int rest, int th);
static int c_member1(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Jsave_arg(arglist,th);
return(user_scbm(0,n,0,arglist,rest,th));
}

static int c_select1(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Jsave_arg(arglist,th);
return(user_scbm(1,n,0,arglist,rest,th));
}

static int c_perm1(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Jsave_arg(arglist,th);
return(user_scbm(2,n,0,arglist,rest,th));
}

static int c_ordered(int arglist, int rest, int th){
int arg1,varX,varY,varXs,ano_1,n,body,save1,save2,save3,goal,cont,clause,res;
save1 = Jget_wp(th);
save2 = Jget_sp(th);
save3 = Jget_ac(th);
Jinc_proof(th);
n = Jarity_count(arglist);
if(n == 1){
arg1 = Jcar(arglist);
loop1:
if(Junify_nil(arg1,th) == YES)
return(YES);
ano_1 = Jmakevariant(th);
if(Junify(arg1,Jwlistcons(ano_1,NIL,th),th) == YES)
return(YES);
varX = Jmakevariant(th);
varY = Jmakevariant(th);
varXs = Jmakevariant(th);
if(Junify(arg1,Jwlistcons(varX,Jwlistcons(varY,varXs,th),th),th) == YES)
if(Jeqsmallerp(Jderef(varX,th),Jderef(varY,th)))
{
arg1 = Jcopy_work(Jderef(Jwlistcons(varY,varXs,th),th),th);
Junbind(save2,th);
Jset_ac(save3,th);
goto loop1;
}
else return(NO);}
}
static int c_sort_test(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Jsave_arg(arglist,th);
return(user_scbm(3,n,0,arglist,rest,th));
}

static int c_p1(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Jsave_arg(arglist,th);
return(user_scbm(4,n,0,arglist,rest,th));
}

static int c_rtest(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Jsave_arg(arglist,th);
return(user_scbm(5,n,0,arglist,rest,th));
}

static int c_choose(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Jsave_arg(arglist,th);
return(user_scbm(6,n,0,arglist,rest,th));
}

static int c_permtest(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Jsave_arg(arglist,th);
return(user_scbm(7,n,0,arglist,rest,th));
}

void init_tpredicate(void){
(deftpred)("member1",c_member1,2,1);
(deftpred)("select1",c_select1,3,1);
(deftpred)("perm1",c_perm1,2,1);
(deftpred)("ordered",c_ordered,1,3);
(deftpred)("sort_test",c_sort_test,2,1);
(deftpred)("p1",c_p1,2,1);
(deftpred)("rtest",c_rtest,2,1);
(deftpred)("choose",c_choose,1,1);
(deftpred)("permtest",c_permtest,0,1);
}
void init_declare(void){
int body,th; th=0;
}
static int user_scbm(int pred, int arity, int clause, int arglist, int rest, int th){
void *next;
int arg1,arg2,arg3,arg4,arg5,aeg6,arg7,arg8,arg9,arg10,subr_number,ano_1,varX,varXs,varY,varYs,varZ,varZs;
np[Jget_scp(CONJ,th)][th] = 0; vp[th] = 0; mode[th] = 0;
Jpush_next(&&success,th);
switch(pred){
case 0: goto member1;
case 1: goto select1;
case 2: goto perm1;
case 3: goto sort_test;
case 4: goto p1;
case 5: goto rtest;
case 6: goto choose;
case 7: goto permtest;
}
member1:
switch(arity){
case 2: goto member1_2;
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
sort_test:
switch(arity){
case 2: goto sort_test_2;
default: goto allfail;
}
p1:
switch(arity){
case 2: goto p1_2;
default: goto allfail;
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
permtest:
switch(arity){
case 0: goto permtest_0;
default: goto allfail;
}
member1_2:
switch(clause){
case 0: goto member1_2_0;
case 1: goto member1_2_1;
case 2: goto member1_2_2;
default: goto allfail;
}
select1_3:
switch(clause){
case 0: goto select1_3_0;
case 1: goto select1_3_1;
case 2: goto select1_3_2;
default: goto allfail;
}
perm1_2:
switch(clause){
case 0: goto perm1_2_0;
case 1: goto perm1_2_1;
case 2: goto perm1_2_2;
default: goto allfail;
}
sort_test_2:
switch(clause){
case 0: goto sort_test_2_0;
case 1: goto sort_test_2_1;
default: goto allfail;
}
p1_2:
switch(clause){
case 0: goto p1_2_0;
case 1: goto p1_2_1;
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
permtest_0:
switch(clause){
case 0: goto permtest_0_0;
case 1: goto permtest_0_1;
default: goto allfail;
}
member1_2_0:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
Jrelease(th);
varX = Jmakevariant(th);
ano_1 = Jmakevariant(th);
Jinc_choice(th);
Jset_back(&&member1_2_1,th);
if(Junify_var(arg1,varX,th) == YES && Junify_pair(arg2,Jwlistcons(varX,ano_1,th),th) == YES)
{
goto success;
}
member1_2_1:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
Jrelease(th);
varX = Jmakevariant(th);
ano_1 = Jmakevariant(th);
varXs = Jmakevariant(th);
Jinc_choice(th);
Jset_back(&&member1_2_2,th);
if(Junify_var(arg1,varX,th) == YES && Junify_pair(arg2,Jwlistcons(ano_1,varXs,th),th) == YES)
{
member1_2_1_0:
arglist = Jwlistcons(varX,Jwlistcons(varXs,NIL,th),th);
Jpush_back(&&member1_2_2,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
member1_2_1_0back:
if(mode[th] == 1){
varXs = Jpop_var(th);
ano_1 = Jpop_var(th);
varX = Jpop_var(th);
Jpush_var(varX,th);
Jpush_var(ano_1,th);
Jpush_var(varXs,th);
arglist = Jwlistcons(varX,Jwlistcons(varXs,NIL,th),th);
mode[th] = 0;}
Jpush_next(&&member1_2_1_1,th);
clause = Jget_choice(th);
goto member1_2;
member1_2_1_1:
goto success;
}
member1_2_2:
Jpop_back(th);
goto allfail;

select1_3_0:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
Jrelease(th);
varX = Jmakevariant(th);
varXs = Jmakevariant(th);
Jinc_choice(th);
Jset_back(&&select1_3_1,th);
if(Junify_var(arg1,varX,th) == YES && Junify_pair(arg2,Jwlistcons(varX,varXs,th),th) == YES && Junify_var(arg3,varXs,th) == YES)
{
goto success;
}
select1_3_1:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
Jrelease(th);
varX = Jmakevariant(th);
varYs = Jmakevariant(th);
varY = Jmakevariant(th);
varZs = Jmakevariant(th);
Jinc_choice(th);
Jset_back(&&select1_3_2,th);
if(Junify_var(arg1,varX,th) == YES && Junify_pair(arg2,Jwlistcons(varY,varYs,th),th) == YES && Junify_pair(arg3,Jwlistcons(varY,varZs,th),th) == YES)
{
select1_3_1_0:
arglist = Jwlistcons(varX,Jwlistcons(varYs,Jwlistcons(varZs,NIL,th),th),th);
Jpush_back(&&select1_3_2,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
select1_3_1_0back:
if(mode[th] == 1){
varZs = Jpop_var(th);
varY = Jpop_var(th);
varYs = Jpop_var(th);
varX = Jpop_var(th);
Jpush_var(varX,th);
Jpush_var(varYs,th);
Jpush_var(varY,th);
Jpush_var(varZs,th);
arglist = Jwlistcons(varX,Jwlistcons(varYs,Jwlistcons(varZs,NIL,th),th),th);
mode[th] = 0;}
Jpush_next(&&select1_3_1_1,th);
clause = Jget_choice(th);
goto select1_3;
select1_3_1_1:
goto success;
}
select1_3_2:
Jpop_back(th);
goto allfail;

perm1_2_0:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
Jrelease(th);
Jinc_choice(th);
Jset_back(&&perm1_2_1,th);
if(Junify_nil(arg1,th) == YES && Junify_nil(arg2,th) == YES)
{
goto success;
}
perm1_2_1:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
Jrelease(th);
varZs = Jmakevariant(th);
varXs = Jmakevariant(th);
varX = Jmakevariant(th);
varYs = Jmakevariant(th);
Jinc_choice(th);
Jset_back(&&perm1_2_2,th);
if(Junify_var(arg1,varXs,th) == YES && Junify_pair(arg2,Jwlistcons(varX,varYs,th),th) == YES)
{
perm1_2_1_0:
arglist = Jwlistcons(varX,Jwlistcons(varXs,Jwlistcons(varZs,NIL,th),th),th);
Jpush_var(varZs,th);
Jpush_var(varXs,th);
Jpush_var(varX,th);
Jpush_var(varYs,th);
Jpush_back(&&perm1_2_2,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
perm1_2_1_0back:
if(mode[th] == 1){
varYs = Jpop_var(th);
varX = Jpop_var(th);
varXs = Jpop_var(th);
varZs = Jpop_var(th);
Jpush_var(varZs,th);
Jpush_var(varXs,th);
Jpush_var(varX,th);
Jpush_var(varYs,th);
arglist = Jwlistcons(varX,Jwlistcons(varXs,Jwlistcons(varZs,NIL,th),th),th);
mode[th] = 0;}
Jpush_next(&&perm1_2_1_1,th);
clause = Jget_choice(th);
goto select1_3;
perm1_2_1_1:
varYs = Jpop_var(th);
varX = Jpop_var(th);
varXs = Jpop_var(th);
varZs = Jpop_var(th);
arglist = Jwlistcons(varZs,Jwlistcons(varYs,NIL,th),th);
Jpush_back(&&perm1_2_1_0back,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
perm1_2_1_1back:
if(mode[th] == 1){
varYs = Jpop_var(th);
varX = Jpop_var(th);
varXs = Jpop_var(th);
varZs = Jpop_var(th);
Jpush_var(varZs,th);
Jpush_var(varXs,th);
Jpush_var(varX,th);
Jpush_var(varYs,th);
arglist = Jwlistcons(varZs,Jwlistcons(varYs,NIL,th),th);
mode[th] = 0;}
Jpush_next(&&perm1_2_1_2,th);
clause = Jget_choice(th);
goto perm1_2;
perm1_2_1_2:
goto success;
}
perm1_2_2:
Jpop_back(th);
goto allfail;

sort_test_2_0:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
Jrelease(th);
varXs = Jmakevariant(th);
varYs = Jmakevariant(th);
Jinc_choice(th);
Jset_back(&&sort_test_2_1,th);
if(Junify_var(arg1,varXs,th) == YES && Junify_var(arg2,varYs,th) == YES)
{
sort_test_2_0_0:
arglist = Jwlistcons(varXs,Jwlistcons(varYs,NIL,th),th);
Jpush_var(varXs,th);
Jpush_var(varYs,th);
Jpush_back(&&sort_test_2_1,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
sort_test_2_0_0back:
if(mode[th] == 1){
varYs = Jpop_var(th);
varXs = Jpop_var(th);
Jpush_var(varXs,th);
Jpush_var(varYs,th);
arglist = Jwlistcons(varXs,Jwlistcons(varYs,NIL,th),th);
mode[th] = 0;}
Jpush_next(&&sort_test_2_0_1,th);
clause = Jget_choice(th);
goto perm1_2;
sort_test_2_0_1:
varYs = Jpop_var(th);
varXs = Jpop_var(th);
arglist = Jwlistcons(varYs,NIL,th);
Jpush_back(&&sort_test_2_0_0back,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
Jpush_next(&&sort_test_2_0_2,th);
subr_number = Jmakecomp("ordered");
goto builtin_call;
sort_test_2_0_2:
goto success;
}
sort_test_2_1:
Jpop_back(th);
goto allfail;

p1_2_0:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
Jrelease(th);
varZ = Jmakevariant(th);
ano_1 = Jmakevariant(th);
varX = Jmakevariant(th);
varY = Jmakevariant(th);
Jinc_choice(th);
Jset_back(&&p1_2_1,th);
if(Junify_var(arg1,varX,th) == YES && Junify_var(arg2,varY,th) == YES)
{
p1_2_0_0:
arglist = Jwlistcons(varX,Jwlistcons(Jwlistcons(Jmakeint(1),Jwlistcons(Jmakeint(2),Jwlistcons(Jmakeint(3),NIL,th),th),th),Jwlistcons(varZ,NIL,th),th),th);
Jpush_var(varZ,th);
Jpush_var(ano_1,th);
Jpush_var(varX,th);
Jpush_var(varY,th);
Jpush_back(&&p1_2_1,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
p1_2_0_0back:
if(mode[th] == 1){
varY = Jpop_var(th);
varX = Jpop_var(th);
ano_1 = Jpop_var(th);
varZ = Jpop_var(th);
Jpush_var(varZ,th);
Jpush_var(ano_1,th);
Jpush_var(varX,th);
Jpush_var(varY,th);
arglist = Jwlistcons(varX,Jwlistcons(Jwlistcons(Jmakeint(1),Jwlistcons(Jmakeint(2),Jwlistcons(Jmakeint(3),NIL,th),th),th),Jwlistcons(varZ,NIL,th),th),th);
mode[th] = 0;}
Jpush_next(&&p1_2_0_1,th);
clause = Jget_choice(th);
goto select1_3;
p1_2_0_1:
varY = Jpop_var(th);
varX = Jpop_var(th);
ano_1 = Jpop_var(th);
varZ = Jpop_var(th);
arglist = Jwlistcons(varY,Jwlistcons(varZ,Jwlistcons(ano_1,NIL,th),th),th);
Jpush_back(&&p1_2_0_0back,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
p1_2_0_1back:
if(mode[th] == 1){
varY = Jpop_var(th);
varX = Jpop_var(th);
ano_1 = Jpop_var(th);
varZ = Jpop_var(th);
Jpush_var(varZ,th);
Jpush_var(ano_1,th);
Jpush_var(varX,th);
Jpush_var(varY,th);
arglist = Jwlistcons(varY,Jwlistcons(varZ,Jwlistcons(ano_1,NIL,th),th),th);
mode[th] = 0;}
Jpush_next(&&p1_2_0_2,th);
clause = Jget_choice(th);
goto select1_3;
p1_2_0_2:
goto success;
}
p1_2_1:
Jpop_back(th);
goto allfail;

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
Jpush_var(ano_1,th);
Jpush_var(varXs,th);
Jpush_var(varX,th);
Jpush_var(varYs,th);
Jpush_back(&&rtest_2_2,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
rtest_2_1_0back:
if(mode[th] == 1){
varYs = Jpop_var(th);
varX = Jpop_var(th);
varXs = Jpop_var(th);
ano_1 = Jpop_var(th);
Jpush_var(ano_1,th);
Jpush_var(varXs,th);
Jpush_var(varX,th);
Jpush_var(varYs,th);
arglist = Jwlistcons(varX,NIL,th);
mode[th] = 0;}
Jpush_next(&&rtest_2_1_1,th);
clause = Jget_choice(th);
goto choose_1;
rtest_2_1_1:
varYs = Jpop_var(th);
varX = Jpop_var(th);
varXs = Jpop_var(th);
ano_1 = Jpop_var(th);
arglist = Jwlistcons(varXs,Jwlistcons(varYs,NIL,th),th);
Jpush_back(&&rtest_2_1_0back,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
rtest_2_1_1back:
if(mode[th] == 1){
varYs = Jpop_var(th);
varX = Jpop_var(th);
varXs = Jpop_var(th);
ano_1 = Jpop_var(th);
Jpush_var(ano_1,th);
Jpush_var(varXs,th);
Jpush_var(varX,th);
Jpush_var(varYs,th);
arglist = Jwlistcons(varXs,Jwlistcons(varYs,NIL,th),th);
mode[th] = 0;}
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

permtest_0_0:
Jrelease(th);
ano_1 = Jmakevariant(th);
Jinc_choice(th);
Jset_back(&&permtest_0_1,th);
{
permtest_0_0_0:
arglist = Jwlistcons(Jwlistcons(Jmakeint(1),Jwlistcons(Jmakeint(2),Jwlistcons(Jmakeint(3),Jwlistcons(Jmakeint(4),Jwlistcons(Jmakeint(5),NIL,th),th),th),th),th),Jwlistcons(ano_1,NIL,th),th);
Jpush_var(ano_1,th);
Jpush_back(&&permtest_0_1,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
permtest_0_0_0back:
if(mode[th] == 1){
ano_1 = Jpop_var(th);
Jpush_var(ano_1,th);
arglist = Jwlistcons(Jwlistcons(Jmakeint(1),Jwlistcons(Jmakeint(2),Jwlistcons(Jmakeint(3),Jwlistcons(Jmakeint(4),Jwlistcons(Jmakeint(5),NIL,th),th),th),th),th),Jwlistcons(ano_1,NIL,th),th);
mode[th] = 0;}
Jpush_next(&&permtest_0_0_1,th);
clause = Jget_choice(th);
goto perm1_2;
permtest_0_0_1:
ano_1 = Jpop_var(th);
Jpush_back(&&permtest_0_0_0back,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
goto allfail;
}
permtest_0_1:
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
mode[th] = 1;
goto *next;
builtin_call:
if(Jcallsubr(subr_number,arglist,NIL,th) == YES)
goto success;
else goto allfail;
}
