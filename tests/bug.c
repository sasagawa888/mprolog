#include "jump.h"
static int c_plus(int arglist, int rest, int th);
static int c_times(int arglist, int rest, int th);
static int c_color(int arglist, int rest, int th);
static int c_mappend(int arglist, int rest, int th);
static int c_reverse(int arglist, int rest, int th);
static int c_list30(int arglist, int rest, int th);
static int c_bench1(int arglist, int rest, int th);
static int c_n(int arglist, int rest, int th);
static int c_bench(int arglist, int rest, int th);
static int c_nat(int arglist, int rest, int th);
static int c_le(int arglist, int rest, int th);
static int c_lt(int arglist, int rest, int th);
static int c_quot(int arglist, int rest, int th);
static int c_dnd(int arglist, int rest, int th);
static int c_df(int arglist, int rest, int th);
static int c_prime(int arglist, int rest, int th);
static int c_foo(int arglist, int rest, int th);
static int c_apptest(int arglist, int rest, int th);
static int c_apptest1(int arglist, int rest, int th);
static int c_likes(int arglist, int rest, int th);
static int c_nodiag(int arglist, int rest, int th);
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

static int c_color(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Jsave_arg(arglist,th);
return(user_scbm(2,n,0,arglist,rest,th));
}

static int c_mappend(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Jsave_arg(arglist,th);
return(user_scbm(3,n,0,arglist,rest,th));
}

static int c_reverse(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Jsave_arg(arglist,th);
return(user_scbm(4,n,0,arglist,rest,th));
}

static int c_list30(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Jsave_arg(arglist,th);
return(user_scbm(5,n,0,arglist,rest,th));
}

static int c_bench1(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Jsave_arg(arglist,th);
return(user_scbm(6,n,0,arglist,rest,th));
}

static int c_n(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Jsave_arg(arglist,th);
return(user_scbm(7,n,0,arglist,rest,th));
}

static int c_bench(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Jsave_arg(arglist,th);
return(user_scbm(8,n,0,arglist,rest,th));
}

static int c_nat(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Jsave_arg(arglist,th);
return(user_scbm(9,n,0,arglist,rest,th));
}

static int c_le(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Jsave_arg(arglist,th);
return(user_scbm(10,n,0,arglist,rest,th));
}

static int c_lt(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Jsave_arg(arglist,th);
return(user_scbm(11,n,0,arglist,rest,th));
}

static int c_quot(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Jsave_arg(arglist,th);
return(user_scbm(12,n,0,arglist,rest,th));
}

static int c_dnd(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Jsave_arg(arglist,th);
return(user_scbm(13,n,0,arglist,rest,th));
}

static int c_df(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Jsave_arg(arglist,th);
return(user_scbm(14,n,0,arglist,rest,th));
}

static int c_prime(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Jsave_arg(arglist,th);
return(user_scbm(15,n,0,arglist,rest,th));
}

static int c_foo(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Jsave_arg(arglist,th);
return(user_scbm(16,n,0,arglist,rest,th));
}

static int c_apptest(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Jsave_arg(arglist,th);
return(user_scbm(17,n,0,arglist,rest,th));
}

static int c_apptest1(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Jsave_arg(arglist,th);
return(user_scbm(18,n,0,arglist,rest,th));
}

