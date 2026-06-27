#include "jump.h"
static int c_p(int arglist, int rest, int th);
static int c_mappend(int arglist, int rest, int th);
static int c_p(int arglist, int rest, int th){
int arg1,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
arglist = Jprepare(arglist,th);
if(n == 1){
arg1 = Jcar(arglist);
if(rest == NIL){
clause = Jget_choice(th);
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
Jsuccess(arglist,th); return(YES);}
clause_1_1:
Jrelease(th);
Jinc_choice(th);
if(Junify_int(arg1,Jmakeint(2),th) == YES)
{
skip_1_1:;
Jsuccess(arglist,th); return(YES);}
clause_1_2:
Jrelease(th);
Jinc_choice(th);
if(Junify_int(arg1,Jmakeint(3),th) == YES)
{
skip_1_2:;
Jsuccess(arglist,th); return(YES);}
clause_1_3:
Jrelease(th);
allfail:
Jdiscard(th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("p"),arglist);
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
clause = Jget_choice(th);
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
Jpush_recur(th);
retry_3_1_0:;
if (c_mappend(arg_3_1_0,NIL,th) == YES){
Jpop_recur(th);
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
void init_tpredicate(void){
(deftpred)("p",c_p,1,1);
(deftpred)("mappend",c_mappend,3,1);
}
void init_declare(void){
int body,th; th=0;
}