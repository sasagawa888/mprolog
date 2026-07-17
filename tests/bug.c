#include "jump.h"
static int c_mappend(int arglist, int rest, int th);
static int c_apptest(int arglist, int rest, int th);
static int c_nat(int arglist, int rest, int th);
static int c_plus(int arglist, int rest, int th);
static int c_times(int arglist, int rest, int th);
static int c_le(int arglist, int rest, int th);
static int c_lt(int arglist, int rest, int th);
static int c_quot(int arglist, int rest, int th);
static int c_dnd(int arglist, int rest, int th);
static int c_df(int arglist, int rest, int th);
static int c_prime(int arglist, int rest, int th);
static int c_apptest1(int arglist, int rest, int th);
static int recur_scbm(int pred, int clause, int arglist);
static int c_mappend(int arglist, int rest, int th){
int arg1,arg2,arg3,varY,varA,varZ,varX,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
arglist = Jprepare(arglist,th);
Jpredname("mappend");
if(n == 3){
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
clause = Jget_choice(th);
switch(clause){
case 0: goto clause_3_0;
case 10000: goto skip_3_0;
case 1: goto clause_3_1;
case 10001: goto skip_3_1;
default: goto allfail;
}
clause_3_0:
varX = Jmakevariant(th);
Jinc_choice(th);
if(Junify_nil(arg1,th) == YES && Junify_var(arg2,varX,th) == YES && Junify_var(arg3,varX,th) == YES)
{
skip_3_0:
Jsuccess(arglist,th); return(YES);}
clause_3_1:
Jrelease(th);
varX = Jmakevariant(th);
varY = Jmakevariant(th);
varA = Jmakevariant(th);
varZ = Jmakevariant(th);
Jinc_choice(th);
if(Junify_pair(arg1,Jwlistcons(varA,varX,th),th) == YES && Junify_var(arg2,varY,th) == YES && Junify_pair(arg3,Jwlistcons(varA,varZ,th),th) == YES)
{
skip_3_1:;
int arg_3_1_0 = Jwlistcons(varX,Jwlistcons(varY,Jwlistcons(varZ,NIL,th),th),th);
retry_3_1_0:;
Jpush_recur(th);
if (c_mappend(arg_3_1_0,NIL,th) == YES){
Jpop_recur(th);
return(YES);
}
}
clause_3_2:
Jrelease(th);
allfail:
Jdiscard_recur(th);
if(rest != NIL) Jdiscard_conj(th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("mappend"),arglist);
return(NO);}
static int c_apptest(int arglist, int rest, int th){
int varX,varY,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
arglist = Jprepare(arglist,th);
Jpredname("apptest");
if(n == 0){
clause = Jget_choice(th);
switch(clause){
case 0: goto clause_0_0;
case 10000: goto skip_0_0;
default: goto allfail;
}
clause_0_0:
varX = Jmakevariant(th);
varY = Jmakevariant(th);
Jinc_choice(th);
{
skip_0_0:;
int arg_0_0_0 = Jwlistcons(varX,Jwlistcons(varY,Jwlistcons(Jwlistcons(Jmakeint(1),Jwlistcons(Jmakeint(2),Jwlistcons(Jmakeint(3),NIL,th),th),th),NIL,th),th),th);
retry_0_0_0:;
Jpush_recur(th);
if (c_mappend(arg_0_0_0,NIL,th) == YES){
Jpop_recur(th);
if (Jcall_det(Jmakesys("write"),Jwlistcons(varX,NIL,th),th) == YES){
if (Jcall_det(Jmakesys("write"),Jwlistcons(varY,NIL,th),th) == YES){
Jset_mode(RETRY,th);
goto retry_0_0_0;
return(YES);
}else{Jset_mode(RETRY,th);
goto retry_0_0_0;}
}else{Jset_mode(RETRY,th);
goto retry_0_0_0;}
}
}
clause_0_1:
Jrelease(th);
allfail:
Jdiscard_recur(th);
if(rest != NIL) Jdiscard_conj(th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("apptest"),arglist);
return(NO);}
static int c_nat(int arglist, int rest, int th){
int arg1,varX,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
arglist = Jprepare(arglist,th);
Jpredname("nat");
if(n == 1){
arg1 = Jcar(arglist);
clause = Jget_choice(th);
switch(clause){
case 0: goto clause_1_0;
case 10000: goto skip_1_0;
case 1: goto clause_1_1;
case 10001: goto skip_1_1;
default: goto allfail;
}
clause_1_0:
Jinc_choice(th);
if(Junify_int(arg1,Jmakeint(0),th) == YES)
{
skip_1_0:
Jsuccess(arglist,th); return(YES);}
clause_1_1:
Jrelease(th);
varX = Jmakevariant(th);
Jinc_choice(th);
if(Junify(arg1,Jwcons(Jmakepred("s"),Jwcons(varX,NIL,th),th),th) == YES)
{
skip_1_1:;
int arg_1_1_0 = Jwlistcons(varX,NIL,th);
retry_1_1_0:;
Jpush_recur(th);
if (c_nat(arg_1_1_0,NIL,th) == YES){
Jpop_recur(th);
return(YES);
}
}
clause_1_2:
Jrelease(th);
allfail:
Jdiscard_recur(th);
if(rest != NIL) Jdiscard_conj(th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("nat"),arglist);
return(NO);}
static int c_plus(int arglist, int rest, int th){
int arg1,arg2,arg3,varX,varZ,varY,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
arglist = Jprepare(arglist,th);
Jpredname("plus");
if(n == 3){
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
clause = Jget_choice(th);
switch(clause){
case 0: goto clause_3_0;
case 10000: goto skip_3_0;
case 1: goto clause_3_1;
case 10001: goto skip_3_1;
default: goto allfail;
}
clause_3_0:
varY = Jmakevariant(th);
Jinc_choice(th);
if(Junify_int(arg1,Jmakeint(0),th) == YES && Junify_var(arg2,varY,th) == YES && Junify_var(arg3,varY,th) == YES)
{
skip_3_0:
Jsuccess(arglist,th); return(YES);}
clause_3_1:
Jrelease(th);
varX = Jmakevariant(th);
varY = Jmakevariant(th);
varZ = Jmakevariant(th);
Jinc_choice(th);
if(Junify(arg1,Jwcons(Jmakepred("s"),Jwcons(varX,NIL,th),th),th) == YES && Junify_var(arg2,varY,th) == YES && Junify(arg3,Jwcons(Jmakepred("s"),Jwcons(varZ,NIL,th),th),th) == YES)
{
skip_3_1:;
int arg_3_1_0 = Jwlistcons(varX,Jwlistcons(varY,Jwlistcons(varZ,NIL,th),th),th);
retry_3_1_0:;
Jpush_recur(th);
if (c_plus(arg_3_1_0,NIL,th) == YES){
Jpop_recur(th);
return(YES);
}
}
clause_3_2:
Jrelease(th);
allfail:
Jdiscard_recur(th);
if(rest != NIL) Jdiscard_conj(th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("plus"),arglist);
return(NO);}
static int c_times(int arglist, int rest, int th){
int arg1,arg2,arg3,varZ1,varX,varY,varZ,ano_1,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
arglist = Jprepare(arglist,th);
Jpredname("times");
if(n == 3){
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
clause = Jget_choice(th);
switch(clause){
case 0: goto clause_3_0;
case 10000: goto skip_3_0;
case 1: goto clause_3_1;
case 10001: goto skip_3_1;
default: goto allfail;
}
clause_3_0:
ano_1 = Jmakevariant(th);
Jinc_choice(th);
if(Junify_int(arg1,Jmakeint(0),th) == YES && Junify_var(arg2,ano_1,th) == YES && Junify_int(arg3,Jmakeint(0),th) == YES)
{
skip_3_0:
Jsuccess(arglist,th); return(YES);}
clause_3_1:
Jrelease(th);
varZ1 = Jmakevariant(th);
varX = Jmakevariant(th);
varY = Jmakevariant(th);
varZ = Jmakevariant(th);
Jinc_choice(th);
if(Junify(arg1,Jwcons(Jmakepred("s"),Jwcons(varX,NIL,th),th),th) == YES && Junify_var(arg2,varY,th) == YES && Junify_var(arg3,varZ,th) == YES)
{
skip_3_1:;
int arg_3_1_0 = Jwlistcons(varX,Jwlistcons(varY,Jwlistcons(varZ1,NIL,th),th),th);
retry_3_1_0:;
Jpush_recur(th);
if (c_times(arg_3_1_0,NIL,th) == YES){
Jpop_recur(th);
int arg_3_1_1 = Jwlistcons(varZ1,Jwlistcons(varY,Jwlistcons(varZ,NIL,th),th),th);
retry_3_1_1:;
Jpush_recur(th);
if (c_plus(arg_3_1_1,NIL,th) == YES){
Jpop_recur(th);
return(YES);
}else{Jset_mode(RETRY,th);
goto retry_3_1_0;}
}
}
clause_3_2:
Jrelease(th);
allfail:
Jdiscard_recur(th);
if(rest != NIL) Jdiscard_conj(th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("times"),arglist);
return(NO);}
static int c_le(int arglist, int rest, int th){
int arg1,arg2,ano_1,varX,varY,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
arglist = Jprepare(arglist,th);
Jpredname("le");
if(n == 2){
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
clause = Jget_choice(th);
switch(clause){
case 0: goto clause_2_0;
case 10000: goto skip_2_0;
default: goto allfail;
}
clause_2_0:
ano_1 = Jmakevariant(th);
varX = Jmakevariant(th);
varY = Jmakevariant(th);
Jinc_choice(th);
if(Junify_var(arg1,varX,th) == YES && Junify_var(arg2,varY,th) == YES)
{
skip_2_0:;
int arg_2_0_0 = Jwlistcons(varX,Jwlistcons(ano_1,Jwlistcons(varY,NIL,th),th),th);
retry_2_0_0:;
Jpush_recur(th);
if (c_plus(arg_2_0_0,NIL,th) == YES){
Jpop_recur(th);
return(YES);
}
}
clause_2_1:
Jrelease(th);
allfail:
Jdiscard_recur(th);
if(rest != NIL) Jdiscard_conj(th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("le"),arglist);
return(NO);}
static int c_lt(int arglist, int rest, int th){
int arg1,arg2,varX,varY,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
arglist = Jprepare(arglist,th);
Jpredname("lt");
if(n == 2){
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
clause = Jget_choice(th);
switch(clause){
case 0: goto clause_2_0;
case 10000: goto skip_2_0;
default: goto allfail;
}
clause_2_0:
varX = Jmakevariant(th);
varY = Jmakevariant(th);
Jinc_choice(th);
if(Junify_var(arg1,varX,th) == YES && Junify_var(arg2,varY,th) == YES)
{
skip_2_0:;
int arg_2_0_0 = Jwlistcons(Jwcons(Jmakepred("s"),Jwcons(varX,NIL,th),th),Jwlistcons(varY,NIL,th),th);
retry_2_0_0:;
Jpush_recur(th);
if (c_le(arg_2_0_0,NIL,th) == YES){
Jpop_recur(th);
return(YES);
}
}
clause_2_1:
Jrelease(th);
allfail:
Jdiscard_recur(th);
if(rest != NIL) Jdiscard_conj(th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("lt"),arglist);
return(NO);}
static int c_quot(int arglist, int rest, int th){
int arg1,arg2,arg3,arg4,varX1,varQ,varR,varY,varX,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
arglist = Jprepare(arglist,th);
Jpredname("quot");
if(n == 4){
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
arg4 = Jnth(arglist,4);
clause = Jget_choice(th);
switch(clause){
case 0: goto clause_4_0;
case 10000: goto skip_4_0;
case 1: goto clause_4_1;
case 10001: goto skip_4_1;
default: goto allfail;
}
clause_4_0:
varY = Jmakevariant(th);
varX = Jmakevariant(th);
Jinc_choice(th);
if(Junify_var(arg1,varX,th) == YES && Junify_var(arg2,varY,th) == YES && Junify_int(arg3,Jmakeint(0),th) == YES && Junify_var(arg4,varX,th) == YES)
{
skip_4_0:;
int arg_4_0_0 = Jwlistcons(varX,Jwlistcons(varY,NIL,th),th);
retry_4_0_0:;
Jpush_recur(th);
if (c_lt(arg_4_0_0,NIL,th) == YES){
Jpop_recur(th);
return(YES);
}
}
clause_4_1:
Jrelease(th);
varX1 = Jmakevariant(th);
varX = Jmakevariant(th);
varY = Jmakevariant(th);
varQ = Jmakevariant(th);
varR = Jmakevariant(th);
Jinc_choice(th);
if(Junify_var(arg1,varX,th) == YES && Junify_var(arg2,varY,th) == YES && Junify(arg3,Jwcons(Jmakepred("s"),Jwcons(varQ,NIL,th),th),th) == YES && Junify_var(arg4,varR,th) == YES)
{
skip_4_1:;
int arg_4_1_0 = Jwlistcons(varY,Jwlistcons(varX1,Jwlistcons(varX,NIL,th),th),th);
retry_4_1_0:;
Jpush_recur(th);
if (c_plus(arg_4_1_0,NIL,th) == YES){
Jpop_recur(th);
int arg_4_1_1 = Jwlistcons(varX1,Jwlistcons(varY,Jwlistcons(varQ,Jwlistcons(varR,NIL,th),th),th),th);
retry_4_1_1:;
Jpush_recur(th);
if (c_quot(arg_4_1_1,NIL,th) == YES){
Jpop_recur(th);
return(YES);
}else{Jset_mode(RETRY,th);
goto retry_4_1_0;}
}
}
clause_4_2:
Jrelease(th);
allfail:
Jdiscard_recur(th);
if(rest != NIL) Jdiscard_conj(th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("quot"),arglist);
return(NO);}
static int c_dnd(int arglist, int rest, int th){
int arg1,arg2,ano_2,ano_1,varM,varN,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
arglist = Jprepare(arglist,th);
Jpredname("dnd");
if(n == 2){
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
clause = Jget_choice(th);
switch(clause){
case 0: goto clause_2_0;
case 10000: goto skip_2_0;
default: goto allfail;
}
clause_2_0:
ano_2 = Jmakevariant(th);
ano_1 = Jmakevariant(th);
varM = Jmakevariant(th);
varN = Jmakevariant(th);
Jinc_choice(th);
if(Junify_var(arg1,varM,th) == YES && Junify_var(arg2,varN,th) == YES)
{
skip_2_0:;
int arg_2_0_0 = Jwlistcons(varN,Jwlistcons(varM,Jwlistcons(ano_2,Jwlistcons(Jwcons(Jmakepred("s"),Jwcons(ano_1,NIL,th),th),NIL,th),th),th),th);
retry_2_0_0:;
Jpush_recur(th);
if (c_quot(arg_2_0_0,NIL,th) == YES){
Jpop_recur(th);
return(YES);
}
}
clause_2_1:
Jrelease(th);
allfail:
Jdiscard_recur(th);
if(rest != NIL) Jdiscard_conj(th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("dnd"),arglist);
return(NO);}
static int c_df(int arglist, int rest, int th){
int arg1,arg2,varM,varN,ano_1,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
arglist = Jprepare(arglist,th);
Jpredname("df");
if(n == 2){
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
clause = Jget_choice(th);
switch(clause){
case 0: goto clause_2_0;
case 10000: goto skip_2_0;
case 1: goto clause_2_1;
case 10001: goto skip_2_1;
default: goto allfail;
}
clause_2_0:
ano_1 = Jmakevariant(th);
Jinc_choice(th);
if(Junify(arg1,Jwcons(Jmakepred("s"),Jwcons(Jmakeint(0),NIL,th),th),th) == YES && Junify_var(arg2,ano_1,th) == YES)
{
skip_2_0:
Jsuccess(arglist,th); return(YES);}
clause_2_1:
Jrelease(th);
varM = Jmakevariant(th);
varN = Jmakevariant(th);
Jinc_choice(th);
if(Junify(arg1,Jwcons(Jmakepred("s"),Jwcons(Jwcons(Jmakepred("s"),Jwcons(varM,NIL,th),th),NIL,th),th),th) == YES && Junify_var(arg2,varN,th) == YES)
{
skip_2_1:;
int arg_2_1_0 = Jwlistcons(Jwcons(Jmakepred("s"),Jwcons(Jwcons(Jmakepred("s"),Jwcons(varM,NIL,th),th),NIL,th),th),Jwlistcons(varN,NIL,th),th);
retry_2_1_0:;
Jpush_recur(th);
if (c_dnd(arg_2_1_0,NIL,th) == YES){
Jpop_recur(th);
int arg_2_1_1 = Jwlistcons(Jwcons(Jmakepred("s"),Jwcons(varM,NIL,th),th),Jwlistcons(varN,NIL,th),th);
retry_2_1_1:;
Jpush_recur(th);
if (c_df(arg_2_1_1,NIL,th) == YES){
Jpop_recur(th);
return(YES);
}else{Jset_mode(RETRY,th);
goto retry_2_1_0;}
}
}
clause_2_2:
Jrelease(th);
allfail:
Jdiscard_recur(th);
if(rest != NIL) Jdiscard_conj(th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("df"),arglist);
return(NO);}
static int c_prime(int arglist, int rest, int th){
int arg1,varX,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
arglist = Jprepare(arglist,th);
Jpredname("prime");
if(n == 1){
arg1 = Jcar(arglist);
clause = Jget_choice(th);
switch(clause){
case 0: goto clause_1_0;
case 10000: goto skip_1_0;
default: goto allfail;
}
clause_1_0:
varX = Jmakevariant(th);
Jinc_choice(th);
if(Junify(arg1,Jwcons(Jmakepred("s"),Jwcons(varX,NIL,th),th),th) == YES)
{
skip_1_0:;
int arg_1_0_0 = Jwlistcons(varX,Jwlistcons(Jwcons(Jmakepred("s"),Jwcons(varX,NIL,th),th),NIL,th),th);
retry_1_0_0:;
Jpush_recur(th);
if (c_df(arg_1_0_0,NIL,th) == YES){
Jpop_recur(th);
return(YES);
}
}
clause_1_1:
Jrelease(th);
allfail:
Jdiscard_recur(th);
if(rest != NIL) Jdiscard_conj(th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("prime"),arglist);
return(NO);}
static int c_apptest1(int arglist, int rest, int th){
int varX,varY,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
arglist = Jprepare(arglist,th);
Jpredname("apptest1");
if(n == 0){
clause = Jget_choice(th);
switch(clause){
case 0: goto clause_0_0;
case 10000: goto skip_0_0;
default: goto allfail;
}
clause_0_0:
varX = Jmakevariant(th);
varY = Jmakevariant(th);
Jinc_choice(th);
{
skip_0_0:;
int arg_0_0_0 = Jwlistcons(varX,Jwlistcons(varY,Jwlistcons(Jwlistcons(Jmakeint(1),Jwlistcons(Jmakeint(2),Jwlistcons(Jmakeint(3),Jwlistcons(Jmakeint(4),Jwlistcons(Jmakeint(5),Jwlistcons(Jmakeint(6),Jwlistcons(Jmakeint(7),Jwlistcons(Jmakeint(8),Jwlistcons(Jmakeint(9),Jwlistcons(Jmakeint(0),NIL,th),th),th),th),th),th),th),th),th),th),NIL,th),th),th);
retry_0_0_0:;
Jpush_recur(th);
if (c_mappend(arg_0_0_0,NIL,th) == YES){
Jpop_recur(th);
Jset_mode(RETRY,th);
goto retry_0_0_0;
return(YES);
}
}
clause_0_1:
Jrelease(th);
allfail:
Jdiscard_recur(th);
if(rest != NIL) Jdiscard_conj(th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("apptest1"),arglist);
return(NO);}
void init_tpredicate(void){
(deftpred)("mappend",c_mappend,3,6);
(deftpred)("apptest",c_apptest,0,6);
(deftpred)("nat",c_nat,1,6);
(deftpred)("plus",c_plus,3,6);
(deftpred)("times",c_times,3,6);
(deftpred)("le",c_le,2,6);
(deftpred)("lt",c_lt,2,6);
(deftpred)("quot",c_quot,4,6);
(deftpred)("dnd",c_dnd,2,6);
(deftpred)("df",c_df,2,6);
(deftpred)("prime",c_prime,1,6);
(deftpred)("apptest1",c_apptest1,0,6);
}
void init_declare(void){
int body,th; th=0;
}
static int recur_scbm(int preed, int clause, int arglist){
return(YES);
}