static int c_likes(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Jsave_arg(arglist,th);
return(user_scbm(19,n,0,arglist,rest,th));
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
return(YES);
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
(deftpred)("plus",c_plus,3,1);
(deftpred)("times",c_times,3,1);
(deftpred)("color",c_color,1,1);
(deftpred)("mappend",c_mappend,3,1);
(deftpred)("reverse",c_reverse,2,1);
(deftpred)("list30",c_list30,1,1);
(deftpred)("bench1",c_bench1,0,1);
(deftpred)("n",c_n,1,1);
(deftpred)("bench",c_bench,0,1);
(deftpred)("nat",c_nat,1,1);
(deftpred)("le",c_le,2,1);
(deftpred)("lt",c_lt,2,1);
(deftpred)("quot",c_quot,4,1);
(deftpred)("dnd",c_dnd,2,1);
(deftpred)("df",c_df,2,1);
(deftpred)("prime",c_prime,1,1);
(deftpred)("foo",c_foo,3,1);
(deftpred)("apptest",c_apptest,0,1);
(deftpred)("apptest1",c_apptest1,0,1);
(deftpred)("likes",c_likes,2,1);
(deftpred)("nodiag",c_nodiag,3,3);
}
void init_declare(void){
int body,th; th=0;
}
static int user_scbm(int pred, int arity, int clause, int arglist, int rest, int th){
void *next;
int arg1,arg2,arg3,arg4,arg5,aeg6,arg7,arg8,arg9,arg10,subr_number,ano_1,ano_2,varA,varB,varM,varN,varQ,varR,varX,varX1,varXs,varY,varY1,varZ,varZ1;
np[Jget_scp(CONJ,th)][th] = 0; vp[th] = 0;
Jpush_next(&&success,th);
switch(pred){
case 0: goto plus;
case 1: goto times;
case 2: goto color;
case 3: goto mappend;
case 4: goto reverse;
case 5: goto list30;
case 6: goto bench1;
case 7: goto n;
case 8: goto bench;
case 9: goto nat;
case 10: goto le;
case 11: goto lt;
case 12: goto quot;
case 13: goto dnd;
case 14: goto df;
case 15: goto prime;
case 16: goto foo;
case 17: goto apptest;
case 18: goto apptest1;
case 19: goto likes;
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
color:
switch(arity){
case 1: goto color_1;
default: goto allfail;
}
mappend:
switch(arity){
case 3: goto mappend_3;
default: goto allfail;
}
reverse:
switch(arity){
case 2: goto reverse_2;
default: goto allfail;
}
list30:
switch(arity){
case 1: goto list30_1;
default: goto allfail;
}
bench1:
switch(arity){
case 0: goto bench1_0;
default: goto allfail;
}
n:
switch(arity){
case 1: goto n_1;
default: goto allfail;
}
bench:
switch(arity){
case 0: goto bench_0;
default: goto allfail;
}
nat:
switch(arity){
case 1: goto nat_1;
default: goto allfail;
}
le:
switch(arity){
case 2: goto le_2;
default: goto allfail;
}
lt:
switch(arity){
case 2: goto lt_2;
default: goto allfail;
}
quot:
switch(arity){
case 4: goto quot_4;
default: goto allfail;
}
dnd:
switch(arity){
case 2: goto dnd_2;
default: goto allfail;
}
df:
switch(arity){
case 2: goto df_2;
default: goto allfail;
}
prime:
switch(arity){
case 1: goto prime_1;
default: goto allfail;
}
foo:
switch(arity){
case 3: goto foo_3;
default: goto allfail;
}
apptest:
switch(arity){
case 0: goto apptest_0;
default: goto allfail;
}
apptest1:
switch(arity){
case 0: goto apptest1_0;
default: goto allfail;
}
likes:
switch(arity){
case 2: goto likes_2;
default: goto allfail;
}
plus_3:
switch(clause){
case 0: goto plus_3_0;
case 1: goto plus_3_1;
case 2: goto plus_3_2;
default: goto allfail;
}
times_3:
switch(clause){
case 0: goto times_3_0;
case 1: goto times_3_1;
case 2: goto times_3_2;
default: goto allfail;
}
color_1:
switch(clause){
case 0: goto color_1_0;
case 1: goto color_1_1;
case 2: goto color_1_2;
case 3: goto color_1_3;
default: goto allfail;
}
mappend_3:
switch(clause){
case 0: goto mappend_3_0;
case 1: goto mappend_3_1;
case 2: goto mappend_3_2;
default: goto allfail;
}
reverse_2:
switch(clause){
case 0: goto reverse_2_0;
case 1: goto reverse_2_1;
case 2: goto reverse_2_2;
default: goto allfail;
}
list30_1:
switch(clause){
case 0: goto list30_1_0;
case 1: goto list30_1_1;
default: goto allfail;
}
bench1_0:
switch(clause){
case 0: goto bench1_0_0;
case 1: goto bench1_0_1;
default: goto allfail;
}
n_1:
switch(clause){
case 0: goto n_1_0;
case 1: goto n_1_1;
case 2: goto n_1_2;
case 3: goto n_1_3;
case 4: goto n_1_4;
case 5: goto n_1_5;
case 6: goto n_1_6;
case 7: goto n_1_7;
case 8: goto n_1_8;
case 9: goto n_1_9;
case 10: goto n_1_10;
default: goto allfail;
}
bench_0:
switch(clause){
case 0: goto bench_0_0;
case 1: goto bench_0_1;
case 2: goto bench_0_2;
default: goto allfail;
}
nat_1:
switch(clause){
case 0: goto nat_1_0;
case 1: goto nat_1_1;
case 2: goto nat_1_2;
default: goto allfail;
}
le_2:
switch(clause){
case 0: goto le_2_0;
case 1: goto le_2_1;
default: goto allfail;
}
lt_2:
switch(clause){
case 0: goto lt_2_0;
case 1: goto lt_2_1;
default: goto allfail;
}
quot_4:
switch(clause){
case 0: goto quot_4_0;
case 1: goto quot_4_1;
case 2: goto quot_4_2;
default: goto allfail;
}
dnd_2:
switch(clause){
case 0: goto dnd_2_0;
case 1: goto dnd_2_1;
default: goto allfail;
}
df_2:
switch(clause){
case 0: goto df_2_0;
case 1: goto df_2_1;
case 2: goto df_2_2;
default: goto allfail;
}
prime_1:
switch(clause){
case 0: goto prime_1_0;
case 1: goto prime_1_1;
default: goto allfail;
}
foo_3:
switch(clause){
case 0: goto foo_3_0;
case 1: goto foo_3_1;
default: goto allfail;
}
apptest_0:
switch(clause){
case 0: goto apptest_0_0;
case 1: goto apptest_0_1;
default: goto allfail;
}
apptest1_0:
switch(clause){
case 0: goto apptest1_0_0;
case 1: goto apptest1_0_1;
default: goto allfail;
}
likes_2:
switch(clause){
case 0: goto likes_2_0;
case 1: goto likes_2_1;
case 2: goto likes_2_2;
case 3: goto likes_2_3;
case 4: goto likes_2_4;
case 5: goto likes_2_5;
case 6: goto likes_2_6;
case 7: goto likes_2_7;
default: goto allfail;
}
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
Jpush_var(varX,th);
Jpush_var(varY,th);
Jpush_var(varZ,th);
Jpush_back(&&plus_3_2,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
plus_3_1_0back:
Jpush_next(&&plus_3_1_1,th);
clause = Jget_choice(th);
goto plus_3;
plus_3_1_1:
varZ = Jpop_var(th);
varY = Jpop_var(th);
varX = Jpop_var(th);
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
Jpush_var(varZ1,th);
Jpush_var(varX,th);
Jpush_var(varY,th);
Jpush_var(varZ,th);
Jpush_back(&&times_3_1_0back,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
times_3_1_1back:
Jpush_next(&&times_3_1_2,th);
clause = Jget_choice(th);
goto plus_3;
times_3_1_2:
varZ = Jpop_var(th);
varY = Jpop_var(th);
varX = Jpop_var(th);
varZ1 = Jpop_var(th);
goto success;
}
times_3_2:
Jpop_back(th);
goto allfail;

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

mappend_3_0:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
Jrelease(th);
varX = Jmakevariant(th);
Jinc_choice(th);
Jset_back(&&mappend_3_1,th);
if(Junify_nil(arg1,th) == YES && Junify_var(arg2,varX,th) == YES && Junify_var(arg3,varX,th) == YES)
{
goto success;
}
mappend_3_1:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
Jrelease(th);
varX = Jmakevariant(th);
varY = Jmakevariant(th);
varA = Jmakevariant(th);
varZ = Jmakevariant(th);
Jinc_choice(th);
Jset_back(&&mappend_3_2,th);
if(Junify_pair(arg1,Jwlistcons(varA,varX,th),th) == YES && Junify_var(arg2,varY,th) == YES && Junify_pair(arg3,Jwlistcons(varA,varZ,th),th) == YES)
{
mappend_3_1_0:
arglist = Jwlistcons(varX,Jwlistcons(varY,Jwlistcons(varZ,NIL,th),th),th);
Jpush_var(varX,th);
Jpush_var(varY,th);
Jpush_var(varA,th);
Jpush_var(varZ,th);
Jpush_back(&&mappend_3_2,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
mappend_3_1_0back:
Jpush_next(&&mappend_3_1_1,th);
clause = Jget_choice(th);
goto mappend_3;
mappend_3_1_1:
varZ = Jpop_var(th);
varA = Jpop_var(th);
varY = Jpop_var(th);
varX = Jpop_var(th);
goto success;
}
mappend_3_2:
Jpop_back(th);
goto allfail;

reverse_2_0:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
Jrelease(th);
Jinc_choice(th);
Jset_back(&&reverse_2_1,th);
if(Junify_nil(arg1,th) == YES && Junify_nil(arg2,th) == YES)
{
goto success;
}
reverse_2_1:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
Jrelease(th);
varY1 = Jmakevariant(th);
varX = Jmakevariant(th);
varXs = Jmakevariant(th);
varY = Jmakevariant(th);
Jinc_choice(th);
Jset_back(&&reverse_2_2,th);
if(Junify_pair(arg1,Jwlistcons(varX,varXs,th),th) == YES && Junify_var(arg2,varY,th) == YES)
{
reverse_2_1_0:
arglist = Jwlistcons(varXs,Jwlistcons(varY1,NIL,th),th);
Jpush_var(varY1,th);
Jpush_var(varX,th);
Jpush_var(varXs,th);
Jpush_var(varY,th);
Jpush_back(&&reverse_2_2,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
reverse_2_1_0back:
Jpush_next(&&reverse_2_1_1,th);
clause = Jget_choice(th);
goto reverse_2;
reverse_2_1_1:
varY = Jpop_var(th);
varXs = Jpop_var(th);
varX = Jpop_var(th);
varY1 = Jpop_var(th);
arglist = Jwlistcons(varY1,Jwlistcons(Jwlistcons(varX,NIL,th),Jwlistcons(varY,NIL,th),th),th);
Jpush_var(varY1,th);
Jpush_var(varX,th);
Jpush_var(varXs,th);
Jpush_var(varY,th);
Jpush_back(&&reverse_2_1_0back,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
reverse_2_1_1back:
Jpush_next(&&reverse_2_1_2,th);
clause = Jget_choice(th);
goto mappend_3;
reverse_2_1_2:
varY = Jpop_var(th);
varXs = Jpop_var(th);
varX = Jpop_var(th);
varY1 = Jpop_var(th);
goto success;
}
reverse_2_2:
Jpop_back(th);
goto allfail;

list30_1_0:
arg1 = Jcar(arglist);
Jrelease(th);
Jinc_choice(th);
Jset_back(&&list30_1_1,th);
if(Junify(arg1,Jwlistcons(Jmakeint(1),Jwlistcons(Jmakeint(2),Jwlistcons(Jmakeint(3),Jwlistcons(Jmakeint(4),Jwlistcons(Jmakeint(5),Jwlistcons(Jmakeint(6),Jwlistcons(Jmakeint(7),Jwlistcons(Jmakeint(8),Jwlistcons(Jmakeint(9),Jwlistcons(Jmakeint(10),Jwlistcons(Jmakeint(11),Jwlistcons(Jmakeint(12),Jwlistcons(Jmakeint(15),Jwlistcons(Jmakeint(14),Jwlistcons(Jmakeint(15),Jwlistcons(Jmakeint(16),Jwlistcons(Jmakeint(17),Jwlistcons(Jmakeint(18),Jwlistcons(Jmakeint(19),Jwlistcons(Jmakeint(20),Jwlistcons(Jmakeint(21),Jwlistcons(Jmakeint(22),Jwlistcons(Jmakeint(25),Jwlistcons(Jmakeint(24),Jwlistcons(Jmakeint(25),Jwlistcons(Jmakeint(26),Jwlistcons(Jmakeint(27),Jwlistcons(Jmakeint(28),Jwlistcons(Jmakeint(29),Jwlistcons(Jmakeint(30),NIL,th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th) == YES)
{
goto success;
}
list30_1_1:
Jpop_back(th);
goto allfail;

bench1_0_0:
Jrelease(th);
varX = Jmakevariant(th);
varY = Jmakevariant(th);
Jinc_choice(th);
Jset_back(&&bench1_0_1,th);
{
bench1_0_0_0:
arglist = Jwlistcons(varX,NIL,th);
Jpush_var(varX,th);
Jpush_var(varY,th);
Jpush_back(&&bench1_0_1,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
bench1_0_0_0back:
Jpush_next(&&bench1_0_0_1,th);
clause = Jget_choice(th);
goto list30_1;
bench1_0_0_1:
varY = Jpop_var(th);
varX = Jpop_var(th);
arglist = Jwlistcons(varX,Jwlistcons(varY,NIL,th),th);
Jpush_var(varX,th);
Jpush_var(varY,th);
Jpush_back(&&bench1_0_0_0back,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
bench1_0_0_1back:
Jpush_next(&&bench1_0_0_2,th);
clause = Jget_choice(th);
goto reverse_2;
bench1_0_0_2:
varY = Jpop_var(th);
varX = Jpop_var(th);
goto success;
}
bench1_0_1:
Jpop_back(th);
goto allfail;

n_1_0:
arg1 = Jcar(arglist);
Jrelease(th);
Jinc_choice(th);
Jset_back(&&n_1_1,th);
if(Junify_int(arg1,Jmakeint(1),th) == YES)
{
goto success;
}
n_1_1:
arg1 = Jcar(arglist);
Jrelease(th);
Jinc_choice(th);
Jset_back(&&n_1_2,th);
if(Junify_int(arg1,Jmakeint(2),th) == YES)
{
goto success;
}
n_1_2:
arg1 = Jcar(arglist);
Jrelease(th);
Jinc_choice(th);
Jset_back(&&n_1_3,th);
if(Junify_int(arg1,Jmakeint(3),th) == YES)
{
goto success;
}
n_1_3:
arg1 = Jcar(arglist);
Jrelease(th);
Jinc_choice(th);
Jset_back(&&n_1_4,th);
if(Junify_int(arg1,Jmakeint(4),th) == YES)
{
goto success;
}
n_1_4:
arg1 = Jcar(arglist);
Jrelease(th);
Jinc_choice(th);
Jset_back(&&n_1_5,th);
if(Junify_int(arg1,Jmakeint(5),th) == YES)
{
goto success;
}
n_1_5:
arg1 = Jcar(arglist);
Jrelease(th);
Jinc_choice(th);
Jset_back(&&n_1_6,th);
if(Junify_int(arg1,Jmakeint(6),th) == YES)
{
goto success;
}
n_1_6:
arg1 = Jcar(arglist);
Jrelease(th);
Jinc_choice(th);
Jset_back(&&n_1_7,th);
if(Junify_int(arg1,Jmakeint(7),th) == YES)
{
goto success;
}
n_1_7:
arg1 = Jcar(arglist);
Jrelease(th);
Jinc_choice(th);
Jset_back(&&n_1_8,th);
if(Junify_int(arg1,Jmakeint(8),th) == YES)
{
goto success;
}
n_1_8:
arg1 = Jcar(arglist);
Jrelease(th);
Jinc_choice(th);
Jset_back(&&n_1_9,th);
if(Junify_int(arg1,Jmakeint(9),th) == YES)
{
goto success;
}
n_1_9:
arg1 = Jcar(arglist);
Jrelease(th);
Jinc_choice(th);
Jset_back(&&n_1_10,th);
if(Junify_int(arg1,Jmakeint(10),th) == YES)
{
goto success;
}
n_1_10:
Jpop_back(th);
goto allfail;

bench_0_0:
Jrelease(th);
varX = Jmakevariant(th);
varY = Jmakevariant(th);
varZ = Jmakevariant(th);
varA = Jmakevariant(th);
varB = Jmakevariant(th);
Jinc_choice(th);
Jset_back(&&bench_0_1,th);
{
bench_0_0_0:
arglist = Jwlistcons(varX,NIL,th);
Jpush_var(varX,th);
Jpush_var(varY,th);
Jpush_var(varZ,th);
Jpush_var(varA,th);
Jpush_var(varB,th);
Jpush_back(&&bench_0_1,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
bench_0_0_0back:
Jpush_next(&&bench_0_0_1,th);
clause = Jget_choice(th);
goto n_1;
bench_0_0_1:
varB = Jpop_var(th);
varA = Jpop_var(th);
varZ = Jpop_var(th);
varY = Jpop_var(th);
varX = Jpop_var(th);
arglist = Jwlistcons(varY,NIL,th);
Jpush_var(varX,th);
Jpush_var(varY,th);
Jpush_var(varZ,th);
Jpush_var(varA,th);
Jpush_var(varB,th);
Jpush_back(&&bench_0_0_0back,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
bench_0_0_1back:
Jpush_next(&&bench_0_0_2,th);
clause = Jget_choice(th);
goto n_1;
bench_0_0_2:
varB = Jpop_var(th);
varA = Jpop_var(th);
varZ = Jpop_var(th);
varY = Jpop_var(th);
varX = Jpop_var(th);
arglist = Jwlistcons(varZ,NIL,th);
Jpush_var(varX,th);
Jpush_var(varY,th);
Jpush_var(varZ,th);
Jpush_var(varA,th);
Jpush_var(varB,th);
Jpush_back(&&bench_0_0_1back,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
bench_0_0_2back:
Jpush_next(&&bench_0_0_3,th);
clause = Jget_choice(th);
goto n_1;
bench_0_0_3:
varB = Jpop_var(th);
varA = Jpop_var(th);
varZ = Jpop_var(th);
varY = Jpop_var(th);
varX = Jpop_var(th);
arglist = Jwlistcons(varA,NIL,th);
Jpush_var(varX,th);
Jpush_var(varY,th);
Jpush_var(varZ,th);
Jpush_var(varA,th);
Jpush_var(varB,th);
Jpush_back(&&bench_0_0_2back,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
bench_0_0_3back:
Jpush_next(&&bench_0_0_4,th);
clause = Jget_choice(th);
goto n_1;
bench_0_0_4:
varB = Jpop_var(th);
varA = Jpop_var(th);
varZ = Jpop_var(th);
varY = Jpop_var(th);
varX = Jpop_var(th);
arglist = Jwlistcons(varB,NIL,th);
Jpush_var(varX,th);
Jpush_var(varY,th);
Jpush_var(varZ,th);
Jpush_var(varA,th);
Jpush_var(varB,th);
Jpush_back(&&bench_0_0_3back,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
bench_0_0_4back:
Jpush_next(&&bench_0_0_5,th);
clause = Jget_choice(th);
goto n_1;
bench_0_0_5:
varB = Jpop_var(th);
varA = Jpop_var(th);
varZ = Jpop_var(th);
varY = Jpop_var(th);
varX = Jpop_var(th);
arglist = NIL;
Jpush_back(&&bench_0_0_4back,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
Jpush_next(&&bench_0_0_6,th);
subr_number = 593;
goto builtin_call;
bench_0_0_6:
goto success;
}
bench_0_1:
Jrelease(th);
Jinc_choice(th);
Jset_back(&&bench_0_2,th);
{
goto success;
}
bench_0_2:
Jpop_back(th);
goto allfail;

nat_1_0:
arg1 = Jcar(arglist);
Jrelease(th);
Jinc_choice(th);
Jset_back(&&nat_1_1,th);
if(Junify_int(arg1,Jmakeint(0),th) == YES)
{
goto success;
}
nat_1_1:
arg1 = Jcar(arglist);
Jrelease(th);
varX = Jmakevariant(th);
Jinc_choice(th);
Jset_back(&&nat_1_2,th);
if(Junify(arg1,Jwcons(Jmakepred("s"),Jwcons(varX,NIL,th),th),th) == YES)
{
nat_1_1_0:
arglist = Jwlistcons(varX,NIL,th);
Jpush_var(varX,th);
Jpush_back(&&nat_1_2,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
nat_1_1_0back:
Jpush_next(&&nat_1_1_1,th);
clause = Jget_choice(th);
goto nat_1;
nat_1_1_1:
varX = Jpop_var(th);
goto success;
}
nat_1_2:
Jpop_back(th);
goto allfail;

le_2_0:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
Jrelease(th);
ano_1 = Jmakevariant(th);
varX = Jmakevariant(th);
varY = Jmakevariant(th);
Jinc_choice(th);
Jset_back(&&le_2_1,th);
if(Junify_var(arg1,varX,th) == YES && Junify_var(arg2,varY,th) == YES)
{
le_2_0_0:
arglist = Jwlistcons(varX,Jwlistcons(ano_1,Jwlistcons(varY,NIL,th),th),th);
Jpush_var(ano_1,th);
Jpush_var(varX,th);
Jpush_var(varY,th);
Jpush_back(&&le_2_1,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
le_2_0_0back:
Jpush_next(&&le_2_0_1,th);
clause = Jget_choice(th);
goto plus_3;
le_2_0_1:
varY = Jpop_var(th);
varX = Jpop_var(th);
ano_1 = Jpop_var(th);
goto success;
}
le_2_1:
Jpop_back(th);
goto allfail;

lt_2_0:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
Jrelease(th);
varX = Jmakevariant(th);
varY = Jmakevariant(th);
Jinc_choice(th);
Jset_back(&&lt_2_1,th);
if(Junify_var(arg1,varX,th) == YES && Junify_var(arg2,varY,th) == YES)
{
lt_2_0_0:
arglist = Jwlistcons(Jwcons(Jmakepred("s"),Jwcons(varX,NIL,th),th),Jwlistcons(varY,NIL,th),th);
Jpush_var(varX,th);
Jpush_var(varY,th);
Jpush_back(&&lt_2_1,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
lt_2_0_0back:
Jpush_next(&&lt_2_0_1,th);
clause = Jget_choice(th);
goto le_2;
lt_2_0_1:
varY = Jpop_var(th);
varX = Jpop_var(th);
goto success;
}
lt_2_1:
Jpop_back(th);
goto allfail;

quot_4_0:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
arg4 = Jnth(arglist,4);
Jrelease(th);
varY = Jmakevariant(th);
varX = Jmakevariant(th);
Jinc_choice(th);
Jset_back(&&quot_4_1,th);
if(Junify_var(arg1,varX,th) == YES && Junify_var(arg2,varY,th) == YES && Junify_int(arg3,Jmakeint(0),th) == YES && Junify_var(arg4,varX,th) == YES)
{
quot_4_0_0:
arglist = Jwlistcons(varX,Jwlistcons(varY,NIL,th),th);
Jpush_var(varY,th);
Jpush_var(varX,th);
Jpush_back(&&quot_4_1,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
quot_4_0_0back:
Jpush_next(&&quot_4_0_1,th);
clause = Jget_choice(th);
goto lt_2;
quot_4_0_1:
varX = Jpop_var(th);
varY = Jpop_var(th);
goto success;
}
quot_4_1:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
arg4 = Jnth(arglist,4);
Jrelease(th);
varX1 = Jmakevariant(th);
varX = Jmakevariant(th);
varY = Jmakevariant(th);
varQ = Jmakevariant(th);
varR = Jmakevariant(th);
Jinc_choice(th);
Jset_back(&&quot_4_2,th);
if(Junify_var(arg1,varX,th) == YES && Junify_var(arg2,varY,th) == YES && Junify(arg3,Jwcons(Jmakepred("s"),Jwcons(varQ,NIL,th),th),th) == YES && Junify_var(arg4,varR,th) == YES)
{
quot_4_1_0:
arglist = Jwlistcons(varY,Jwlistcons(varX1,Jwlistcons(varX,NIL,th),th),th);
Jpush_var(varX1,th);
Jpush_var(varX,th);
Jpush_var(varY,th);
Jpush_var(varQ,th);
Jpush_var(varR,th);
Jpush_back(&&quot_4_2,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
quot_4_1_0back:
Jpush_next(&&quot_4_1_1,th);
clause = Jget_choice(th);
goto plus_3;
quot_4_1_1:
varR = Jpop_var(th);
varQ = Jpop_var(th);
varY = Jpop_var(th);
varX = Jpop_var(th);
varX1 = Jpop_var(th);
arglist = Jwlistcons(varX1,Jwlistcons(varY,Jwlistcons(varQ,Jwlistcons(varR,NIL,th),th),th),th);
Jpush_var(varX1,th);
Jpush_var(varX,th);
Jpush_var(varY,th);
Jpush_var(varQ,th);
Jpush_var(varR,th);
Jpush_back(&&quot_4_1_0back,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
quot_4_1_1back:
Jpush_next(&&quot_4_1_2,th);
clause = Jget_choice(th);
goto quot_4;
quot_4_1_2:
varR = Jpop_var(th);
varQ = Jpop_var(th);
varY = Jpop_var(th);
varX = Jpop_var(th);
varX1 = Jpop_var(th);
goto success;
}
quot_4_2:
Jpop_back(th);
goto allfail;

dnd_2_0:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
Jrelease(th);
ano_2 = Jmakevariant(th);
ano_1 = Jmakevariant(th);
varM = Jmakevariant(th);
varN = Jmakevariant(th);
Jinc_choice(th);
Jset_back(&&dnd_2_1,th);
if(Junify_var(arg1,varM,th) == YES && Junify_var(arg2,varN,th) == YES)
{
dnd_2_0_0:
arglist = Jwlistcons(varN,Jwlistcons(varM,Jwlistcons(ano_2,Jwlistcons(Jwcons(Jmakepred("s"),Jwcons(ano_1,NIL,th),th),NIL,th),th),th),th);
Jpush_var(ano_2,th);
Jpush_var(ano_1,th);
Jpush_var(varM,th);
Jpush_var(varN,th);
Jpush_back(&&dnd_2_1,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
dnd_2_0_0back:
Jpush_next(&&dnd_2_0_1,th);
clause = Jget_choice(th);
goto quot_4;
dnd_2_0_1:
varN = Jpop_var(th);
varM = Jpop_var(th);
ano_1 = Jpop_var(th);
ano_2 = Jpop_var(th);
goto success;
}
dnd_2_1:
Jpop_back(th);
goto allfail;

df_2_0:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
Jrelease(th);
ano_1 = Jmakevariant(th);
Jinc_choice(th);
Jset_back(&&df_2_1,th);
if(Junify(arg1,Jwcons(Jmakepred("s"),Jwcons(Jmakeint(0),NIL,th),th),th) == YES && Junify_var(arg2,ano_1,th) == YES)
{
goto success;
}
df_2_1:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
Jrelease(th);
varM = Jmakevariant(th);
varN = Jmakevariant(th);
Jinc_choice(th);
Jset_back(&&df_2_2,th);
if(Junify(arg1,Jwcons(Jmakepred("s"),Jwcons(Jwcons(Jmakepred("s"),Jwcons(varM,NIL,th),th),NIL,th),th),th) == YES && Junify_var(arg2,varN,th) == YES)
{
df_2_1_0:
arglist = Jwlistcons(Jwcons(Jmakepred("s"),Jwcons(Jwcons(Jmakepred("s"),Jwcons(varM,NIL,th),th),NIL,th),th),Jwlistcons(varN,NIL,th),th);
Jpush_var(varM,th);
Jpush_var(varN,th);
Jpush_back(&&df_2_2,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
df_2_1_0back:
Jpush_next(&&df_2_1_1,th);
clause = Jget_choice(th);
goto dnd_2;
df_2_1_1:
varN = Jpop_var(th);
varM = Jpop_var(th);
arglist = Jwlistcons(Jwcons(Jmakepred("s"),Jwcons(varM,NIL,th),th),Jwlistcons(varN,NIL,th),th);
Jpush_var(varM,th);
Jpush_var(varN,th);
Jpush_back(&&df_2_1_0back,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
df_2_1_1back:
Jpush_next(&&df_2_1_2,th);
clause = Jget_choice(th);
goto df_2;
df_2_1_2:
varN = Jpop_var(th);
varM = Jpop_var(th);
goto success;
}
df_2_2:
Jpop_back(th);
goto allfail;

prime_1_0:
arg1 = Jcar(arglist);
Jrelease(th);
varX = Jmakevariant(th);
Jinc_choice(th);
Jset_back(&&prime_1_1,th);
if(Junify(arg1,Jwcons(Jmakepred("s"),Jwcons(varX,NIL,th),th),th) == YES)
{
prime_1_0_0:
arglist = Jwlistcons(varX,Jwlistcons(Jwcons(Jmakepred("s"),Jwcons(varX,NIL,th),th),NIL,th),th);
Jpush_var(varX,th);
Jpush_back(&&prime_1_1,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
prime_1_0_0back:
Jpush_next(&&prime_1_0_1,th);
clause = Jget_choice(th);
goto df_2;
prime_1_0_1:
varX = Jpop_var(th);
goto success;
}
prime_1_1:
Jpop_back(th);
goto allfail;

foo_3_0:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
Jrelease(th);
varX = Jmakevariant(th);
varY = Jmakevariant(th);
varZ = Jmakevariant(th);
Jinc_choice(th);
Jset_back(&&foo_3_1,th);
if(Junify_var(arg1,varX,th) == YES && Junify_var(arg2,varY,th) == YES && Junify_var(arg3,varZ,th) == YES)
{
foo_3_0_0:
arglist = Jwlistcons(varX,Jwlistcons(varY,Jwlistcons(varZ,NIL,th),th),th);
Jpush_var(varX,th);
Jpush_var(varY,th);
Jpush_var(varZ,th);
Jpush_back(&&foo_3_1,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
foo_3_0_0back:
Jpush_next(&&foo_3_0_1,th);
clause = Jget_choice(th);
goto plus_3;
foo_3_0_1:
varZ = Jpop_var(th);
varY = Jpop_var(th);
varX = Jpop_var(th);
goto success;
}
foo_3_1:
Jpop_back(th);
goto allfail;

apptest_0_0:
Jrelease(th);
varX = Jmakevariant(th);
varY = Jmakevariant(th);
Jinc_choice(th);
Jset_back(&&apptest_0_1,th);
{
apptest_0_0_0:
arglist = Jwlistcons(varX,Jwlistcons(varY,Jwlistcons(Jwlistcons(Jmakeint(1),Jwlistcons(Jmakeint(2),Jwlistcons(Jmakeint(3),NIL,th),th),th),NIL,th),th),th);
Jpush_var(varX,th);
Jpush_var(varY,th);
Jpush_back(&&apptest_0_1,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
apptest_0_0_0back:
Jpush_next(&&apptest_0_0_1,th);
clause = Jget_choice(th);
goto mappend_3;
apptest_0_0_1:
varY = Jpop_var(th);
varX = Jpop_var(th);
arglist = Jwlistcons(varX,NIL,th);
Jpush_back(&&apptest_0_0_0back,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
Jpush_next(&&apptest_0_0_2,th);
subr_number = 1204;
goto builtin_call;
apptest_0_0_2:
arglist = Jwlistcons(varY,NIL,th);
Jpush_next(&&apptest_0_0_3,th);
subr_number = 1204;
goto builtin_call;
apptest_0_0_3:
arglist = NIL;
Jpush_next(&&apptest_0_0_4,th);
subr_number = 593;
goto builtin_call;
apptest_0_0_4:
goto success;
}
apptest_0_1:
Jpop_back(th);
goto allfail;

apptest1_0_0:
Jrelease(th);
varX = Jmakevariant(th);
varY = Jmakevariant(th);
Jinc_choice(th);
Jset_back(&&apptest1_0_1,th);
{
apptest1_0_0_0:
arglist = Jwlistcons(varX,Jwlistcons(varY,Jwlistcons(Jwlistcons(Jmakeint(1),Jwlistcons(Jmakeint(2),Jwlistcons(Jmakeint(3),Jwlistcons(Jmakeint(4),Jwlistcons(Jmakeint(5),Jwlistcons(Jmakeint(6),Jwlistcons(Jmakeint(7),Jwlistcons(Jmakeint(8),Jwlistcons(Jmakeint(9),Jwlistcons(Jmakeint(0),NIL,th),th),th),th),th),th),th),th),th),th),NIL,th),th),th);
Jpush_var(varX,th);
Jpush_var(varY,th);
Jpush_back(&&apptest1_0_1,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
apptest1_0_0_0back:
Jpush_next(&&apptest1_0_0_1,th);
clause = Jget_choice(th);
goto mappend_3;
apptest1_0_0_1:
varY = Jpop_var(th);
varX = Jpop_var(th);
arglist = NIL;
Jpush_back(&&apptest1_0_0_0back,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
Jpush_next(&&apptest1_0_0_2,th);
subr_number = 593;
goto builtin_call;
apptest1_0_0_2:
goto success;
}
apptest1_0_1:
Jpop_back(th);
goto allfail;

likes_2_0:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
Jrelease(th);
Jinc_choice(th);
Jset_back(&&likes_2_1,th);
if(Junify_atom(arg1,Jmakeconst("kim"),th) == YES && Junify_atom(arg2,Jmakeconst("robin"),th) == YES)
{
goto success;
}
likes_2_1:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
Jrelease(th);
Jinc_choice(th);
Jset_back(&&likes_2_2,th);
if(Junify_atom(arg1,Jmakeconst("sandy"),th) == YES && Junify_atom(arg2,Jmakeconst("lee"),th) == YES)
{
goto success;
}
likes_2_2:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
Jrelease(th);
Jinc_choice(th);
Jset_back(&&likes_2_3,th);
if(Junify_atom(arg1,Jmakeconst("sandy"),th) == YES && Junify_atom(arg2,Jmakeconst("kim"),th) == YES)
{
goto success;
}
likes_2_3:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
Jrelease(th);
Jinc_choice(th);
Jset_back(&&likes_2_4,th);
if(Junify_atom(arg1,Jmakeconst("robin"),th) == YES && Junify_atom(arg2,Jmakeconst("cats"),th) == YES)
{
goto success;
}
likes_2_4:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
Jrelease(th);
varX = Jmakevariant(th);
Jinc_choice(th);
Jset_back(&&likes_2_5,th);
if(Junify_atom(arg1,Jmakeconst("sandy"),th) == YES && Junify_var(arg2,varX,th) == YES)
{
likes_2_4_0:
arglist = Jwlistcons(varX,Jwlistcons(Jmakeconst("cats"),NIL,th),th);
Jpush_var(varX,th);
Jpush_back(&&likes_2_5,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
likes_2_4_0back:
Jpush_next(&&likes_2_4_1,th);
clause = Jget_choice(th);
goto likes_2;
likes_2_4_1:
varX = Jpop_var(th);
goto success;
}
likes_2_5:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
Jrelease(th);
varX = Jmakevariant(th);
Jinc_choice(th);
Jset_back(&&likes_2_6,th);
if(Junify_atom(arg1,Jmakeconst("kim"),th) == YES && Junify_var(arg2,varX,th) == YES)
{
likes_2_5_0:
arglist = Jwlistcons(varX,Jwlistcons(Jmakeconst("lee"),NIL,th),th);
Jpush_var(varX,th);
Jpush_back(&&likes_2_6,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
likes_2_5_0back:
Jpush_next(&&likes_2_5_1,th);
clause = Jget_choice(th);
goto likes_2;
likes_2_5_1:
varX = Jpop_var(th);
arglist = Jwlistcons(varX,Jwlistcons(Jmakeconst("kim"),NIL,th),th);
Jpush_var(varX,th);
Jpush_back(&&likes_2_5_0back,arglist,vp[th],np[Jget_scp(CONJ,th)][th],th);
likes_2_5_1back:
Jpush_next(&&likes_2_5_2,th);
clause = Jget_choice(th);
goto likes_2;
likes_2_5_2:
varX = Jpop_var(th);
goto success;
}
likes_2_6:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
Jrelease(th);
varX = Jmakevariant(th);
Jinc_choice(th);
Jset_back(&&likes_2_7,th);
if(Junify_var(arg1,varX,th) == YES && Junify_var(arg2,varX,th) == YES)
{
goto success;
}
likes_2_7:
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
builtin_call:
if(Jcallsubr(subr_number,arglist,NIL,th) == YES)
goto success;
else goto allfail;
}
