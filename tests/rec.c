#include "jump.h"
static int c_nat(int arglist, int rest, int th);
static int c_plus(int arglist, int rest, int th);
static int c_times(int arglist, int rest, int th);
static int c_le(int arglist, int rest, int th);
static int c_lt(int arglist, int rest, int th);
static int c_quot(int arglist, int rest, int th);
static int c_dnd(int arglist, int rest, int th);
static int c_df(int arglist, int rest, int th);
static int c_prime(int arglist, int rest, int th);
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
skip_1_0:
{Jsave_arg(arglist,th); return(YES);}
clause_1_1:
Jrelease(th);
varX = Jmakevariant(th);
Jinc_choice(th);
if(Junify(arg1,Jwcons(Jmakepred("s"),Jwcons(varX,NIL,th),th),th) == YES)
{
skip_1_1:
int arg_1_1_0 = Jwlistcons(varX,NIL,th);
Jpush_back(th);
retry_1_1_0:
if (c_nat(arg_1_1_0,NIL,th) == YES){
Jcopy_back(th);
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
skip_3_0:
{Jsave_arg(arglist,th); return(YES);}
clause_3_1:
Jrelease(th);
varX = Jmakevariant(th);
varY = Jmakevariant(th);
varZ = Jmakevariant(th);
Jinc_choice(th);
if(Junify(arg1,Jwcons(Jmakepred("s"),Jwcons(varX,NIL,th),th),th) == YES && Junify_var(arg2,varY,th) == YES && Junify(arg3,Jwcons(Jmakepred("s"),Jwcons(varZ,NIL,th),th),th) == YES)
{
skip_3_1:
int arg_3_1_0 = Jwlistcons(varX,Jwlistcons(varY,Jwlistcons(varZ,NIL,th),th),th);
Jpush_back(th);
retry_3_1_0:
if (c_plus(arg_3_1_0,NIL,th) == YES){
Jcopy_back(th);
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
skip_3_0:
{Jsave_arg(arglist,th); return(YES);}
clause_3_1:
Jrelease(th);
varZ1 = Jmakevariant(th);
varX = Jmakevariant(th);
varY = Jmakevariant(th);
varZ = Jmakevariant(th);
Jinc_choice(th);
if(Junify(arg1,Jwcons(Jmakepred("s"),Jwcons(varX,NIL,th),th),th) == YES && Junify_var(arg2,varY,th) == YES && Junify_var(arg3,varZ,th) == YES)
{
skip_3_1:
int arg_3_1_0 = Jwlistcons(varX,Jwlistcons(varY,Jwlistcons(varZ1,NIL,th),th),th);
int arg_3_1_1 = Jwlistcons(varZ1,Jwlistcons(varY,Jwlistcons(varZ,NIL,th),th),th);
Jpush_back(th);
retry_3_1_0:
if (c_times(arg_3_1_0,NIL,th) == YES){
Jpush_back(th);
retry_3_1_1:
if (c_plus(arg_3_1_1,NIL,th) == YES){
Jcopy_back(th);
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
skip_2_0:
int arg_2_0_0 = Jwlistcons(varX,Jwlistcons(ano_1,Jwlistcons(varY,NIL,th),th),th);
Jpush_back(th);
retry_2_0_0:
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
skip_2_0:
int arg_2_0_0 = Jwlistcons(Jwcons(Jmakepred("s"),Jwcons(varX,NIL,th),th),Jwlistcons(varY,NIL,th),th);
Jpush_back(th);
retry_2_0_0:
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
skip_4_0:
int arg_4_0_0 = Jwlistcons(varX,Jwlistcons(varY,NIL,th),th);
Jpush_back(th);
retry_4_0_0:
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
skip_4_1:
int arg_4_1_0 = Jwlistcons(varY,Jwlistcons(varX1,Jwlistcons(varX,NIL,th),th),th);
int arg_4_1_1 = Jwlistcons(varX1,Jwlistcons(varY,Jwlistcons(varQ,Jwlistcons(varR,NIL,th),th),th),th);
Jpush_back(th);
retry_4_1_0:
if (c_plus(arg_4_1_0,NIL,th) == YES){
Jpush_back(th);
retry_4_1_1:
if (c_quot(arg_4_1_1,NIL,th) == YES){
Jcopy_back(th);
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
skip_2_0:
int arg_2_0_0 = Jwlistcons(varN,Jwlistcons(varM,Jwlistcons(ano_2,Jwlistcons(Jwcons(Jmakepred("s"),Jwcons(ano_1,NIL,th),th),NIL,th),th),th),th);
Jpush_back(th);
retry_2_0_0:
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
skip_2_0:
{Jsave_arg(arglist,th); return(YES);}
clause_2_1:
Jrelease(th);
varM = Jmakevariant(th);
varN = Jmakevariant(th);
Jinc_choice(th);
if(Junify(arg1,Jwcons(Jmakepred("s"),Jwcons(Jwcons(Jmakepred("s"),Jwcons(varM,NIL,th),th),NIL,th),th),th) == YES && Junify_var(arg2,varN,th) == YES)
{
skip_2_1:
int arg_2_1_0 = Jwlistcons(Jwcons(Jmakepred("s"),Jwcons(Jwcons(Jmakepred("s"),Jwcons(varM,NIL,th),th),NIL,th),th),Jwlistcons(varN,NIL,th),th);
int arg_2_1_1 = Jwlistcons(Jwcons(Jmakepred("s"),Jwcons(varM,NIL,th),th),Jwlistcons(varN,NIL,th),th);
Jpush_back(th);
retry_2_1_0:
if (c_dnd(arg_2_1_0,NIL,th) == YES){
Jpush_back(th);
retry_2_1_1:
if (c_df(arg_2_1_1,NIL,th) == YES){
Jcopy_back(th);
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
skip_1_0:
int arg_1_0_0 = Jwlistcons(varX,Jwlistcons(Jwcons(Jmakepred("s"),Jwcons(varX,NIL,th),th),NIL,th),th);
Jpush_back(th);
retry_1_0_0:
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
void init_tpredicate(void){
(deftpred)("nat",c_nat,1,1);
(deftpred)("plus",c_plus,3,1);
(deftpred)("times",c_times,3,1);
(deftpred)("le",c_le,2,1);
(deftpred)("lt",c_lt,2,1);
(deftpred)("quot",c_quot,4,1);
(deftpred)("dnd",c_dnd,2,1);
(deftpred)("df",c_df,2,1);
(deftpred)("prime",c_prime,1,1);
}
void init_declare(void){
int body,th; th=0;
}