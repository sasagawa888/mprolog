#include "jump.h"
static int c_n(int arglist, int rest, int th);
static int c_bench(int arglist, int rest, int th);
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
static int recur_scbm(int pred, int arity, int clause, int arglist, int th);
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
static int c_mappend(int arglist, int rest, int th){
int n;
if(n == 3){
return(recur_scbm(0,3,0,arglist,th));
}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("mappend"),arglist);
return(NO);}
static int c_apptest(int arglist, int rest, int th){
int n;
if(n == 0){
return(recur_scbm(1,0,0,arglist,th));
}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("apptest"),arglist);
return(NO);}
static int c_nat(int arglist, int rest, int th){
int n;
if(n == 1){
return(recur_scbm(2,1,0,arglist,th));
}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("nat"),arglist);
return(NO);}
static int c_plus(int arglist, int rest, int th){
int n;
if(n == 3){
return(recur_scbm(3,3,0,arglist,th));
}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("plus"),arglist);
return(NO);}
static int c_times(int arglist, int rest, int th){
int n;
if(n == 3){
return(recur_scbm(4,3,0,arglist,th));
}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("times"),arglist);
return(NO);}
static int c_le(int arglist, int rest, int th){
int n;
if(n == 2){
return(recur_scbm(5,2,0,arglist,th));
}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("le"),arglist);
return(NO);}
static int c_lt(int arglist, int rest, int th){
int n;
if(n == 2){
return(recur_scbm(6,2,0,arglist,th));
}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("lt"),arglist);
return(NO);}
static int c_quot(int arglist, int rest, int th){
int n;
if(n == 4){
return(recur_scbm(7,4,0,arglist,th));
}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("quot"),arglist);
return(NO);}
static int c_dnd(int arglist, int rest, int th){
int n;
if(n == 2){
return(recur_scbm(8,2,0,arglist,th));
}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("dnd"),arglist);
return(NO);}
static int c_df(int arglist, int rest, int th){
int n;
if(n == 2){
return(recur_scbm(9,2,0,arglist,th));
}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("df"),arglist);
return(NO);}
static int c_prime(int arglist, int rest, int th){
int n;
if(n == 1){
return(recur_scbm(10,1,0,arglist,th));
}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("prime"),arglist);
return(NO);}
static int c_apptest1(int arglist, int rest, int th){
int n;
if(n == 0){
return(recur_scbm(11,0,0,arglist,th));
}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("apptest1"),arglist);
return(NO);}
void init_tpredicate(void){
(deftpred)("n",c_n,1,1);
(deftpred)("bench",c_bench,0,1);
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
static int recur_scbm(int pred, int arity, int clause, int arglist, int th){
void *next;
np[scp[CONJ][th]][th] = 0;
switch(pred){
case 0: goto apptest1;
case 1: goto prime;
case 2: goto df;
case 3: goto dnd;
case 4: goto quot;
case 5: goto lt;
case 6: goto le;
case 7: goto times;
case 8: goto plus;
case 9: goto nat;
case 10: goto apptest;
case 11: goto mappend;
}
apptest1:
switch(arity){
case 0: goto apptest1_0;
}
prime:
switch(arity){
case 1: goto prime_1;
}
df:
switch(arity){
case 2: goto df_2;
}
dnd:
switch(arity){
case 2: goto dnd_2;
}
quot:
switch(arity){
case 4: goto quot_4;
}
lt:
switch(arity){
case 2: goto lt_2;
}
le:
switch(arity){
case 2: goto le_2;
}
times:
switch(arity){
case 3: goto times_3;
}
plus:
switch(arity){
case 3: goto plus_3;
}
nat:
switch(arity){
case 1: goto nat_1;
}
apptest:
switch(arity){
case 0: goto apptest_0;
}
mappend:
switch(arity){
case 3: goto mappend_3;
}
apptest1_0:
switch(clause){
case 0: goto apptest1_0_0;
}
prime_1:
switch(clause){
case 0: goto prime_1_0;
}
df_2:
switch(clause){
case 0: goto df_2_0;
case 1: goto df_2_1;
}
dnd_2:
switch(clause){
case 0: goto dnd_2_0;
}
quot_4:
switch(clause){
case 0: goto quot_4_0;
case 1: goto quot_4_1;
}
lt_2:
switch(clause){
case 0: goto lt_2_0;
}
le_2:
switch(clause){
case 0: goto le_2_0;
}
times_3:
switch(clause){
case 0: goto times_3_0;
case 1: goto times_3_1;
}
plus_3:
switch(clause){
case 0: goto plus_3_0;
case 1: goto plus_3_1;
}
nat_1:
switch(clause){
case 0: goto nat_1_0;
case 1: goto nat_1_1;
}
apptest_0:
switch(clause){
case 0: goto apptest_0_0;
}
mappend_3:
switch(clause){
case 0: goto mappend_3_0;
case 1: goto mappend_3_1;
}
apptest1_0_0:
prime_1_0:
df_2_0:
df_2_1:
dnd_2_0:
quot_4_0:
quot_4_1:
lt_2_0:
le_2_0:
times_3_0:
times_3_1:
plus_3_0:
plus_3_1:
nat_1_0:
nat_1_1:
apptest_0_0:
mappend_3_0:
mappend_3_1:
success:
if(np[scp[CONJ][th]] == 0) return(YES);
else{
next = next_stack[np[scp[CONJ][th]][th]];
goto *next;}
}
