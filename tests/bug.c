#include "jump.h"
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
static int recur_scbm(int pred, int clause, int arglist);
static int c_mappend(int arglist, int rest, int th){
int arg1,arg2,arg3,varY,varA,varZ,varX,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
arglist = Jprepare(arglist,th);
Jpredname("mappend");
if(n == 3){
return(recur_scbm(0,1,arglist));
}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("mappend"),arglist);
return(NO);}
static int c_apptest(int arglist, int rest, int th){
int varX,varY,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
arglist = Jprepare(arglist,th);
Jpredname("apptest");
if(n == 0){
return(recur_scbm(0,1,arglist));
}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("apptest"),arglist);
return(NO);}
static int c_nat(int arglist, int rest, int th){
int arg1,varX,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
arglist = Jprepare(arglist,th);
Jpredname("nat");
if(n == 1){
return(recur_scbm(0,1,arglist));
}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("nat"),arglist);
return(NO);}
static int c_plus(int arglist, int rest, int th){
int arg1,arg2,arg3,varX,varZ,varY,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
arglist = Jprepare(arglist,th);
Jpredname("plus");
if(n == 3){
return(recur_scbm(0,1,arglist));
}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("plus"),arglist);
return(NO);}
static int c_times(int arglist, int rest, int th){
int arg1,arg2,arg3,varZ1,varX,varY,varZ,ano_1,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
arglist = Jprepare(arglist,th);
Jpredname("times");
if(n == 3){
return(recur_scbm(0,1,arglist));
}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("times"),arglist);
return(NO);}
static int c_le(int arglist, int rest, int th){
int arg1,arg2,ano_1,varX,varY,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
arglist = Jprepare(arglist,th);
Jpredname("le");
if(n == 2){
return(recur_scbm(0,1,arglist));
}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("le"),arglist);
return(NO);}
static int c_lt(int arglist, int rest, int th){
int arg1,arg2,varX,varY,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
arglist = Jprepare(arglist,th);
Jpredname("lt");
if(n == 2){
return(recur_scbm(0,1,arglist));
}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("lt"),arglist);
return(NO);}
static int c_quot(int arglist, int rest, int th){
int arg1,arg2,arg3,arg4,varX1,varQ,varR,varY,varX,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
arglist = Jprepare(arglist,th);
Jpredname("quot");
if(n == 4){
return(recur_scbm(0,1,arglist));
}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("quot"),arglist);
return(NO);}
static int c_dnd(int arglist, int rest, int th){
int arg1,arg2,ano_2,ano_1,varM,varN,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
arglist = Jprepare(arglist,th);
Jpredname("dnd");
if(n == 2){
return(recur_scbm(0,1,arglist));
}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("dnd"),arglist);
return(NO);}
static int c_df(int arglist, int rest, int th){
int arg1,arg2,varM,varN,ano_1,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
arglist = Jprepare(arglist,th);
Jpredname("df");
if(n == 2){
return(recur_scbm(0,1,arglist));
}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("df"),arglist);
return(NO);}
static int c_prime(int arglist, int rest, int th){
int arg1,varX,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
arglist = Jprepare(arglist,th);
Jpredname("prime");
if(n == 1){
return(recur_scbm(0,1,arglist));
}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("prime"),arglist);
return(NO);}
static int c_apptest1(int arglist, int rest, int th){
int varX,varY,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
arglist = Jprepare(arglist,th);
Jpredname("apptest1");
if(n == 0){
return(recur_scbm(0,1,arglist));
}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("apptest1"),arglist);
return(NO);}
void init_tpredicate(void){
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
static int recur_scbm(int preed, int clause, int arglist){
return(YES);
}
