#include "jump.h"
static int c_disj(int arglist, int rest, int th);
static int c_disj(int arglist, int rest, int th){
int n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
if(rest != NIL) Jprepare(rest,th);
if(n == 0){
if(rest == NIL){
clause = Jget_back_choice(th);
switch(clause){
case 0: goto clause_0_0;
default: goto allfail;
}}clause_0_0:
Jinc_choice(th);
{
int arg_0_0_0 = Jwlistcons(Jwcons(1204,Jwcons(Jmakeconst("a"),NIL,th),th),Jwlistcons(Jwcons(1204,Jwcons(Jmakeconst("b"),NIL,th),th),NIL,th),th);
res = NIL;
int disj = Jget_disj_choice(th);
switch(disj){
case 0: goto disj_0_0_1_0;
case 1: goto disj_0_0_1_1;
default: Jreset_disj_choice(th);
goto clause_0_1;
}
disj_0_0_1_0:
Jinc_disj_choice(th);
if (Jcall_det(Jmakesys("write"),Jwlistcons(Jmakeconst("a"),NIL,th),th) == YES){
if(rest==NIL) res = YES;
else if(Jrespond(rest,th)==YES) res = YES;
}
if(res == YES) goto exit_0_0_1;

disj_0_0_1_1:
Jinc_disj_choice(th);
Jrelease(rest,th);
if (Jcall_det(Jmakesys("write"),Jwlistcons(Jmakeconst("b"),NIL,th),th) == YES){
if(rest==NIL) res = YES;
else if(Jrespond(rest,th)==YES) res = YES;
}
exit_0_0_1:
if(rest==NIL) return(YES);
else if(Jrespond(rest,th)==YES) return(YES);
if(rest!=NIL) Jreset_disj(th);
}
clause_0_1:
Jrelease(rest,th);
allfail:
Jdiscard(rest,th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("disj"),arglist);
return(NO);}
static int c_disjfail(int arglist, int rest, int th);
static int c_disjfail(int arglist, int rest, int th){
int n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
if(rest != NIL) Jprepare(rest,th);
if(n == 0){
if(rest == NIL){
clause = Jget_back_choice(th);
switch(clause){
case 0: goto clause_0_0;
default: goto allfail;
}}clause_0_0:
Jinc_choice(th);
{
int arg_0_0_0 = NIL;
int arg_0_0_1 = NIL;
Jpush_back(th);
retry_0_0_0:
if (c_disj(arg_0_0_0,NIL,th) == YES){
goto retry_0_0_0;
}
}
clause_0_1:
Jrelease(rest,th);
allfail:
Jdiscard(rest,th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("disjfail"),arglist);
return(NO);}
static int c_p(int arglist, int rest, int th);
static int c_p(int arglist, int rest, int th){
int arg1,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
if(rest != NIL) Jprepare(rest,th);
if(n == 1){
arg1 = Jcar(arglist);
if(rest == NIL){
clause = Jget_back_choice(th);
switch(clause){
case 0: goto clause_1_0;
case 1: goto clause_1_1;
case 2: goto clause_1_2;
default: goto allfail;
}}clause_1_0:
Jinc_choice(th);
if(Junify_int(arg1,Jmakeint(1),th) == YES)
if(rest==NIL) return(YES);
else if(Jrespond(rest,th)==YES) return(YES);
clause_1_1:
Jrelease(rest,th);
Jinc_choice(th);
if(Junify_int(arg1,Jmakeint(2),th) == YES)
if(rest==NIL) return(YES);
else if(Jrespond(rest,th)==YES) return(YES);
clause_1_2:
Jrelease(rest,th);
Jinc_choice(th);
if(Junify_int(arg1,Jmakeint(3),th) == YES)
if(rest==NIL) return(YES);
else if(Jrespond(rest,th)==YES) return(YES);
clause_1_3:
Jrelease(rest,th);
allfail:
Jdiscard(rest,th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("p"),arglist);
return(NO);}
static int c_cut(int arglist, int rest, int th);
static int c_cut(int arglist, int rest, int th){
int arg1,varX,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
if(rest != NIL) Jprepare(rest,th);
if(n == 1){
arg1 = Jcar(arglist);
if(rest == NIL){
clause = Jget_back_choice(th);
switch(clause){
case 0: goto clause_1_0;
default: goto allfail;
}}clause_1_0:
varX = Jmakevariant(th);
Jinc_choice(th);
if(Junify_var(arg1,varX,th) == YES)
{
int arg_1_0_0 = Jwlistcons(varX,NIL,th);
int arg_1_0_1 = NIL;
int arg_1_0_2 = Jwlistcons(varX,NIL,th);
Jpush_back(th);
retry_1_0_0:
if (c_p(arg_1_0_0,NIL,th) == YES){
if (Jcall_det(Jmakesys("write"),Jwlistcons(varX,NIL,th),th) == YES){
if(rest==NIL) return(YES);
else if(Jrespond(rest,th)==YES) return(YES);
}
}
}
clause_1_1:
Jrelease(rest,th);
allfail:
Jdiscard(rest,th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("cut"),arglist);
return(NO);}
static int c_n(int arglist, int rest, int th);
static int c_n(int arglist, int rest, int th){
int arg1,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
if(rest != NIL) Jprepare(rest,th);
if(n == 1){
arg1 = Jcar(arglist);
if(rest == NIL){
clause = Jget_back_choice(th);
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
}}clause_1_0:
Jinc_choice(th);
if(Junify_int(arg1,Jmakeint(1),th) == YES)
if(rest==NIL) return(YES);
else if(Jrespond(rest,th)==YES) return(YES);
clause_1_1:
Jrelease(rest,th);
Jinc_choice(th);
if(Junify_int(arg1,Jmakeint(2),th) == YES)
if(rest==NIL) return(YES);
else if(Jrespond(rest,th)==YES) return(YES);
clause_1_2:
Jrelease(rest,th);
Jinc_choice(th);
if(Junify_int(arg1,Jmakeint(3),th) == YES)
if(rest==NIL) return(YES);
else if(Jrespond(rest,th)==YES) return(YES);
clause_1_3:
Jrelease(rest,th);
Jinc_choice(th);
if(Junify_int(arg1,Jmakeint(4),th) == YES)
if(rest==NIL) return(YES);
else if(Jrespond(rest,th)==YES) return(YES);
clause_1_4:
Jrelease(rest,th);
Jinc_choice(th);
if(Junify_int(arg1,Jmakeint(5),th) == YES)
if(rest==NIL) return(YES);
else if(Jrespond(rest,th)==YES) return(YES);
clause_1_5:
Jrelease(rest,th);
Jinc_choice(th);
if(Junify_int(arg1,Jmakeint(6),th) == YES)
if(rest==NIL) return(YES);
else if(Jrespond(rest,th)==YES) return(YES);
clause_1_6:
Jrelease(rest,th);
Jinc_choice(th);
if(Junify_int(arg1,Jmakeint(7),th) == YES)
if(rest==NIL) return(YES);
else if(Jrespond(rest,th)==YES) return(YES);
clause_1_7:
Jrelease(rest,th);
Jinc_choice(th);
if(Junify_int(arg1,Jmakeint(8),th) == YES)
if(rest==NIL) return(YES);
else if(Jrespond(rest,th)==YES) return(YES);
clause_1_8:
Jrelease(rest,th);
Jinc_choice(th);
if(Junify_int(arg1,Jmakeint(9),th) == YES)
if(rest==NIL) return(YES);
else if(Jrespond(rest,th)==YES) return(YES);
clause_1_9:
Jrelease(rest,th);
Jinc_choice(th);
if(Junify_int(arg1,Jmakeint(10),th) == YES)
if(rest==NIL) return(YES);
else if(Jrespond(rest,th)==YES) return(YES);
clause_1_10:
Jrelease(rest,th);
allfail:
Jdiscard(rest,th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("n"),arglist);
return(NO);}
static int c_bench(int arglist, int rest, int th);
static int c_bench(int arglist, int rest, int th){
int varX,varY,varZ,varA,varB,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
if(rest != NIL) Jprepare(rest,th);
if(n == 0){
if(rest == NIL){
clause = Jget_back_choice(th);
switch(clause){
case 0: goto clause_0_0;
case 1: goto clause_0_1;
default: goto allfail;
}}clause_0_0:
varX = Jmakevariant(th);
varY = Jmakevariant(th);
varZ = Jmakevariant(th);
varA = Jmakevariant(th);
varB = Jmakevariant(th);
Jinc_choice(th);
{
int arg_0_0_0 = Jwlistcons(varX,NIL,th);
int arg_0_0_1 = Jwlistcons(varY,NIL,th);
int arg_0_0_2 = Jwlistcons(varZ,NIL,th);
int arg_0_0_3 = Jwlistcons(varA,NIL,th);
int arg_0_0_4 = Jwlistcons(varB,NIL,th);
int arg_0_0_5 = NIL;
Jpush_back(th);
retry_0_0_0:
if (c_n(arg_0_0_0,NIL,th) == YES){
Jpush_back(th);
retry_0_0_1:
if (c_n(arg_0_0_1,NIL,th) == YES){
Jpush_back(th);
retry_0_0_2:
if (c_n(arg_0_0_2,NIL,th) == YES){
Jpush_back(th);
retry_0_0_3:
if (c_n(arg_0_0_3,NIL,th) == YES){
Jpush_back(th);
retry_0_0_4:
if (c_n(arg_0_0_4,NIL,th) == YES){
goto retry_0_0_4;
}else goto retry_0_0_3;
}else goto retry_0_0_2;
}else goto retry_0_0_1;
}else goto retry_0_0_0;
}
}
clause_0_1:
Jrelease(rest,th);
Jinc_choice(th);
if(rest!=NIL){
return(Jprove_all(rest,Jget_sp(th),th));}
else return(YES);
allfail:
Jdiscard(rest,th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("bench"),arglist);
return(NO);}
static int c_bench1(int arglist, int rest, int th);
static int c_bench1(int arglist, int rest, int th){
int varX,varY,varZ,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
if(rest != NIL) Jprepare(rest,th);
if(n == 0){
if(rest == NIL){
clause = Jget_back_choice(th);
switch(clause){
case 0: goto clause_0_0;
case 1: goto clause_0_1;
default: goto allfail;
}}clause_0_0:
varX = Jmakevariant(th);
varY = Jmakevariant(th);
varZ = Jmakevariant(th);
Jinc_choice(th);
{
int arg_0_0_0 = Jwlistcons(varX,NIL,th);
int arg_0_0_1 = Jwlistcons(varY,NIL,th);
int arg_0_0_2 = Jwlistcons(varZ,NIL,th);
int arg_0_0_3 = Jwlistcons(Jwlistcons(varX,Jwlistcons(varY,Jwlistcons(varZ,NIL,th),th),th),NIL,th);
int arg_0_0_4 = NIL;
int arg_0_0_5 = NIL;
Jpush_back(th);
retry_0_0_0:
if (c_n(arg_0_0_0,NIL,th) == YES){
Jpush_back(th);
retry_0_0_1:
if (c_n(arg_0_0_1,NIL,th) == YES){
Jpush_back(th);
retry_0_0_2:
if (c_n(arg_0_0_2,NIL,th) == YES){
if (Jcall_det(Jmakesys("write"),Jwlistcons(Jwlistcons(varX,Jwlistcons(varY,Jwlistcons(varZ,NIL,th),th),th),NIL,th),th) == YES){
if (Jcall_det(Jmakesys("nl"),NIL,th) == YES){
goto retry_0_0_2;
}else goto retry_0_0_2;
}else goto retry_0_0_2;
}else goto retry_0_0_1;
}else goto retry_0_0_0;
}
}
clause_0_1:
Jrelease(rest,th);
Jinc_choice(th);
if(rest!=NIL){
return(Jprove_all(rest,Jget_sp(th),th));}
else return(YES);
allfail:
Jdiscard(rest,th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("bench1"),arglist);
return(NO);}
static int c_nodiag(int arglist, int rest, int th);
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
static int c_bar(int arglist, int rest, int th);
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
static int c_f(int arglist, int rest, int th);
static int c_f(int arglist, int rest, int th){
int arg1,arg2,varY,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
if(rest != NIL) Jprepare(rest,th);
if(n == 2){
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
if(rest == NIL){
clause = Jget_back_choice(th);
switch(clause){
case 0: goto clause_2_0;
case 1: goto clause_2_1;
default: goto allfail;
}}clause_2_0:
varY = Jmakevariant(th);
Jinc_choice(th);
if(Junify_int(arg1,Jmakeint(1),th) == YES && Junify_var(arg2,varY,th) == YES)
{
int arg_2_0_0 = Jwlistcons(varY,Jwlistcons(Jmakeint(2),NIL,th),th);
if (Jcall_det(Jmakesys("is"),Jwlistcons(varY,Jwlistcons(Jmakeint(2),NIL,th),th),th) == YES){
if(rest==NIL) return(YES);
else if(Jrespond(rest,th)==YES) return(YES);
}
}
clause_2_1:
Jrelease(rest,th);
varY = Jmakevariant(th);
Jinc_choice(th);
if(Junify_int(arg1,Jmakeint(2),th) == YES && Junify_var(arg2,varY,th) == YES)
{
int arg_2_0_0 = Jwlistcons(varY,Jwlistcons(Jmakeint(3),NIL,th),th);
if (Jcall_det(Jmakesys("is"),Jwlistcons(varY,Jwlistcons(Jmakeint(3),NIL,th),th),th) == YES){
if(rest==NIL) return(YES);
else if(Jrespond(rest,th)==YES) return(YES);
}
}
clause_2_2:
Jrelease(rest,th);
allfail:
Jdiscard(rest,th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("f"),arglist);
return(NO);}
void init_tpredicate(void){
(deftpred)("disj",c_disj,0,1);
(deftpred)("disjfail",c_disjfail,0,1);
(deftpred)("p",c_p,1,1);
(deftpred)("cut",c_cut,1,1);
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