#include "jump.h"
static int c_p(int arglist, int rest, int th);
static int c_p(int arglist, int rest, int th){
int arg1,n,body,save1,save2,save3,goal,cont,clause,res;
Jinc_proof(th);
n = Jlength(arglist);
if(rest != NIL){
save1 = Jget_wp(th);
save2 = Jget_sp(th);
save3 = Jget_ac(th);
}else{
save1 = Jget_back_wp(th);
save2 = Jget_back_sp(th);
save3 = Jget_back_ac(th);
clause = Jget_back_choice(th);}
if(n == 1){
arg1 = Jnth(arglist,1);
if(rest == NIL){
clause = Jget_back_choice(th);
switch(clause){
case 0: goto clause_1_0;
case 1: goto clause_1_1;
default: goto allfail;
}}loop1:
clause_1_0:
if(rest == NIL){
Jinc_back_choice(th);
arg1 = Jnth(arglist,1);
}
if(Junify_int(arg1,Jmakeint(1),th) == YES && 1)
if(rest!=NIL){
if(Jprove_all(rest,Jget_sp(th),th) == YES) return(YES);}
else return(YES);
clause_1_1:
Jset_ac(save3,th);
Junbind(save2,th);
if(rest == NIL){
Jinc_back_choice(th);
arg1 = Jnth(arglist,1);
}
if(Junify_int(arg1,Jmakeint(2),th) == YES && 1)
if(rest!=NIL){
if(Jprove_all(rest,Jget_sp(th),th) == YES) return(YES);}
else return(YES);
clause_1_2:
Jset_ac(save3,th);
Junbind(save2,th);
allfail:
Jpop_back(th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("p"),arglist);
return(NO);}
static int c_foo(int arglist, int rest, int th);
static int c_foo(int arglist, int rest, int th){
int varX,varY,n,body,save1,save2,save3,goal,cont,clause,res;
Jinc_proof(th);
n = Jlength(arglist);
if(rest != NIL){
save1 = Jget_wp(th);
save2 = Jget_sp(th);
save3 = Jget_ac(th);
}else{
save1 = Jget_back_wp(th);
save2 = Jget_back_sp(th);
save3 = Jget_back_ac(th);
clause = Jget_back_choice(th);}
if(n == 0){
if(rest == NIL){
clause = Jget_back_choice(th);
switch(clause){
case 0: goto clause_0_0;
case 1: goto clause_0_1;
default: goto allfail;
}}loop0:
clause_0_0:
varX = Jmakevariant(th);
varY = Jmakevariant(th);
if(rest == NIL){
Jinc_back_choice(th);
}
int arg_0_0_0 = Jwlistcons(varX,NIL,th);
int arg_0_0_1 = Jwlistcons(varY,NIL,th);
int arg_0_0_2 = Jwlistcons(varX,NIL,th);
int arg_0_0_3 = Jwlistcons(varY,NIL,th);
int arg_0_0_4 = NIL;
Jpush_back(th);
retry_0_0_0:
if (c_p(arg_0_0_0,NIL,th) == YES){
Jpush_back(th);
retry_0_0_1:
if (c_p(arg_0_0_1,NIL,th) == YES){
if (Jcall_det(Jmakesys("write"),Jwlistcons(varX,NIL,th),th) == YES){
if (Jcall_det(Jmakesys("write"),Jwlistcons(varY,NIL,th),th) == YES){
goto retry_0_0_1;
}else goto retry_0_0_1;
}else goto retry_0_0_1;
}else goto retry_0_0_0;
}
clause_0_1:
Jset_ac(save3,th);
Junbind(save2,th);
if(rest == NIL){
Jinc_back_choice(th);
}
if(rest!=NIL){
return(Jprove_all(rest,Jget_sp(th),th));}
else return(YES);
allfail:
Jpop_back(th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("foo"),arglist);
return(NO);}
static int c_n(int arglist, int rest, int th);
static int c_n(int arglist, int rest, int th){
int arg1,n,body,save1,save2,save3,goal,cont,clause,res;
Jinc_proof(th);
n = Jlength(arglist);
if(rest != NIL){
save1 = Jget_wp(th);
save2 = Jget_sp(th);
save3 = Jget_ac(th);
}else{
save1 = Jget_back_wp(th);
save2 = Jget_back_sp(th);
save3 = Jget_back_ac(th);
clause = Jget_back_choice(th);}
if(n == 1){
arg1 = Jnth(arglist,1);
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
}}loop1:
clause_1_0:
if(rest == NIL){
Jinc_back_choice(th);
arg1 = Jnth(arglist,1);
}
if(Junify_int(arg1,Jmakeint(1),th) == YES && 1)
if(rest!=NIL){
if(Jprove_all(rest,Jget_sp(th),th) == YES) return(YES);}
else return(YES);
clause_1_1:
Jset_ac(save3,th);
Junbind(save2,th);
if(rest == NIL){
Jinc_back_choice(th);
arg1 = Jnth(arglist,1);
}
if(Junify_int(arg1,Jmakeint(2),th) == YES && 1)
if(rest!=NIL){
if(Jprove_all(rest,Jget_sp(th),th) == YES) return(YES);}
else return(YES);
clause_1_2:
Jset_ac(save3,th);
Junbind(save2,th);
if(rest == NIL){
Jinc_back_choice(th);
arg1 = Jnth(arglist,1);
}
if(Junify_int(arg1,Jmakeint(3),th) == YES && 1)
if(rest!=NIL){
if(Jprove_all(rest,Jget_sp(th),th) == YES) return(YES);}
else return(YES);
clause_1_3:
Jset_ac(save3,th);
Junbind(save2,th);
if(rest == NIL){
Jinc_back_choice(th);
arg1 = Jnth(arglist,1);
}
if(Junify_int(arg1,Jmakeint(4),th) == YES && 1)
if(rest!=NIL){
if(Jprove_all(rest,Jget_sp(th),th) == YES) return(YES);}
else return(YES);
clause_1_4:
Jset_ac(save3,th);
Junbind(save2,th);
if(rest == NIL){
Jinc_back_choice(th);
arg1 = Jnth(arglist,1);
}
if(Junify_int(arg1,Jmakeint(5),th) == YES && 1)
if(rest!=NIL){
if(Jprove_all(rest,Jget_sp(th),th) == YES) return(YES);}
else return(YES);
clause_1_5:
Jset_ac(save3,th);
Junbind(save2,th);
if(rest == NIL){
Jinc_back_choice(th);
arg1 = Jnth(arglist,1);
}
if(Junify_int(arg1,Jmakeint(6),th) == YES && 1)
if(rest!=NIL){
if(Jprove_all(rest,Jget_sp(th),th) == YES) return(YES);}
else return(YES);
clause_1_6:
Jset_ac(save3,th);
Junbind(save2,th);
if(rest == NIL){
Jinc_back_choice(th);
arg1 = Jnth(arglist,1);
}
if(Junify_int(arg1,Jmakeint(7),th) == YES && 1)
if(rest!=NIL){
if(Jprove_all(rest,Jget_sp(th),th) == YES) return(YES);}
else return(YES);
clause_1_7:
Jset_ac(save3,th);
Junbind(save2,th);
if(rest == NIL){
Jinc_back_choice(th);
arg1 = Jnth(arglist,1);
}
if(Junify_int(arg1,Jmakeint(8),th) == YES && 1)
if(rest!=NIL){
if(Jprove_all(rest,Jget_sp(th),th) == YES) return(YES);}
else return(YES);
clause_1_8:
Jset_ac(save3,th);
Junbind(save2,th);
if(rest == NIL){
Jinc_back_choice(th);
arg1 = Jnth(arglist,1);
}
if(Junify_int(arg1,Jmakeint(9),th) == YES && 1)
if(rest!=NIL){
if(Jprove_all(rest,Jget_sp(th),th) == YES) return(YES);}
else return(YES);
clause_1_9:
Jset_ac(save3,th);
Junbind(save2,th);
if(rest == NIL){
Jinc_back_choice(th);
arg1 = Jnth(arglist,1);
}
if(Junify_int(arg1,Jmakeint(10),th) == YES && 1)
if(rest!=NIL){
if(Jprove_all(rest,Jget_sp(th),th) == YES) return(YES);}
else return(YES);
clause_1_10:
Jset_ac(save3,th);
Junbind(save2,th);
allfail:
Jpop_back(th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("n"),arglist);
return(NO);}
static int c_bench(int arglist, int rest, int th);
static int c_bench(int arglist, int rest, int th){
int varX,varY,varZ,varA,varB,n,body,save1,save2,save3,goal,cont,clause,res;
Jinc_proof(th);
n = Jlength(arglist);
if(rest != NIL){
save1 = Jget_wp(th);
save2 = Jget_sp(th);
save3 = Jget_ac(th);
}else{
save1 = Jget_back_wp(th);
save2 = Jget_back_sp(th);
save3 = Jget_back_ac(th);
clause = Jget_back_choice(th);}
if(n == 0){
if(rest == NIL){
clause = Jget_back_choice(th);
switch(clause){
case 0: goto clause_0_0;
case 1: goto clause_0_1;
default: goto allfail;
}}loop0:
clause_0_0:
varX = Jmakevariant(th);
varY = Jmakevariant(th);
varZ = Jmakevariant(th);
varA = Jmakevariant(th);
varB = Jmakevariant(th);
if(rest == NIL){
Jinc_back_choice(th);
}
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
clause_0_1:
Jset_ac(save3,th);
Junbind(save2,th);
if(rest == NIL){
Jinc_back_choice(th);
}
if(rest!=NIL){
return(Jprove_all(rest,Jget_sp(th),th));}
else return(YES);
allfail:
Jpop_back(th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("bench"),arglist);
return(NO);}
static int c_bench1(int arglist, int rest, int th);
static int c_bench1(int arglist, int rest, int th){
int varX,varY,varZ,n,body,save1,save2,save3,goal,cont,clause,res;
Jinc_proof(th);
n = Jlength(arglist);
if(rest != NIL){
save1 = Jget_wp(th);
save2 = Jget_sp(th);
save3 = Jget_ac(th);
}else{
save1 = Jget_back_wp(th);
save2 = Jget_back_sp(th);
save3 = Jget_back_ac(th);
clause = Jget_back_choice(th);}
if(n == 0){
if(rest == NIL){
clause = Jget_back_choice(th);
switch(clause){
case 0: goto clause_0_0;
case 1: goto clause_0_1;
default: goto allfail;
}}loop0:
clause_0_0:
varX = Jmakevariant(th);
varY = Jmakevariant(th);
varZ = Jmakevariant(th);
if(rest == NIL){
Jinc_back_choice(th);
}
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
clause_0_1:
Jset_ac(save3,th);
Junbind(save2,th);
if(rest == NIL){
Jinc_back_choice(th);
}
if(rest!=NIL){
return(Jprove_all(rest,Jget_sp(th),th));}
else return(YES);
allfail:
Jpop_back(th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("bench1"),arglist);
return(NO);}
static int c_nodiag(int arglist, int rest, int th);
static int c_nodiag(int arglist, int rest, int th){
int arg1,arg2,arg3,varD1,varN,varL,varB,varD,ano_2,ano_1,n,body,save1,save2,save3,goal,cont,clause,res;
Jinc_proof(th);
n = Jlength(arglist);
if(rest != NIL){
save1 = Jget_wp(th);
save2 = Jget_sp(th);
save3 = Jget_ac(th);
}else{
save1 = Jget_back_wp(th);
save2 = Jget_back_sp(th);
save3 = Jget_back_ac(th);
clause = Jget_back_choice(th);}
if(n == 3){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
if(rest == NIL){
clause = Jget_back_choice(th);
switch(clause){
case 0: goto clause_3_0;
case 1: goto clause_3_1;
default: goto allfail;
}}loop3:
clause_3_0:
ano_2 = Jmakevariant(th);
ano_1 = Jmakevariant(th);
if(rest == NIL){
Jinc_back_choice(th);
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
}
if(Junify_nil(arg1,th) == YES && Junify_var(arg2,ano_2,th) == YES && Junify_var(arg3,ano_1,th) == YES && 1)
if(rest!=NIL){
if(Jprove_all(rest,Jget_sp(th),th) == YES) return(YES);}
else return(YES);
clause_3_1:
Jset_ac(save3,th);
Junbind(save2,th);
varD1 = Jmakevariant(th);
varN = Jmakevariant(th);
varL = Jmakevariant(th);
varB = Jmakevariant(th);
varD = Jmakevariant(th);
if(rest == NIL){
Jinc_back_choice(th);
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
}
if(Junify_pair(arg1,Jwlistcons(varN,varL,th),th) == YES && Junify_var(arg2,varB,th) == YES && Junify_var(arg3,varD,th) == YES && 1)
if(Jnot_numeqp(Jderef(varD,th),Jminus(Jderef(varN,th),Jderef(varB,th),th)) && Jinc_proof(th))if(Jnot_numeqp(Jderef(varD,th),Jminus(Jderef(varB,th),Jderef(varN,th),th)) && Jinc_proof(th))if(Junify(varD1,Jplus(Jderef(varD,th),Jmakeint(1),th),th)==YES && Jinc_proof(th)){
arg1 = Jcopy_work(Jderef(varL,th),th);
arg2 = Jcopy_work(Jderef(varB,th),th);
arg3 = Jcopy_work(Jderef(varD1,th),th);
Junbind(save2,th);
Jset_ac(save3,th);
goto loop3;
}
allfail:
Jpop_back(th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("nodiag"),arglist);
return(NO);}
void init_tpredicate(void){(deftpred)("p",c_p,1,2);
(deftpred)("foo",c_foo,1,2);
(deftpred)("n",c_n,1,2);
(deftpred)("bench",c_bench,1,2);
(deftpred)("bench1",c_bench1,1,2);
(deftpred)("nodiag",c_nodiag,1,2);
}
void init_declare(void){int body,th; th=0;
}