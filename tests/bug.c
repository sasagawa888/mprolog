#include "jump.h"
static int c_mappend(int arglist, int rest, int th);
static int c_n(int arglist, int rest, int th);
static int c_bench(int arglist, int rest, int th);
static int c_nat(int arglist, int rest, int th);
static int c_plus(int arglist, int rest, int th);
static int c_le(int arglist, int rest, int th);
static int c_lt(int arglist, int rest, int th);
static int c_times(int arglist, int rest, int th);
static int c_quot(int arglist, int rest, int th);
static int c_dnd(int arglist, int rest, int th);
static int c_df(int arglist, int rest, int th);
static int c_prime(int arglist, int rest, int th);
static int c_foo(int arglist, int rest, int th);
static int recur_scbm(int pred, int arity, int clause, int arglist, int rest, int th);
static int c_mappend(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
return(recur_scbm(0,n,0,arglist,rest,th));
}

static int c_n(int arglist, int rest, int th){
int arg1,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
if(n == 1){
arg1 = Jcar(arglist);
clause = Jget_choice(th);
switch(clause){
case 0: goto clause_1_0;
case 1: goto clause_1_1;
case 2: goto clause_1_2;
case 3: goto clause_1_3;
case 4: goto clause_1_4;
case 5: goto clause_1_5;
case 6: goto clause_1_6;
case 7: goto clause_1_7;
case 8: goto clause_1_8;
case 9: goto clause_1_9;
default: goto allfail;
}
clause_1_0:
Jinc_choice(th);
if(Junify_int(arg1,Jmakeint(1),th) == YES)
return(YES);
clause_1_1:
Jrelease(th);
Jinc_choice(th);
if(Junify_int(arg1,Jmakeint(2),th) == YES)
return(YES);
clause_1_2:
Jrelease(th);
Jinc_choice(th);
if(Junify_int(arg1,Jmakeint(3),th) == YES)
return(YES);
clause_1_3:
Jrelease(th);
Jinc_choice(th);
if(Junify_int(arg1,Jmakeint(4),th) == YES)
return(YES);
clause_1_4:
Jrelease(th);
Jinc_choice(th);
if(Junify_int(arg1,Jmakeint(5),th) == YES)
return(YES);
clause_1_5:
Jrelease(th);
Jinc_choice(th);
if(Junify_int(arg1,Jmakeint(6),th) == YES)
return(YES);
clause_1_6:
Jrelease(th);
Jinc_choice(th);
if(Junify_int(arg1,Jmakeint(7),th) == YES)
return(YES);
clause_1_7:
Jrelease(th);
Jinc_choice(th);
if(Junify_int(arg1,Jmakeint(8),th) == YES)
return(YES);
clause_1_8:
Jrelease(th);
Jinc_choice(th);
if(Junify_int(arg1,Jmakeint(9),th) == YES)
return(YES);
clause_1_9:
Jrelease(th);
Jinc_choice(th);
if(Junify_int(arg1,Jmakeint(10),th) == YES)
return(YES);
clause_1_10:
Jrelease(th);
allfail:
Jdiscard_conj(th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("n"),arglist);
return(NO);

}
static int c_bench(int arglist, int rest, int th){
int varX,varY,varZ,varA,varB,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
if(n == 0){
clause = Jget_choice(th);
switch(clause){
case 0: goto clause_0_0;
case 1: goto clause_0_1;
default: goto allfail;
}
clause_0_0:
varX = Jmakevariant(th);
varY = Jmakevariant(th);
varZ = Jmakevariant(th);
varA = Jmakevariant(th);
varB = Jmakevariant(th);
Jinc_choice(th);
{
Jpush_conj(th);
retry_0_0_0:;
int arg_0_0_0 = Jwlistcons(varX,NIL,th);
if (c_n(arg_0_0_0,NIL,th) == YES){
Jpush_conj(th);
retry_0_0_1:;
int arg_0_0_1 = Jwlistcons(varY,NIL,th);
if (c_n(arg_0_0_1,NIL,th) == YES){
Jpush_conj(th);
retry_0_0_2:;
int arg_0_0_2 = Jwlistcons(varZ,NIL,th);
if (c_n(arg_0_0_2,NIL,th) == YES){
Jpush_conj(th);
retry_0_0_3:;
int arg_0_0_3 = Jwlistcons(varA,NIL,th);
if (c_n(arg_0_0_3,NIL,th) == YES){
Jpush_conj(th);
retry_0_0_4:;
int arg_0_0_4 = Jwlistcons(varB,NIL,th);
if (c_n(arg_0_0_4,NIL,th) == YES){
goto retry_0_0_4;
{Jsuccess(arglist,th); return(YES);}
}else goto retry_0_0_3;
}else goto retry_0_0_2;
}else goto retry_0_0_1;
}else goto retry_0_0_0;
}
}
clause_0_1:
Jrelease(th);
Jinc_choice(th);
return(YES);
allfail:
Jdiscard_conj(th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("bench"),arglist);
return(NO);

}
static int c_nat(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
return(recur_scbm(1,n,0,arglist,rest,th));
}

static int c_plus(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
return(recur_scbm(2,n,0,arglist,rest,th));
}

static int c_le(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
return(recur_scbm(3,n,0,arglist,rest,th));
}

static int c_lt(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
return(recur_scbm(4,n,0,arglist,rest,th));
}

static int c_times(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
return(recur_scbm(5,n,0,arglist,rest,th));
}

static int c_quot(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
return(recur_scbm(6,n,0,arglist,rest,th));
}

static int c_dnd(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
return(recur_scbm(7,n,0,arglist,rest,th));
}

static int c_df(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
return(recur_scbm(8,n,0,arglist,rest,th));
}

static int c_prime(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
return(recur_scbm(9,n,0,arglist,rest,th));
}

static int c_foo(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
return(recur_scbm(10,n,0,arglist,rest,th));
}

void init_tpredicate(void){
(deftpred)("mappend",c_mappend,3,6);
(deftpred)("n",c_n,1,1);
(deftpred)("bench",c_bench,0,1);
(deftpred)("nat",c_nat,1,6);
(deftpred)("plus",c_plus,3,6);
(deftpred)("le",c_le,2,6);
(deftpred)("lt",c_lt,2,6);
(deftpred)("times",c_times,3,6);
(deftpred)("quot",c_quot,4,6);
(deftpred)("dnd",c_dnd,2,6);
(deftpred)("df",c_df,2,6);
(deftpred)("prime",c_prime,1,6);
(deftpred)("foo",c_foo,3,6);
}
void init_declare(void){
int body,th; th=0;
}
static int recur_scbm(int pred, int arity, int clause, int arglist, int rest, int th){
void *next;
int arg1,arg2,arg3,arg4,arg5,aeg6,arg7,arg8,arg9,arg10,ano_1,ano_2,varA,varM,varN,varQ,varR,varX,varX1,varY,varZ,varZ1;
np[Jget_scp(CONJ,th)][th] = 0; vp[th] = 0;
switch(pred){
case 0: goto mappend;
case 1: goto nat;
case 2: goto plus;
case 3: goto le;
case 4: goto lt;
case 5: goto times;
case 6: goto quot;
case 7: goto dnd;
case 8: goto df;
case 9: goto prime;
case 10: goto foo;
}
mappend:
switch(arity){
case 3: goto mappend_3;
default: goto allfail;
}
nat:
switch(arity){
case 1: goto nat_1;
default: goto allfail;
}
plus:
switch(arity){
case 3: goto plus_3;
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
times:
switch(arity){
case 3: goto times_3;
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
mappend_3:
switch(clause){
case 0: goto mappend_3_0;
case 1: goto mappend_3_1;
default: goto allfail;
}
nat_1:
switch(clause){
case 0: goto nat_1_0;
case 1: goto nat_1_1;
default: goto allfail;
}
plus_3:
switch(clause){
case 0: goto plus_3_0;
case 1: goto plus_3_1;
default: goto allfail;
}
le_2:
switch(clause){
case 0: goto le_2_0;
default: goto allfail;
}
lt_2:
switch(clause){
case 0: goto lt_2_0;
default: goto allfail;
}
times_3:
switch(clause){
case 0: goto times_3_0;
case 1: goto times_3_1;
default: goto allfail;
}
quot_4:
switch(clause){
case 0: goto quot_4_0;
case 1: goto quot_4_1;
default: goto allfail;
}
dnd_2:
switch(clause){
case 0: goto dnd_2_0;
default: goto allfail;
}
df_2:
switch(clause){
case 0: goto df_2_0;
case 1: goto df_2_1;
default: goto allfail;
}
prime_1:
switch(clause){
case 0: goto prime_1_0;
default: goto allfail;
}
foo_3:
switch(clause){
case 0: goto foo_3_0;
default: goto allfail;
}
mappend_3_0:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
Jrelease(th);
varX = Jmakevariant(th);
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
Jset_back(&&mappend_3_2,th);
if(Junify_pair(arg1,Jwlistcons(varA,varX,th),th) == YES && Junify_var(arg2,varY,th) == YES && Junify_pair(arg3,Jwlistcons(varA,varZ,th),th) == YES)
{
mappend_3_1_0:
arglist = Jwlistcons(varX,Jwlistcons(varY,Jwlistcons(varZ,NIL,th),th),th);
Jpush_back(&&mappend_3_2,th);
Jpush_next(&&mappend_3_1_1,th);
goto mappend_3;
mappend_3_1_1:
goto success;
}
mappend_3_2:
goto allfail;

nat_1_0:
arg1 = Jcar(arglist);
Jrelease(th);
Jset_back(&&nat_1_1,th);
if(Junify_int(arg1,Jmakeint(0),th) == YES)
{
goto success;
}
nat_1_1:
arg1 = Jcar(arglist);
Jrelease(th);
varX = Jmakevariant(th);
Jset_back(&&nat_1_2,th);
if(Junify(arg1,Jwcons(Jmakepred("s"),Jwcons(varX,NIL,th),th),th) == YES)
{
nat_1_1_0:
arglist = Jwlistcons(varX,NIL,th);
Jpush_back(&&nat_1_2,th);
Jpush_next(&&nat_1_1_1,th);
goto nat_1;
nat_1_1_1:
goto success;
}
nat_1_2:
goto allfail;

plus_3_0:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
Jrelease(th);
varY = Jmakevariant(th);
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
Jset_back(&&plus_3_2,th);
if(Junify(arg1,Jwcons(Jmakepred("s"),Jwcons(varX,NIL,th),th),th) == YES && Junify_var(arg2,varY,th) == YES && Junify(arg3,Jwcons(Jmakepred("s"),Jwcons(varZ,NIL,th),th),th) == YES)
{
plus_3_1_0:
arglist = Jwlistcons(varX,Jwlistcons(varY,Jwlistcons(varZ,NIL,th),th),th);
Jpush_back(&&plus_3_2,th);
Jpush_next(&&plus_3_1_1,th);
goto plus_3;
plus_3_1_1:
goto success;
}
plus_3_2:
goto allfail;

le_2_0:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
Jrelease(th);
ano_1 = Jmakevariant(th);
varX = Jmakevariant(th);
varY = Jmakevariant(th);
Jset_back(&&le_2_1,th);
if(Junify_var(arg1,varX,th) == YES && Junify_var(arg2,varY,th) == YES)
{
le_2_0_0:
arglist = Jwlistcons(varX,Jwlistcons(ano_1,Jwlistcons(varY,NIL,th),th),th);
Jpush_back(&&le_2_1,th);
Jpush_next(&&le_2_0_1,th);
goto plus_3;
le_2_0_1:
goto success;
}
le_2_1:
goto allfail;

lt_2_0:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
Jrelease(th);
varX = Jmakevariant(th);
varY = Jmakevariant(th);
Jset_back(&&lt_2_1,th);
if(Junify_var(arg1,varX,th) == YES && Junify_var(arg2,varY,th) == YES)
{
lt_2_0_0:
arglist = Jwlistcons(Jwcons(Jmakepred("s"),Jwcons(varX,NIL,th),th),Jwlistcons(varY,NIL,th),th);
Jpush_back(&&lt_2_1,th);
Jpush_next(&&lt_2_0_1,th);
goto le_2;
lt_2_0_1:
goto success;
}
lt_2_1:
goto allfail;

times_3_0:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
Jrelease(th);
ano_1 = Jmakevariant(th);
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
Jset_back(&&times_3_2,th);
if(Junify(arg1,Jwcons(Jmakepred("s"),Jwcons(varX,NIL,th),th),th) == YES && Junify_var(arg2,varY,th) == YES && Junify_var(arg3,varZ,th) == YES)
{
times_3_1_0:
arglist = Jwlistcons(varX,Jwlistcons(varY,Jwlistcons(varZ1,NIL,th),th),th);
Jpush_var(varZ1,th);
Jpush_var(varX,th);
Jpush_var(varY,th);
Jpush_var(varZ,th);
Jpush_back(&&times_3_2,th);
Jpush_next(&&times_3_1_1,th);
goto times_3;
times_3_1_1:
varZ = Jpop_var(th);
varY = Jpop_var(th);
varX = Jpop_var(th);
varZ1 = Jpop_var(th);
arglist = Jwlistcons(varZ1,Jwlistcons(varY,Jwlistcons(varZ,NIL,th),th),th);
Jpush_back(&&times_3_1_1back,th);
times_3_1_1back:
Jpush_next(&&times_3_1_2,th);
goto plus_3;
times_3_1_2:
goto success;
}
times_3_2:
goto allfail;

quot_4_0:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
arg4 = Jnth(arglist,4);
Jrelease(th);
varY = Jmakevariant(th);
varX = Jmakevariant(th);
Jset_back(&&quot_4_1,th);
if(Junify_var(arg1,varX,th) == YES && Junify_var(arg2,varY,th) == YES && Junify_int(arg3,Jmakeint(0),th) == YES && Junify_var(arg4,varX,th) == YES)
{
quot_4_0_0:
arglist = Jwlistcons(varX,Jwlistcons(varY,NIL,th),th);
Jpush_back(&&quot_4_1,th);
Jpush_next(&&quot_4_0_1,th);
goto lt_2;
quot_4_0_1:
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
Jpush_back(&&quot_4_2,th);
Jpush_next(&&quot_4_1_1,th);
goto plus_3;
quot_4_1_1:
varR = Jpop_var(th);
varQ = Jpop_var(th);
varY = Jpop_var(th);
varX = Jpop_var(th);
varX1 = Jpop_var(th);
arglist = Jwlistcons(varX1,Jwlistcons(varY,Jwlistcons(varQ,Jwlistcons(varR,NIL,th),th),th),th);
Jpush_back(&&quot_4_1_1back,th);
quot_4_1_1back:
Jpush_next(&&quot_4_1_2,th);
goto quot_4;
quot_4_1_2:
goto success;
}
quot_4_2:
goto allfail;

dnd_2_0:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
Jrelease(th);
ano_2 = Jmakevariant(th);
ano_1 = Jmakevariant(th);
varM = Jmakevariant(th);
varN = Jmakevariant(th);
Jset_back(&&dnd_2_1,th);
if(Junify_var(arg1,varM,th) == YES && Junify_var(arg2,varN,th) == YES)
{
dnd_2_0_0:
arglist = Jwlistcons(varN,Jwlistcons(varM,Jwlistcons(ano_2,Jwlistcons(Jwcons(Jmakepred("s"),Jwcons(ano_1,NIL,th),th),NIL,th),th),th),th);
Jpush_back(&&dnd_2_1,th);
Jpush_next(&&dnd_2_0_1,th);
goto quot_4;
dnd_2_0_1:
goto success;
}
dnd_2_1:
goto allfail;

df_2_0:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
Jrelease(th);
ano_1 = Jmakevariant(th);
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
Jset_back(&&df_2_2,th);
if(Junify(arg1,Jwcons(Jmakepred("s"),Jwcons(Jwcons(Jmakepred("s"),Jwcons(varM,NIL,th),th),NIL,th),th),th) == YES && Junify_var(arg2,varN,th) == YES)
{
df_2_1_0:
arglist = Jwlistcons(Jwcons(Jmakepred("s"),Jwcons(Jwcons(Jmakepred("s"),Jwcons(varM,NIL,th),th),NIL,th),th),Jwlistcons(varN,NIL,th),th);
Jpush_var(varM,th);
Jpush_var(varN,th);
Jpush_back(&&df_2_2,th);
Jpush_next(&&df_2_1_1,th);
goto dnd_2;
df_2_1_1:
varN = Jpop_var(th);
varM = Jpop_var(th);
arglist = Jwlistcons(Jwcons(Jmakepred("s"),Jwcons(varM,NIL,th),th),Jwlistcons(varN,NIL,th),th);
Jpush_back(&&df_2_1_1back,th);
df_2_1_1back:
Jpush_next(&&df_2_1_2,th);
goto df_2;
df_2_1_2:
goto success;
}
df_2_2:
goto allfail;

prime_1_0:
arg1 = Jcar(arglist);
Jrelease(th);
varX = Jmakevariant(th);
Jset_back(&&prime_1_1,th);
if(Junify(arg1,Jwcons(Jmakepred("s"),Jwcons(varX,NIL,th),th),th) == YES)
{
prime_1_0_0:
arglist = Jwlistcons(varX,Jwlistcons(Jwcons(Jmakepred("s"),Jwcons(varX,NIL,th),th),NIL,th),th);
Jpush_back(&&prime_1_1,th);
Jpush_next(&&prime_1_0_1,th);
goto df_2;
prime_1_0_1:
goto success;
}
prime_1_1:
goto allfail;

foo_3_0:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
Jrelease(th);
varX = Jmakevariant(th);
varY = Jmakevariant(th);
varZ = Jmakevariant(th);
Jset_back(&&foo_3_1,th);
if(Junify_var(arg1,varX,th) == YES && Junify_var(arg2,varY,th) == YES && Junify_var(arg3,varZ,th) == YES)
{
foo_3_0_0:
arglist = Jwlistcons(varX,Jwlistcons(varY,Jwlistcons(varZ,NIL,th),th),th);
Jpush_back(&&foo_3_1,th);
Jpush_next(&&foo_3_0_1,th);
goto plus_3;
foo_3_0_1:
goto success;
}
foo_3_1:
goto allfail;

success:
if(np[Jget_scp(CONJ,th)][th] == 0){
if(Jprove_all(rest,Jget_sp(th),th) == YES) return(YES);
else goto allfail1;
}else{
next = next_stack[np[Jget_scp(CONJ,th)][th]][Jget_scp(CONJ,th)][th];
Jpop_next(th);
goto *next;}
allfail:
if(Jget_scp(RECUR,th)==0) {Jdiscard_conj(th); return(NO);}
next = back_stack[Jget_scp(RECUR,th)][Jget_scp(CONJ,th)][th];
Jpop_recur(th);
Jpop_next(th);
goto *next;allfail1:
next = back_stack[Jget_scp(RECUR,th)][Jget_scp(CONJ,th)][th];
goto *next;}
