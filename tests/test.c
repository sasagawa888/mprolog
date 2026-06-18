#include "jump.h"
static int c_uoo(int arglist, int rest, int th);
static int c_bar(int arglist, int rest, int th);
static int c_boo(int arglist, int rest, int th);
static int c_foo(int arglist, int rest, int th);
static int c_uoo(int arglist, int rest, int th){
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
static int c_bar(int arglist, int rest, int th){
int arg1,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
arglist = Jprepare(arglist,th);
if(n == 1){
arg1 = Jcar(arglist);
if(rest == NIL){
clause = Jget_back_choice(th);
switch(clause){
case 0: goto clause_1_0;
case 1: goto clause_1_1;
default: goto allfail;
}}
clause_1_0:
Jinc_choice(th);
if(Junify(arg1,Jmakeint(1),th) == YES)
{return(YES);}
clause_1_1:
Jrelease(th);
Jinc_choice(th);
if(Junify(arg1,Jmakeint(2),th) == YES)
{return(YES);}
clause_1_2:
Jrelease(th);
allfail:
Jdiscard(th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("bar"),arglist);
return(NO);}
void boo(void){
dynamic_clause = Jcons(26,Jcons(Jcons(Jmakepred("boo"),Jcons(Jmakevar("varX"),NIL)),Jcons(Jcons(1204,Jcons(Jmakevar("varX"),NIL)),NIL)));
Jadd_dynamic(dynamic_clause);
}static int c_foo(int arglist, int rest, int th){
int arg1,varX1,varX,n,body,save1,save2,save3,goal,cont,clause,res;
save1 = Jget_wp(th);
save2 = Jget_sp(th);
save3 = Jget_ac(th);
Jinc_proof(th);
n = Jarity_count(arglist);
if(n == 1){
arg1 = Jcar(arglist);
loop1:
if(Junify_int(arg1,Jmakeint(0),th) == YES)
if(Jprove_all(rest,Jget_sp(th),th) == YES) return(YES);
varX1 = Jmakevariant(th);
varX = Jmakevariant(th);
if(Junify_var(arg1,varX,th) == YES)
if (Jcall_det(Jmakesys("write"),Jwcons(varX,NIL,th),th) == YES)if(Junify(varX1,Jminus(Jderef(varX,th),Jmakeint(1),th),th)==YES){
arg1 = Jcopy_work(Jderef(varX1,th),th);
Junbind(save2,th);
Jset_ac(save3,th);
goto loop1;
}
return(NO);}
}
void init_tpredicate(void){
(deftpred)("uoo",c_uoo,1,2);
(deftpred)("bar",c_bar,1,1);
(deftpred)("foo",c_foo,1,3);
}
void init_declare(void){
int body,th; th=0;
boo();
body = Jcons(1568,Jcons(Jcons(52,Jcons(Jmakepred("boo"),Jcons(Jmakeint(1),NIL))),NIL));
Jprove_all(body,Jget_sp(th),th);
}