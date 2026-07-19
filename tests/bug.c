#include "jump.h"
static int c_mappend(int arglist, int rest, int th);
static int c_n(int arglist, int rest, int th);
static int c_bench(int arglist, int rest, int th);
static int recur_scbm(int pred, int arity, int clause, int arglist, int th);
static int c_mappend(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
return(recur_scbm(0,n,Jget_choice(th),arglist,th));
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
return(NO);}
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
return(NO);}
void init_tpredicate(void){
(deftpred)("mappend",c_mappend,3,6);
(deftpred)("n",c_n,1,1);
(deftpred)("bench",c_bench,0,1);
}
void init_declare(void){
int body,th; th=0;
}
static int recur_scbm(int pred, int arity, int clause, int arglist, int th){
void *next;
int index,arg1,arg2,arg3,arg4,arg5,aeg6,arg7,arg8,arg9,arg10,varA,varX,varY,varZ;
np[Jget_scp(CONJ,th)][th] = 0;
switch(pred){
case 0: goto mappend;
}
mappend:
switch(arity){
case 3: goto mappend_3;
}
mappend_3:
switch(clause){
case 0: goto mappend_3_0;
case 1: goto mappend_3_1;
default: goto allfail;
}
mappend_3_0:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
varX = Jmakevariant(th);
Jinc_choice(th);
if(Junify_nil(arg1,th) == YES && Junify_var(arg2,varX,th) == YES && Junify_var(arg3,varX,th) == YES)
{
goto success;
}
Jrelease(th);
mappend_3_1:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
varX = Jmakevariant(th);
varY = Jmakevariant(th);
varA = Jmakevariant(th);
varZ = Jmakevariant(th);
Jinc_choice(th);
if(Junify_pair(arg1,Jwlistcons(varA,varX,th),th) == YES && Junify_var(arg2,varY,th) == YES && Junify_pair(arg3,Jwlistcons(varA,varZ,th),th) == YES)
{
arglist = Jwlistcons(varX,Jwlistcons(varY,Jwlistcons(varZ,NIL,th),th),th);
mappend_3_1_0:
Jpush_recur(NIL,th);
Jpush_next(&&mappend_3_1_1,th);
Jget_choice(th);
goto mappend_3;
mappend_3_1_1:
goto success;
}
Jrelease(th);
goto allfail;

success:
if(np[Jget_scp(CONJ,th)][th] == 0) return(YES);
else{
next = next_stack[np[Jget_scp(CONJ,th)][th]][Jget_scp(CONJ,th)][th];
Jpop_next(th);
goto *next;}
allfail:
Jpop_recur(th);
Jpop_next(th);
index = Jget_cont(th);
if(index == 0) {
next = next_clause[th];
if(next == NIL) return(NO);
goto *next;
}
else{
next = next_stack[index][Jget_scp(CONJ,th)][th];
Jset_mode(1,th);
clause = Jget_choice(th);
goto *next;}
}
