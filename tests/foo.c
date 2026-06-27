#include "jump.h"
static int c_p(int arglist, int rest, int th);
static int c_p(int arglist, int rest, int th){
int arg1,n,body,save1,save2,save3,goal,cont,clause,res;
n = Jarity_count(arglist);
arglist = Sprepare(arglist,th);
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
Jsave_arg(arglist,th); return(YES);}
clause_1_1:
Srelease(th);
Jinc_choice(th);
if(Junify_int(arg1,Jmakeint(2),th) == YES)
{
skip_1_1:;
Jsave_arg(arglist,th); return(YES);}
clause_1_2:
Srelease(th);
Jinc_choice(th);
if(Junify_int(arg1,Jmakeint(3),th) == YES)
{
skip_1_2:;
Jsave_arg(arglist,th); return(YES);}
clause_1_3:
Srelease(th);
allfail:
Sdiscard(th);
return(NO);}

Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("p"),arglist);
return(NO);}
void init_tpredicate(void){
(deftpred)("p",c_p,1,1);
}
void init_declare(void){
int body,th; th=0;
}