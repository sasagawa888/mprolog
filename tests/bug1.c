#include "jump.h"
static int c_color(int arglist, int rest, int th);
static int recur_scbm(int pred, int arity, int clause, int arglist, int rest, int th);
static int c_color(int arglist, int rest, int th){
int arg1,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
if(n == 1){
arg1 = Jcar(arglist);
clause = Jget_choice(th);
switch(clause){
case 0: goto clause_1_0;
case 1: goto clause_1_1;
case 2: goto clause_1_2;
default: goto allfail;
}
clause_1_0:
Jinc_choice(th);
if(Junify_atom(arg1,Jmakeconst("red"),th) == YES)
return(YES);
clause_1_1:
Jrelease(th);
Jinc_choice(th);
if(Junify_atom(arg1,Jmakeconst("green"),th) == YES)
return(YES);
clause_1_2:
Jrelease(th);
Jinc_choice(th);
if(Junify_atom(arg1,Jmakeconst("blue"),th) == YES)
return(YES);
clause_1_3:
Jrelease(th);
allfail:
Jdiscard_conj(th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("color"),arglist);
return(NO);

}
void init_tpredicate(void){
(deftpred)("color",c_color,1,1);
}
void init_declare(void){
int body,th; th=0;
}
static int recur_scbm(int pred, int arity, int clause, int arglist, int rest, int th){
void *next;
int arg1,arg2,arg3,arg4,arg5,aeg6,arg7,arg8,arg9,arg10;
np[Jget_scp(CONJ,th)][th] = 0; vp[th] = 0;
Jpush_next(&&success,th);
switch(pred){
case 0: goto plus;
case 1: goto times;
}
plus:
switch(arity){
case 3: goto plus_3;
default: goto allfail;
}
times:
switch(arity){
case 3: goto times_3;
default: goto allfail;
}
plus_3:
switch(clause){
default: goto allfail;
}
times_3:
switch(clause){
default: goto allfail;
}
plus_3_0:
Jpop_back(th);
goto allfail;

times_3_0:
Jpop_back(th);
goto allfail;

success:
if(np[Jget_scp(CONJ,th)][th] == 0){
if(Jprove_all(rest,Jget_sp(th),th) == YES) return(YES);
next = back_stack[Jget_scp(RECUR,th)][Jget_scp(CONJ,th)][th];
clause = Jget_choice(th);
arglist = Jget_arg(th);
Jpush_next(&&success,th);
goto *next;
}else{
next = next_stack[np[Jget_scp(CONJ,th)][th]][Jget_scp(CONJ,th)][th];
Jpop_next(th);
clause = Jget_choice(th);
goto *next;}
allfail:
if(Jget_scp(RECUR,th)==0) {Jdiscard_conj(th); return(NO);}
next = back_stack[Jget_scp(RECUR,th)][Jget_scp(CONJ,th)][th];
Jpop_recur(th);
Jpop_next(th);
clause = Jget_choice(th);
arglist = Jget_arg(th);
vp[th] = Jget_vp(th);
np[Jget_scp(CONJ,th)][th] = Jget_np(th);
goto *next;
}
