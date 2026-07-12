#include "jump.h"
static int c_skip_test(int arglist, int rest, int th);
static int c_test16(int arglist, int rest, int th);
static int c_test(int arglist, int rest, int th);
static int c_test1(int arglist, int rest, int th);
static int c_queen(int arglist, int rest, int th);
static int c_queen_2(int arglist, int rest, int th);
static int c_qdelete(int arglist, int rest, int th);
static int c_nodiag(int arglist, int rest, int th);
static int c_skip_test(int arglist, int rest, int th){
int arg1,arg2,varX,varY,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
arglist = Jprepare(arglist,th);
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
int arg_2_0_0 = Jwlistcons(varX,Jwlistcons(Jmakeint(1),Jwlistcons(Jwlistcons(Jmakeint(2),Jwlistcons(Jmakeint(4),NIL,th),th),Jwlistcons(varY,NIL,th),th),th),th);
Jpush_recur(th);
retry_2_0_0:;
if (c_qdelete(arg_2_0_0,NIL,th) == YES){
Jpop_recur(th);
Jpush_tail_recur(th);
if (Jcall_det(Jmakecomp("nodiag"),Jwlistcons(Jwlistcons(Jmakeint(2),Jwlistcons(Jmakeint(4),NIL,th),th),Jwlistcons(varX,Jwlistcons(Jmakeint(1),NIL,th),th),th),th) == YES){
Jpop_tail_recur(th);
return(YES);
}else{Jset_mode(RETRY,th);
goto retry_2_0_0;}
}
}
clause_2_1:
Jrelease(th);
allfail:
Jdiscard_recur(th);
if(rest != NIL) Jdiscard_conj(th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("skip_test"),arglist);
return(NO);}
static int c_test16(int arglist, int rest, int th){
int varX,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
if(n == 0){
clause = Jget_choice(th);
switch(clause){
case 0: goto clause_0_0;
case 10000: goto skip_0_0;
default: goto allfail;
}
clause_0_0:
varX = Jmakevariant(th);
Jinc_choice(th);
{
skip_0_0:;
if (Jcall_det(Jmakesys("between"),Jwlistcons(Jmakeint(1),Jwlistcons(Jmakeint(16),Jwlistcons(varX,NIL,th),th),th),th) == YES){
Jpush_conj(th);
retry_0_0_1:;
int arg_0_0_1 = NIL;
if (c_test1(arg_0_0_1,NIL,th) == YES){
goto retry_0_0_1;
{Jsuccess(arglist,th); return(YES);}
}
}
}
clause_0_1:
Jrelease(th);
allfail:
Jdiscard_conj(th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("test16"),arglist);
return(NO);}
static int c_test(int arglist, int rest, int th){
int varX,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
if(n == 0){
clause = Jget_choice(th);
switch(clause){
case 0: goto clause_0_0;
case 10000: goto skip_0_0;
default: goto allfail;
}
clause_0_0:
varX = Jmakevariant(th);
Jinc_choice(th);
{
skip_0_0:;
int arg_0_0_0 = Jwlistcons(Jwlistcons(Jmakeint(1),Jwlistcons(Jmakeint(2),Jwlistcons(Jmakeint(3),Jwlistcons(Jmakeint(4),Jwlistcons(Jmakeint(5),Jwlistcons(Jmakeint(6),Jwlistcons(Jmakeint(7),Jwlistcons(Jmakeint(8),Jwlistcons(Jmakeint(9),NIL,th),th),th),th),th),th),th),th),th),Jwlistcons(varX,NIL,th),th);
Jpush_recur(th);
retry_0_0_0:;
if (c_queen(arg_0_0_0,NIL,th) == YES){
Jpop_recur(th);
if (Jcall_det(Jmakesys("write"),Jwlistcons(varX,NIL,th),th) == YES){
if (Jcall_det(Jmakesys("nl"),NIL,th) == YES){
goto retry_0_0_0;
return(YES);
}else goto retry_0_0_0;
}else goto retry_0_0_0;
}
}
clause_0_1:
Jrelease(th);
allfail:
Jdiscard_conj(th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("test"),arglist);
return(NO);}
static int c_test1(int arglist, int rest, int th){
int varX,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
if(n == 0){
clause = Jget_choice(th);
switch(clause){
case 0: goto clause_0_0;
case 10000: goto skip_0_0;
default: goto allfail;
}
clause_0_0:
varX = Jmakevariant(th);
Jinc_choice(th);
{
skip_0_0:;
int arg_0_0_0 = Jwlistcons(Jwlistcons(Jmakeint(1),Jwlistcons(Jmakeint(2),Jwlistcons(Jmakeint(3),Jwlistcons(Jmakeint(4),Jwlistcons(Jmakeint(5),Jwlistcons(Jmakeint(6),Jwlistcons(Jmakeint(7),Jwlistcons(Jmakeint(8),Jwlistcons(Jmakeint(9),NIL,th),th),th),th),th),th),th),th),th),Jwlistcons(varX,NIL,th),th);
Jpush_recur(th);
retry_0_0_0:;
if (c_queen(arg_0_0_0,NIL,th) == YES){
Jpop_recur(th);
goto retry_0_0_0;
return(YES);
}
}
clause_0_1:
Jrelease(th);
allfail:
Jdiscard_conj(th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("test1"),arglist);
return(NO);}
static int c_queen(int arglist, int rest, int th){
int arg1,arg2,varData,varOut,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
arglist = Jprepare(arglist,th);
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
varData = Jmakevariant(th);
varOut = Jmakevariant(th);
Jinc_choice(th);
if(Junify_var(arg1,varData,th) == YES && Junify_var(arg2,varOut,th) == YES)
{
skip_2_0:;
int arg_2_0_0 = Jwlistcons(varData,Jwlistcons(NIL,Jwlistcons(varOut,NIL,th),th),th);
Jpush_recur(th);
retry_2_0_0:;
if (c_queen_2(arg_2_0_0,NIL,th) == YES){
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

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("queen"),arglist);
return(NO);}
static int c_queen_2(int arglist, int rest, int th){
int arg1,arg2,arg3,varL1,varH,varT,varHistory,varQ,varM,ano_1,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
arglist = Jprepare(arglist,th);
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
if(Junify_nil(arg1,th) == YES && Junify_var(arg2,ano_1,th) == YES && Junify_nil(arg3,th) == YES)
{
skip_3_0:
Jsuccess(arglist,th); return(YES);}
clause_3_1:
Jrelease(th);
varL1 = Jmakevariant(th);
varH = Jmakevariant(th);
varT = Jmakevariant(th);
varHistory = Jmakevariant(th);
varQ = Jmakevariant(th);
varM = Jmakevariant(th);
Jinc_choice(th);
if(Junify_pair(arg1,Jwlistcons(varH,varT,th),th) == YES && Junify_var(arg2,varHistory,th) == YES && Junify_pair(arg3,Jwlistcons(varQ,varM,th),th) == YES)
{
skip_3_1:;
if (Jcall_det(Jmakesys("write"),Jwlistcons(Jwlistcons(varH,varT,th),NIL,th),th) == YES){
int arg_3_1_1 = Jwlistcons(varQ,Jwlistcons(varH,Jwlistcons(varT,Jwlistcons(varL1,NIL,th),th),th),th);
Jpush_recur(th);
retry_3_1_1:;
if (c_qdelete(arg_3_1_1,NIL,th) == YES){
Jpop_recur(th);
Jpush_tail_recur(th);
if (Jcall_det(Jmakecomp("nodiag"),Jwlistcons(varHistory,Jwlistcons(varQ,Jwlistcons(Jmakeint(1),NIL,th),th),th),th) == YES){
Jpop_tail_recur(th);
int arg_3_1_3 = Jwlistcons(varL1,Jwlistcons(Jwlistcons(varQ,varHistory,th),Jwlistcons(varM,NIL,th),th),th);
Jpush_recur(th);
retry_3_1_3:;
if (c_queen_2(arg_3_1_3,NIL,th) == YES){
Jpop_recur(th);
return(YES);
}else{Jset_mode(RETRY,th);
goto retry_3_1_1;}
}else{Jset_mode(RETRY,th);
goto retry_3_1_1;}
}
}
}
clause_3_2:
Jrelease(th);
allfail:
Jdiscard_recur(th);
if(rest != NIL) Jdiscard_conj(th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("queen_2"),arglist);
return(NO);}
static int c_qdelete(int arglist, int rest, int th){
int arg1,arg2,arg3,arg4,varX,varH,varT,varR,varA,varL,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
arglist = Jprepare(arglist,th);
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
varA = Jmakevariant(th);
varL = Jmakevariant(th);
Jinc_choice(th);
if(Junify_var(arg1,varA,th) == YES && Junify_var(arg2,varA,th) == YES && Junify_var(arg3,varL,th) == YES && Junify_var(arg4,varL,th) == YES)
{
skip_4_0:
Jsuccess(arglist,th); return(YES);}
clause_4_1:
Jrelease(th);
varX = Jmakevariant(th);
varH = Jmakevariant(th);
varT = Jmakevariant(th);
varA = Jmakevariant(th);
varR = Jmakevariant(th);
Jinc_choice(th);
if(Junify_var(arg1,varX,th) == YES && Junify_var(arg2,varA,th) == YES && Junify_pair(arg3,Jwlistcons(varH,varT,th),th) == YES && Junify_pair(arg4,Jwlistcons(varA,varR,th),th) == YES)
{
skip_4_1:;
int arg_4_1_0 = Jwlistcons(varX,Jwlistcons(varH,Jwlistcons(varT,Jwlistcons(varR,NIL,th),th),th),th);
Jpush_recur(th);
retry_4_1_0:;
if (c_qdelete(arg_4_1_0,NIL,th) == YES){
Jpop_recur(th);
return(YES);
}
}
clause_4_2:
Jrelease(th);
allfail:
Jdiscard_recur(th);
if(rest != NIL) Jdiscard_conj(th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("qdelete"),arglist);
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
(deftpred)("skip_test",c_skip_test,2,6);
(deftpred)("test16",c_test16,0,1);
(deftpred)("test",c_test,0,1);
(deftpred)("test1",c_test1,0,1);
(deftpred)("queen",c_queen,2,6);
(deftpred)("queen_2",c_queen_2,3,6);
(deftpred)("qdelete",c_qdelete,4,6);
(deftpred)("nodiag",c_nodiag,3,3);
}
void init_declare(void){
int body,th; th=0;
}