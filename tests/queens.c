#include "jump.h"
static int b_test16(int arglist, int rest, int th);
static int b_test16(int arglist, int rest, int th){
int varX,n,body,save1,save2,save3,goal,cont,clause,res;
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
Jset_ac(save3,th);
Junbind(save2,th);
clause = Jget_back_choice(th);
switch(clause){
case 0: goto clause_0_0;
default: goto allfail;
}}loop0:
clause_0_0:
varX = Jmakevariant(th);
if(rest == NIL){
Jinc_back_choice(th);
}
if (Jcall_det(Jmakesys("between"),Jwlistcons(Jmakeint(1),Jwlistcons(Jmakeint(16),Jwlistcons(varX,NIL,th),th),th),th) == YES){
Jpush_back(Jget_sp(th),0,Jget_wp(th),Jget_ac(th),th);
retry_0_0_1:
if (Jcall_nondet(Jmakecomp("test1"),NIL,th) == YES){
if (Jcall_det(Jmakesys("fail"),NIL,th) == YES){
return(YES);}else goto retry_0_0_1;
}
}
allfail:
Jpop_back(th);
Jset_wp(save1,th);
Junbind(save2,th);
Jset_ac(save3,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("test16"),arglist);
return(NO);}
static int b_test(int arglist, int rest, int th);
static int b_test(int arglist, int rest, int th){
int varX,n,body,save1,save2,save3,goal,cont,clause,res;
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
Jset_ac(save3,th);
Junbind(save2,th);
clause = Jget_back_choice(th);
switch(clause){
case 0: goto clause_0_0;
default: goto allfail;
}}loop0:
clause_0_0:
varX = Jmakevariant(th);
if(rest == NIL){
Jinc_back_choice(th);
}
Jpush_back(Jget_sp(th),0,Jget_wp(th),Jget_ac(th),th);
retry_0_0_0:
if (Jcall_nondet(Jmakecomp("queen"),Jwlistcons(Jwlistcons(Jmakeint(1),Jwlistcons(Jmakeint(2),Jwlistcons(Jmakeint(3),Jwlistcons(Jmakeint(4),Jwlistcons(Jmakeint(5),Jwlistcons(Jmakeint(6),Jwlistcons(Jmakeint(7),Jwlistcons(Jmakeint(8),Jwlistcons(Jmakeint(9),NIL,th),th),th),th),th),th),th),th),th),Jwlistcons(varX,NIL,th),th),th) == YES){
if (Jcall_det(Jmakesys("write"),Jwlistcons(varX,NIL,th),th) == YES){
if (Jcall_det(Jmakesys("nl"),NIL,th) == YES){
if (Jcall_det(Jmakesys("fail"),NIL,th) == YES){
return(YES);}else goto retry_0_0_0;
}else goto retry_0_0_0;
}else goto retry_0_0_0;
}
allfail:
Jpop_back(th);
Jset_wp(save1,th);
Junbind(save2,th);
Jset_ac(save3,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("test"),arglist);
return(NO);}
static int b_test1(int arglist, int rest, int th);
static int b_test1(int arglist, int rest, int th){
int varX,n,body,save1,save2,save3,goal,cont,clause,res;
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
Jset_ac(save3,th);
Junbind(save2,th);
clause = Jget_back_choice(th);
switch(clause){
case 0: goto clause_0_0;
default: goto allfail;
}}loop0:
clause_0_0:
varX = Jmakevariant(th);
if(rest == NIL){
Jinc_back_choice(th);
}
Jpush_back(Jget_sp(th),0,Jget_wp(th),Jget_ac(th),th);
retry_0_0_0:
if (Jcall_nondet(Jmakecomp("queen"),Jwlistcons(Jwlistcons(Jmakeint(1),Jwlistcons(Jmakeint(2),Jwlistcons(Jmakeint(3),Jwlistcons(Jmakeint(4),Jwlistcons(Jmakeint(5),Jwlistcons(Jmakeint(6),Jwlistcons(Jmakeint(7),Jwlistcons(Jmakeint(8),Jwlistcons(Jmakeint(9),NIL,th),th),th),th),th),th),th),th),th),Jwlistcons(varX,NIL,th),th),th) == YES){
if (Jcall_det(Jmakesys("fail"),NIL,th) == YES){
return(YES);}else goto retry_0_0_0;
}
allfail:
Jpop_back(th);
Jset_wp(save1,th);
Junbind(save2,th);
Jset_ac(save3,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("test1"),arglist);
return(NO);}
static int b_queen(int arglist, int rest, int th);
static int b_queen(int arglist, int rest, int th){
int arg1,arg2,varData,varOut,n,body,save1,save2,save3,goal,cont,clause,res;
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
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
if(rest == NIL){
Jset_ac(save3,th);
Junbind(save2,th);
clause = Jget_back_choice(th);
switch(clause){
case 0: goto clause_2_0;
default: goto allfail;
}}loop2:
clause_2_0:
varData = Jmakevariant(th);
varOut = Jmakevariant(th);
if(rest == NIL){
Jinc_back_choice(th);
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
}
if(Junify_var(arg1,varData,th) == YES && Junify_var(arg2,varOut,th) == YES && 1)
Jmakeconst("varOut"),th) == YES && 1)
