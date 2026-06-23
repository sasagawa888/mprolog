#include "jump.h"
static int c_partition(int arglist, int rest, int th);
static int c_mmember(int arglist, int rest, int th);
static int c_nat(int arglist, int rest, int th);
static int c_plus(int arglist, int rest, int th);
static int c_times(int arglist, int rest, int th);
static int c_le(int arglist, int rest, int th);
static int c_lt(int arglist, int rest, int th);
static int c_quot(int arglist, int rest, int th);
static int c_dnd(int arglist, int rest, int th);
static int c_df(int arglist, int rest, int th);
static int c_prime(int arglist, int rest, int th);
static int c_mappend(int arglist, int rest, int th);
static int c_apptest(int arglist, int rest, int th);
static int c_apptest1(int arglist, int rest, int th);
static int c_disj(int arglist, int rest, int th);
static int c_disjtest(int arglist, int rest, int th);
static int c_p(int arglist, int rest, int th);
static int c_cut(int arglist, int rest, int th);
static int c_cuttest(int arglist, int rest, int th);
static int c_n(int arglist, int rest, int th);
static int c_bench(int arglist, int rest, int th);
static int c_bench1(int arglist, int rest, int th);
static int c_nodiag(int arglist, int rest, int th);
static int c_bar(int arglist, int rest, int th);
static int c_f(int arglist, int rest, int th);
static int c_partition(int arglist, int rest, int th){
int arg1,arg2,arg3,arg4,ano_1,varL,varY,varX,varL1,varL2,n,body,save1,save2,save3,goal,cont,clause,res;
Jinc_proof(th);
n = Jarity_count(arglist);
save1 = Jget_wp(th);
save2 = Jget_sp(th);
save3 = Jget_ac(th);
if(n == 4){
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
arg4 = Jnth(arglist,4);
varL = Jmakevariant(th);
varY = Jmakevariant(th);
varX = Jmakevariant(th);
varL1 = Jmakevariant(th);
varL2 = Jmakevariant(th);
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
arg4 = Jnth(arglist,4);
if(Junify_pair(arg1,Jwlistcons(varX,varL,th),th) == YES && Junify_var(arg2,varY,th) == YES && Junify_pair(arg3,Jwlistcons(varX,varL1,th),th) == YES && Junify_var(arg4,varL2,th) == YES)
if(Jsmallerp(Jderef(varX,th),Jderef(varY,th)))

if (Jcall_det(Jmakecomp("partition"),Jwcons(varL,Jwcons(varY,Jwcons(varL1,Jwcons(varL2,NIL,th),th),th),th),th) == YES)
return(Jprove_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
varL = Jmakevariant(th);
varY = Jmakevariant(th);
varL1 = Jmakevariant(th);
varX = Jmakevariant(th);
varL2 = Jmakevariant(th);
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
arg4 = Jnth(arglist,4);
if(Junify_pair(arg1,Jwlistcons(varX,varL,th),th) == YES && Junify_var(arg2,varY,th) == YES && Junify_var(arg3,varL1,th) == YES && Junify_pair(arg4,Jwlistcons(varX,varL2,th),th) == YES)

if (Jcall_det(Jmakecomp("partition"),Jwcons(varL,Jwcons(varY,Jwcons(varL1,Jwcons(varL2,NIL,th),th),th),th),th) == YES)
return(Jprove_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
ano_1 = Jmakevariant(th);
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
arg4 = Jnth(arglist,4);
if(Junify_nil(arg1,th) == YES && Junify_var(arg2,ano_1,th) == YES && Junify_nil(arg3,th) == YES && Junify_nil(arg4,th) == YES)

return(Jprove_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
}
static int c_mmember(int arglist, int rest, int th){
int arg1,arg2,varXs,varX,ano_1,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
arglist = Jprepare(arglist,th);
if(n == 2){
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
if(rest == NIL){
clause = Jget_back_choice(th);
switch(clause){
case 0: goto clause_2_0;
case 10000: goto skip_2_0;
case 1: goto clause_2_1;
case 10001: goto skip_2_1;
default: goto allfail;
}}
clause_2_0:
varX = Jmakevariant(th);
ano_1 = Jmakevariant(th);
Jinc_choice(th);
if(Junify_var(arg1,varX,th) == YES && Junify_pair(arg2,Jwlistcons(varX,ano_1,th),th) == YES)
{
skip_2_0:;
Jsave_arg(arglist,th); return(YES);}
clause_2_1:
Jrelease(th);
varX = Jmakevariant(th);
ano_1 = Jmakevariant(th);
varXs = Jmakevariant(th);
Jinc_choice(th);
if(Junify_var(arg1,varX,th) == YES && Junify_pair(arg2,Jwlistcons(ano_1,varXs,th),th) == YES)
{
skip_2_1:;
Jpush_back(th);
retry_2_1_0:;
int arg_2_1_0 = Jwlistcons(varX,Jwlistcons(varXs,NIL,th),th);
if (c_mmember(arg_2_1_0,NIL,th) == YES){
Jpop_back(th);
return(YES);
}
}
clause_2_2:
Jrelease(th);
allfail:
Jdiscard(th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("mmember"),arglist);
return(NO);}
static int c_nat(int arglist, int rest, int th){
int arg1,varX,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
arglist = Jprepare(arglist,th);
if(n == 1){
arg1 = Jcar(arglist);
if(rest == NIL){
clause = Jget_back_choice(th);
switch(clause){
case 0: goto clause_1_0;
case 10000: goto skip_1_0;
case 1: goto clause_1_1;
case 10001: goto skip_1_1;
default: goto allfail;
}}
clause_1_0:
Jinc_choice(th);
if(Junify_int(arg1,Jmakeint(0),th) == YES)
{
skip_1_0:;
Jsave_arg(arglist,th); return(YES);}
clause_1_1:
Jrelease(th);
varX = Jmakevariant(th);
Jinc_choice(th);
if(Junify(arg1,Jwcons(Jmakepred("s"),Jwcons(varX,NIL,th),th),th) == YES)
{
skip_1_1:;
Jpush_back(th);
retry_1_1_0:;
int arg_1_1_0 = Jwlistcons(varX,NIL,th);
if (c_nat(arg_1_1_0,NIL,th) == YES){
Jpop_back(th);
return(YES);
}
}
clause_1_2:
Jrelease(th);
allfail:
Jdiscard(th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("nat"),arglist);
return(NO);}
static int c_plus(int arglist, int rest, int th){
int arg1,arg2,arg3,varX,varZ,varY,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
arglist = Jprepare(arglist,th);
if(n == 3){
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
if(rest == NIL){
clause = Jget_back_choice(th);
switch(clause){
case 0: goto clause_3_0;
case 10000: goto skip_3_0;
case 1: goto clause_3_1;
case 10001: goto skip_3_1;
default: goto allfail;
}}
clause_3_0:
varY = Jmakevariant(th);
Jinc_choice(th);
if(Junify_int(arg1,Jmakeint(0),th) == YES && Junify_var(arg2,varY,th) == YES && Junify_var(arg3,varY,th) == YES)
{
skip_3_0:;
Jsave_arg(arglist,th); return(YES);}
clause_3_1:
Jrelease(th);
varX = Jmakevariant(th);
varY = Jmakevariant(th);
varZ = Jmakevariant(th);
Jinc_choice(th);
if(Junify(arg1,Jwcons(Jmakepred("s"),Jwcons(varX,NIL,th),th),th) == YES && Junify_var(arg2,varY,th) == YES && Junify(arg3,Jwcons(Jmakepred("s"),Jwcons(varZ,NIL,th),th),th) == YES)
{
skip_3_1:;
Jpush_back(th);
retry_3_1_0:;
int arg_3_1_0 = Jwlistcons(varX,Jwlistcons(varY,Jwlistcons(varZ,NIL,th),th),th);
if (c_plus(arg_3_1_0,NIL,th) == YES){
Jpop_back(th);
return(YES);
}
}
clause_3_2:
Jrelease(th);
allfail:
Jdiscard(th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("plus"),arglist);
return(NO);}
static int c_times(int arglist, int rest, int th){
int arg1,arg2,arg3,varZ1,varX,varY,varZ,ano_1,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
arglist = Jprepare(arglist,th);
if(n == 3){
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
if(rest == NIL){
clause = Jget_back_choice(th);
switch(clause){
case 0: goto clause_3_0;
case 10000: goto skip_3_0;
case 1: goto clause_3_1;
case 10001: goto skip_3_1;
default: goto allfail;
}}
clause_3_0:
ano_1 = Jmakevariant(th);
Jinc_choice(th);
if(Junify_int(arg1,Jmakeint(0),th) == YES && Junify_var(arg2,ano_1,th) == YES && Junify_int(arg3,Jmakeint(0),th) == YES)
{
skip_3_0:;
Jsave_arg(arglist,th); return(YES);}
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
Jpush_back(th);
retry_3_1_0:;
int arg_3_1_0 = Jwlistcons(varX,Jwlistcons(varY,Jwlistcons(varZ1,NIL,th),th),th);
if (c_times(arg_3_1_0,NIL,th) == YES){
Jpush_back(th);
retry_3_1_1:;
int arg_3_1_1 = Jwlistcons(varZ1,Jwlistcons(varY,Jwlistcons(varZ,NIL,th),th),th);
if (c_plus(arg_3_1_1,NIL,th) == YES){
Jpop_back(th);
return(YES);
}else goto retry_3_1_0;
}
}
clause_3_2:
Jrelease(th);
allfail:
Jdiscard(th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("times"),arglist);
return(NO);}
static int c_le(int arglist, int rest, int th){
int arg1,arg2,ano_1,varX,varY,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
arglist = Jprepare(arglist,th);
if(n == 2){
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
if(rest == NIL){
clause = Jget_back_choice(th);
switch(clause){
case 0: goto clause_2_0;
case 10000: goto skip_2_0;
default: goto allfail;
}}
clause_2_0:
ano_1 = Jmakevariant(th);
varX = Jmakevariant(th);
varY = Jmakevariant(th);
Jinc_choice(th);
if(Junify_var(arg1,varX,th) == YES && Junify_var(arg2,varY,th) == YES)
{
skip_2_0:;
Jpush_back(th);
retry_2_0_0:;
int arg_2_0_0 = Jwlistcons(varX,Jwlistcons(ano_1,Jwlistcons(varY,NIL,th),th),th);
if (c_plus(arg_2_0_0,NIL,th) == YES){
{Jsave_arg(arglist,th); return(YES);}
}
}
clause_2_1:
Jrelease(th);
allfail:
Jdiscard(th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("le"),arglist);
return(NO);}
static int c_lt(int arglist, int rest, int th){
int arg1,arg2,varX,varY,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
arglist = Jprepare(arglist,th);
if(n == 2){
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
if(rest == NIL){
clause = Jget_back_choice(th);
switch(clause){
case 0: goto clause_2_0;
case 10000: goto skip_2_0;
default: goto allfail;
}}
clause_2_0:
varX = Jmakevariant(th);
varY = Jmakevariant(th);
Jinc_choice(th);
if(Junify_var(arg1,varX,th) == YES && Junify_var(arg2,varY,th) == YES)
{
skip_2_0:;
Jpush_back(th);
retry_2_0_0:;
int arg_2_0_0 = Jwlistcons(Jwcons(Jmakepred("s"),Jwcons(varX,NIL,th),th),Jwlistcons(varY,NIL,th),th);
if (c_le(arg_2_0_0,NIL,th) == YES){
{Jsave_arg(arglist,th); return(YES);}
}
}
clause_2_1:
Jrelease(th);
allfail:
Jdiscard(th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("lt"),arglist);
return(NO);}
static int c_quot(int arglist, int rest, int th){
int arg1,arg2,arg3,arg4,varX1,varQ,varR,varY,varX,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
arglist = Jprepare(arglist,th);
if(n == 4){
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
arg4 = Jnth(arglist,4);
if(rest == NIL){
clause = Jget_back_choice(th);
switch(clause){
case 0: goto clause_4_0;
case 10000: goto skip_4_0;
case 1: goto clause_4_1;
case 10001: goto skip_4_1;
default: goto allfail;
}}
clause_4_0:
varY = Jmakevariant(th);
varX = Jmakevariant(th);
Jinc_choice(th);
if(Junify_var(arg1,varX,th) == YES && Junify_var(arg2,varY,th) == YES && Junify_int(arg3,Jmakeint(0),th) == YES && Junify_var(arg4,varX,th) == YES)
{
skip_4_0:;
Jpush_back(th);
retry_4_0_0:;
int arg_4_0_0 = Jwlistcons(varX,Jwlistcons(varY,NIL,th),th);
if (c_lt(arg_4_0_0,NIL,th) == YES){
{Jsave_arg(arglist,th); return(YES);}
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
Jpush_back(th);
retry_4_1_0:;
int arg_4_1_0 = Jwlistcons(varY,Jwlistcons(varX1,Jwlistcons(varX,NIL,th),th),th);
if (c_plus(arg_4_1_0,NIL,th) == YES){
Jpush_back(th);
retry_4_1_1:;
int arg_4_1_1 = Jwlistcons(varX1,Jwlistcons(varY,Jwlistcons(varQ,Jwlistcons(varR,NIL,th),th),th),th);
if (c_quot(arg_4_1_1,NIL,th) == YES){
Jpop_back(th);
return(YES);
}else goto retry_4_1_0;
}
}
clause_4_2:
Jrelease(th);
allfail:
Jdiscard(th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("quot"),arglist);
return(NO);}
static int c_dnd(int arglist, int rest, int th){
int arg1,arg2,ano_2,ano_1,varM,varN,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
arglist = Jprepare(arglist,th);
if(n == 2){
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
if(rest == NIL){
clause = Jget_back_choice(th);
switch(clause){
case 0: goto clause_2_0;
case 10000: goto skip_2_0;
default: goto allfail;
}}
clause_2_0:
ano_2 = Jmakevariant(th);
ano_1 = Jmakevariant(th);
varM = Jmakevariant(th);
varN = Jmakevariant(th);
Jinc_choice(th);
if(Junify_var(arg1,varM,th) == YES && Junify_var(arg2,varN,th) == YES)
{
skip_2_0:;
Jpush_back(th);
retry_2_0_0:;
int arg_2_0_0 = Jwlistcons(varN,Jwlistcons(varM,Jwlistcons(ano_2,Jwlistcons(Jwcons(Jmakepred("s"),Jwcons(ano_1,NIL,th),th),NIL,th),th),th),th);
if (c_quot(arg_2_0_0,NIL,th) == YES){
{Jsave_arg(arglist,th); return(YES);}
}
}
clause_2_1:
Jrelease(th);
allfail:
Jdiscard(th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("dnd"),arglist);
return(NO);}
static int c_df(int arglist, int rest, int th){
int arg1,arg2,varM,varN,ano_1,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
arglist = Jprepare(arglist,th);
if(n == 2){
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
if(rest == NIL){
clause = Jget_back_choice(th);
switch(clause){
case 0: goto clause_2_0;
case 10000: goto skip_2_0;
case 1: goto clause_2_1;
case 10001: goto skip_2_1;
default: goto allfail;
}}
clause_2_0:
ano_1 = Jmakevariant(th);
Jinc_choice(th);
if(Junify(arg1,Jwcons(Jmakepred("s"),Jwcons(Jmakeint(0),NIL,th),th),th) == YES && Junify_var(arg2,ano_1,th) == YES)
{
skip_2_0:;
Jsave_arg(arglist,th); return(YES);}
clause_2_1:
Jrelease(th);
varM = Jmakevariant(th);
varN = Jmakevariant(th);
Jinc_choice(th);
if(Junify(arg1,Jwcons(Jmakepred("s"),Jwcons(Jwcons(Jmakepred("s"),Jwcons(varM,NIL,th),th),NIL,th),th),th) == YES && Junify_var(arg2,varN,th) == YES)
{
skip_2_1:;
Jpush_back(th);
retry_2_1_0:;
int arg_2_1_0 = Jwlistcons(Jwcons(Jmakepred("s"),Jwcons(Jwcons(Jmakepred("s"),Jwcons(varM,NIL,th),th),NIL,th),th),Jwlistcons(varN,NIL,th),th);
if (c_dnd(arg_2_1_0,NIL,th) == YES){
Jpush_back(th);
retry_2_1_1:;
int arg_2_1_1 = Jwlistcons(Jwcons(Jmakepred("s"),Jwcons(varM,NIL,th),th),Jwlistcons(varN,NIL,th),th);
if (c_df(arg_2_1_1,NIL,th) == YES){
Jpop_back(th);
return(YES);
}else goto retry_2_1_0;
}
}
clause_2_2:
Jrelease(th);
allfail:
Jdiscard(th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("df"),arglist);
return(NO);}
static int c_prime(int arglist, int rest, int th){
int arg1,varX,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
arglist = Jprepare(arglist,th);
if(n == 1){
arg1 = Jcar(arglist);
if(rest == NIL){
clause = Jget_back_choice(th);
switch(clause){
case 0: goto clause_1_0;
case 10000: goto skip_1_0;
default: goto allfail;
}}
clause_1_0:
varX = Jmakevariant(th);
Jinc_choice(th);
if(Junify(arg1,Jwcons(Jmakepred("s"),Jwcons(varX,NIL,th),th),th) == YES)
{
skip_1_0:;
Jpush_back(th);
retry_1_0_0:;
int arg_1_0_0 = Jwlistcons(varX,Jwlistcons(Jwcons(Jmakepred("s"),Jwcons(varX,NIL,th),th),NIL,th),th);
if (c_df(arg_1_0_0,NIL,th) == YES){
{Jsave_arg(arglist,th); return(YES);}
}
}
clause_1_1:
Jrelease(th);
allfail:
Jdiscard(th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("prime"),arglist);
return(NO);}
static int c_mappend(int arglist, int rest, int th){
int arg1,arg2,arg3,varY,varA,varZ,varX,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
arglist = Jprepare(arglist,th);
if(n == 3){
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
if(rest == NIL){
clause = Jget_back_choice(th);
printf("clause=%d",clause);
switch(clause){
case 0: goto clause_3_0;
case 10000: goto skip_3_0;
case 1: goto clause_3_1;
case 10001: goto skip_3_1;
default: goto allfail;
}}
clause_3_0:
varX = Jmakevariant(th);
Jinc_choice(th);
if(Junify_nil(arg1,th) == YES && Junify_var(arg2,varX,th) == YES && Junify_var(arg3,varX,th) == YES)
{
skip_3_0:;
Jsave_arg(arglist,th); return(YES);}
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
Jpush_back(th);
retry_3_1_0:;
int arg_3_1_0 = Jwlistcons(varX,Jwlistcons(varY,Jwlistcons(varZ,NIL,th),th),th);
if (c_mappend(arg_3_1_0,NIL,th) == YES){
Jpop_back(th);
return(YES);
}
}
clause_3_2:
Jrelease(th);
allfail:
Jdiscard(th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("mappend"),arglist);
return(NO);}
static int c_apptest(int arglist, int rest, int th){
int varX,varY,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
arglist = Jprepare(arglist,th);
if(n == 0){
if(rest == NIL){
clause = Jget_back_choice(th);
switch(clause){
case 0: goto clause_0_0;
case 10000: goto skip_0_0;
default: goto allfail;
}}
clause_0_0:
varX = Jmakevariant(th);
varY = Jmakevariant(th);
Jinc_choice(th);
{
skip_0_0:;
Jpush_back(th);
retry_0_0_0:;
int arg_0_0_0 = Jwlistcons(varX,Jwlistcons(varY,Jwlistcons(Jwlistcons(Jmakeint(1),Jwlistcons(Jmakeint(2),Jwlistcons(Jmakeint(3),NIL,th),th),th),NIL,th),th),th);
if (c_mappend(arg_0_0_0,NIL,th) == YES){
if (Jcall_det(Jmakesys("write"),Jwlistcons(varX,NIL,th),th) == YES){
if (Jcall_det(Jmakesys("write"),Jwlistcons(varY,NIL,th),th) == YES){
goto retry_0_0_0;
{Jsave_arg(arglist,th); return(YES);}
}else goto retry_0_0_0;
}else goto retry_0_0_0;
}
}
clause_0_1:
Jrelease(th);
allfail:
Jdiscard(th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("apptest"),arglist);
return(NO);}
static int c_apptest1(int arglist, int rest, int th){
int varX,varY,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
arglist = Jprepare(arglist,th);
if(n == 0){
if(rest == NIL){
clause = Jget_back_choice(th);
switch(clause){
case 0: goto clause_0_0;
case 10000: goto skip_0_0;
default: goto allfail;
}}
clause_0_0:
varX = Jmakevariant(th);
varY = Jmakevariant(th);
Jinc_choice(th);
{
skip_0_0:;
Jpush_back(th);
retry_0_0_0:;
int arg_0_0_0 = Jwlistcons(varX,Jwlistcons(varY,Jwlistcons(Jwlistcons(Jmakeint(1),Jwlistcons(Jmakeint(2),Jwlistcons(Jmakeint(3),Jwlistcons(Jmakeint(4),Jwlistcons(Jmakeint(5),Jwlistcons(Jmakeint(6),Jwlistcons(Jmakeint(7),Jwlistcons(Jmakeint(8),Jwlistcons(Jmakeint(9),Jwlistcons(Jmakeint(0),NIL,th),th),th),th),th),th),th),th),th),th),NIL,th),th),th);
if (c_mappend(arg_0_0_0,NIL,th) == YES){
goto retry_0_0_0;
{Jsave_arg(arglist,th); return(YES);}
}
}
clause_0_1:
Jrelease(th);
allfail:
Jdiscard(th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("apptest1"),arglist);
return(NO);}
static int c_disj(int arglist, int rest, int th){
int n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
arglist = Jprepare(arglist,th);
if(n == 0){
if(rest == NIL){
clause = Jget_back_choice(th);
switch(clause){
case 0: goto clause_0_0;
case 10000: goto skip_0_0;
default: goto allfail;
}}
clause_0_0:
Jinc_choice(th);
{
skip_0_0:;
res = NIL;
int disj = Jget_disj_choice(th);
switch(disj){
case 0: goto disj_0_0_0_0;
case 1: goto disj_0_0_0_1;
default: Jreset_disj_choice(th);
goto clause_0_1;
}
disj_0_0_0_0:
Jinc_disj_choice(th);
if (Jcall_det(Jmakesys("write"),Jwlistcons(Jmakeconst("a"),NIL,th),th) == YES){
res = YES;
}
if(res == YES) goto exit_0_0_0;

disj_0_0_0_1:
Jinc_disj_choice(th);
Jrelease(th);
if (Jcall_det(Jmakesys("write"),Jwlistcons(Jmakeconst("b"),NIL,th),th) == YES){
res = YES;
}
exit_0_0_0:
{Jsave_arg(arglist,th); return(YES);}
if(rest!=NIL) Jreset_disj(th);
}
clause_0_1:
Jrelease(th);
allfail:
Jdiscard(th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("disj"),arglist);
return(NO);}
static int c_disjtest(int arglist, int rest, int th){
int n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
arglist = Jprepare(arglist,th);
if(n == 0){
if(rest == NIL){
clause = Jget_back_choice(th);
switch(clause){
case 0: goto clause_0_0;
case 10000: goto skip_0_0;
default: goto allfail;
}}
clause_0_0:
Jinc_choice(th);
{
skip_0_0:;
Jpush_back(th);
retry_0_0_0:;
int arg_0_0_0 = NIL;
if (c_disj(arg_0_0_0,NIL,th) == YES){
goto retry_0_0_0;
{Jsave_arg(arglist,th); return(YES);}
}
}
clause_0_1:
Jrelease(th);
allfail:
Jdiscard(th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("disjtest"),arglist);
return(NO);}
static int c_p(int arglist, int rest, int th){
int arg1,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
arglist = Jprepare(arglist,th);
if(n == 1){
arg1 = Jcar(arglist);
if(rest == NIL){
clause = Jget_back_choice(th);
switch(clause){
case 0: goto clause_1_0;
case 10000: goto skip_1_0;
case 1: goto clause_1_1;
case 10001: goto skip_1_1;
case 2: goto clause_1_2;
case 10002: goto skip_1_2;
default: goto allfail;
}}
clause_1_0:
Jinc_choice(th);
if(Junify_int(arg1,Jmakeint(1),th) == YES)
{
skip_1_0:;
Jsave_arg(arglist,th); return(YES);}
clause_1_1:
Jrelease(th);
Jinc_choice(th);
if(Junify_int(arg1,Jmakeint(2),th) == YES)
{
skip_1_1:;
Jsave_arg(arglist,th); return(YES);}
clause_1_2:
Jrelease(th);
Jinc_choice(th);
if(Junify_int(arg1,Jmakeint(3),th) == YES)
{
skip_1_2:;
Jsave_arg(arglist,th); return(YES);}
clause_1_3:
Jrelease(th);
allfail:
Jdiscard(th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("p"),arglist);
return(NO);}
static int c_cut(int arglist, int rest, int th){
int arg1,varX,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
arglist = Jprepare(arglist,th);
if(n == 1){
arg1 = Jcar(arglist);
if(rest == NIL){
clause = Jget_back_choice(th);
switch(clause){
case 0: goto clause_1_0;
case 10000: goto skip_1_0;
default: goto allfail;
}}
clause_1_0:
varX = Jmakevariant(th);
Jinc_choice(th);
if(Junify_var(arg1,varX,th) == YES)
{
skip_1_0:;
Jpush_back(th);
retry_1_0_0:;
int arg_1_0_0 = Jwlistcons(varX,NIL,th);
if (c_p(arg_1_0_0,NIL,th) == YES){
if (Jcall_det(Jmakesys("write"),Jwlistcons(varX,NIL,th),th) == YES){
{Jsave_arg(arglist,th); return(YES);}
}
}
}
clause_1_1:
Jrelease(th);
allfail:
Jdiscard(th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("cut"),arglist);
return(NO);}
static int c_cuttest(int arglist, int rest, int th){
int varX,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
arglist = Jprepare(arglist,th);
if(n == 0){
if(rest == NIL){
clause = Jget_back_choice(th);
switch(clause){
case 0: goto clause_0_0;
case 10000: goto skip_0_0;
default: goto allfail;
}}
clause_0_0:
varX = Jmakevariant(th);
Jinc_choice(th);
{
skip_0_0:;
Jpush_back(th);
retry_0_0_0:;
int arg_0_0_0 = Jwlistcons(varX,NIL,th);
if (c_cut(arg_0_0_0,NIL,th) == YES){
{Jsave_arg(arglist,th); return(YES);}
}
}
clause_0_1:
Jrelease(th);
allfail:
Jdiscard(th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("cuttest"),arglist);
return(NO);}
static int c_n(int arglist, int rest, int th){
int arg1,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
arglist = Jprepare(arglist,th);
if(n == 1){
arg1 = Jcar(arglist);
if(rest == NIL){
clause = Jget_back_choice(th);
switch(clause){
case 0: goto clause_1_0;
case 10000: goto skip_1_0;
case 1: goto clause_1_1;
case 10001: goto skip_1_1;
case 2: goto clause_1_2;
case 10002: goto skip_1_2;
case 3: goto clause_1_3;
case 10003: goto skip_1_3;
case 4: goto clause_1_4;
case 10004: goto skip_1_4;
case 5: goto clause_1_5;
case 10005: goto skip_1_5;
case 6: goto clause_1_6;
case 10006: goto skip_1_6;
case 7: goto clause_1_7;
case 10007: goto skip_1_7;
case 8: goto clause_1_8;
case 10008: goto skip_1_8;
case 9: goto clause_1_9;
case 10009: goto skip_1_9;
default: goto allfail;
}}
clause_1_0:
Jinc_choice(th);
if(Junify_int(arg1,Jmakeint(1),th) == YES)
{
skip_1_0:;
Jsave_arg(arglist,th); return(YES);}
clause_1_1:
Jrelease(th);
Jinc_choice(th);
if(Junify_int(arg1,Jmakeint(2),th) == YES)
{
skip_1_1:;
Jsave_arg(arglist,th); return(YES);}
clause_1_2:
Jrelease(th);
Jinc_choice(th);
if(Junify_int(arg1,Jmakeint(3),th) == YES)
{
skip_1_2:;
Jsave_arg(arglist,th); return(YES);}
clause_1_3:
Jrelease(th);
Jinc_choice(th);
if(Junify_int(arg1,Jmakeint(4),th) == YES)
{
skip_1_3:;
Jsave_arg(arglist,th); return(YES);}
clause_1_4:
Jrelease(th);
Jinc_choice(th);
if(Junify_int(arg1,Jmakeint(5),th) == YES)
{
skip_1_4:;
Jsave_arg(arglist,th); return(YES);}
clause_1_5:
Jrelease(th);
Jinc_choice(th);
if(Junify_int(arg1,Jmakeint(6),th) == YES)
{
skip_1_5:;
Jsave_arg(arglist,th); return(YES);}
clause_1_6:
Jrelease(th);
Jinc_choice(th);
if(Junify_int(arg1,Jmakeint(7),th) == YES)
{
skip_1_6:;
Jsave_arg(arglist,th); return(YES);}
clause_1_7:
Jrelease(th);
Jinc_choice(th);
if(Junify_int(arg1,Jmakeint(8),th) == YES)
{
skip_1_7:;
Jsave_arg(arglist,th); return(YES);}
clause_1_8:
Jrelease(th);
Jinc_choice(th);
if(Junify_int(arg1,Jmakeint(9),th) == YES)
{
skip_1_8:;
Jsave_arg(arglist,th); return(YES);}
clause_1_9:
Jrelease(th);
Jinc_choice(th);
if(Junify_int(arg1,Jmakeint(10),th) == YES)
{
skip_1_9:;
Jsave_arg(arglist,th); return(YES);}
clause_1_10:
Jrelease(th);
allfail:
Jdiscard(th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("n"),arglist);
return(NO);}
static int c_bench(int arglist, int rest, int th){
int varX,varY,varZ,varA,varB,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
arglist = Jprepare(arglist,th);
if(n == 0){
if(rest == NIL){
clause = Jget_back_choice(th);
switch(clause){
case 0: goto clause_0_0;
case 10000: goto skip_0_0;
case 1: goto clause_0_1;
case 10001: goto skip_0_1;
default: goto allfail;
}}
clause_0_0:
varX = Jmakevariant(th);
varY = Jmakevariant(th);
varZ = Jmakevariant(th);
varA = Jmakevariant(th);
varB = Jmakevariant(th);
Jinc_choice(th);
{
skip_0_0:;
Jpush_back(th);
retry_0_0_0:;
int arg_0_0_0 = Jwlistcons(varX,NIL,th);
if (c_n(arg_0_0_0,NIL,th) == YES){
Jpush_back(th);
retry_0_0_1:;
int arg_0_0_1 = Jwlistcons(varY,NIL,th);
if (c_n(arg_0_0_1,NIL,th) == YES){
Jpush_back(th);
retry_0_0_2:;
int arg_0_0_2 = Jwlistcons(varZ,NIL,th);
if (c_n(arg_0_0_2,NIL,th) == YES){
Jpush_back(th);
retry_0_0_3:;
int arg_0_0_3 = Jwlistcons(varA,NIL,th);
if (c_n(arg_0_0_3,NIL,th) == YES){
Jpush_back(th);
retry_0_0_4:;
int arg_0_0_4 = Jwlistcons(varB,NIL,th);
if (c_n(arg_0_0_4,NIL,th) == YES){
goto retry_0_0_4;
{Jsave_arg(arglist,th); return(YES);}
}else goto retry_0_0_3;
}else goto retry_0_0_2;
}else goto retry_0_0_1;
}else goto retry_0_0_0;
}
}
clause_0_1:
Jrelease(th);
Jinc_choice(th);
skip_0_1:;
return(YES);
allfail:
Jdiscard(th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("bench"),arglist);
return(NO);}
static int c_bench1(int arglist, int rest, int th){
int varX,varY,varZ,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
arglist = Jprepare(arglist,th);
if(n == 0){
if(rest == NIL){
clause = Jget_back_choice(th);
switch(clause){
case 0: goto clause_0_0;
case 10000: goto skip_0_0;
case 1: goto clause_0_1;
case 10001: goto skip_0_1;
default: goto allfail;
}}
clause_0_0:
varX = Jmakevariant(th);
varY = Jmakevariant(th);
varZ = Jmakevariant(th);
Jinc_choice(th);
{
skip_0_0:;
Jpush_back(th);
retry_0_0_0:;
int arg_0_0_0 = Jwlistcons(varX,NIL,th);
if (c_n(arg_0_0_0,NIL,th) == YES){
Jpush_back(th);
retry_0_0_1:;
int arg_0_0_1 = Jwlistcons(varY,NIL,th);
if (c_n(arg_0_0_1,NIL,th) == YES){
Jpush_back(th);
retry_0_0_2:;
int arg_0_0_2 = Jwlistcons(varZ,NIL,th);
if (c_n(arg_0_0_2,NIL,th) == YES){
if (Jcall_det(Jmakesys("write"),Jwlistcons(Jwlistcons(varX,Jwlistcons(varY,Jwlistcons(varZ,NIL,th),th),th),NIL,th),th) == YES){
if (Jcall_det(Jmakesys("nl"),NIL,th) == YES){
goto retry_0_0_2;
{Jsave_arg(arglist,th); return(YES);}
}else goto retry_0_0_2;
}else goto retry_0_0_2;
}else goto retry_0_0_1;
}else goto retry_0_0_0;
}
}
clause_0_1:
Jrelease(th);
Jinc_choice(th);
skip_0_1:;
return(YES);
allfail:
Jdiscard(th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("bench1"),arglist);
return(NO);}
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
if(Jprove_all(rest,Jget_sp(th),th) == YES) return(YES);
varD1 = Jmakevariant(th);
varN = Jmakevariant(th);
varL = Jmakevariant(th);
varB = Jmakevariant(th);
varD = Jmakevariant(th);
if(Junify_pair(arg1,Jwlistcons(varN,varL,th),th) == YES && Junify_var(arg2,varB,th) == YES && Junify_var(arg3,varD,th) == YES)
if(Jnot_numeqp(Jderef(varD,th),Jminus(Jderef(varN,th),Jderef(varB,th),th)))if(Jnot_numeqp(Jderef(varD,th),Jminus(Jderef(varB,th),Jderef(varN,th),th)))if(Junify(varD1,Jplus(Jderef(varD,th),Jmakeint(1),th),th)==YES){
arg1 = Jcopy_work(Jderef(varL,th),th);
arg2 = Jcopy_work(Jderef(varB,th),th);
arg3 = Jcopy_work(Jderef(varD1,th),th);
Junbind(save2,th);
Jset_ac(save3,th);
goto loop3;
}
return(NO);}
}
static int c_bar(int arglist, int rest, int th){
int arg1,varX,n,body,save1,save2,save3,goal,cont,clause,res;
Jinc_proof(th);
n = Jarity_count(arglist);
save1 = Jget_wp(th);
save2 = Jget_sp(th);
save3 = Jget_ac(th);
if(n == 1){
arg1 = Jcar(arglist);
varX = Jmakevariant(th);
arg1 = Jcar(arglist);
if(Junify_var(arg1,varX,th) == YES)
if (Jcall_det(Jmakesys("write"),Jwcons(varX,NIL,th),th) == YES)
return(Jprove_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
}
static int c_f(int arglist, int rest, int th){
int arg1,arg2,varY,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
arglist = Jprepare(arglist,th);
if(n == 2){
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
if(rest == NIL){
clause = Jget_back_choice(th);
switch(clause){
case 0: goto clause_2_0;
case 10000: goto skip_2_0;
case 1: goto clause_2_1;
case 10001: goto skip_2_1;
default: goto allfail;
}}
clause_2_0:
varY = Jmakevariant(th);
Jinc_choice(th);
if(Junify_int(arg1,Jmakeint(1),th) == YES && Junify_var(arg2,varY,th) == YES)
{
skip_2_0:;
if (Jcall_det(Jmakesys("is"),Jwlistcons(varY,Jwlistcons(Jmakeint(2),NIL,th),th),th) == YES){
{Jsave_arg(arglist,th); return(YES);}
}
}
clause_2_1:
Jrelease(th);
varY = Jmakevariant(th);
Jinc_choice(th);
if(Junify_int(arg1,Jmakeint(2),th) == YES && Junify_var(arg2,varY,th) == YES)
{
skip_2_1:;
if (Jcall_det(Jmakesys("is"),Jwlistcons(varY,Jwlistcons(Jmakeint(3),NIL,th),th),th) == YES){
{Jsave_arg(arglist,th); return(YES);}
}
}
clause_2_2:
Jrelease(th);
allfail:
Jdiscard(th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("f"),arglist);
return(NO);}
void init_tpredicate(void){
(deftpred)("partition",c_partition,4,2);
(deftpred)("mmember",c_mmember,2,1);
(deftpred)("nat",c_nat,1,1);
(deftpred)("plus",c_plus,3,1);
(deftpred)("times",c_times,3,1);
(deftpred)("le",c_le,2,1);
(deftpred)("lt",c_lt,2,1);
(deftpred)("quot",c_quot,4,1);
(deftpred)("dnd",c_dnd,2,1);
(deftpred)("df",c_df,2,1);
(deftpred)("prime",c_prime,1,1);
(deftpred)("mappend",c_mappend,3,1);
(deftpred)("apptest",c_apptest,0,1);
(deftpred)("apptest1",c_apptest1,0,1);
(deftpred)("disj",c_disj,0,1);
(deftpred)("disjtest",c_disjtest,0,1);
(deftpred)("p",c_p,1,1);
(deftpred)("cut",c_cut,1,1);
(deftpred)("cuttest",c_cuttest,0,1);
(deftpred)("n",c_n,1,1);
(deftpred)("bench",c_bench,0,1);
(deftpred)("bench1",c_bench1,0,1);
(deftpred)("nodiag",c_nodiag,3,3);
(deftpred)("bar",c_bar,1,2);
(deftpred)("f",c_f,2,1);
}
void init_declare(void){
int body,th; th=0;
}