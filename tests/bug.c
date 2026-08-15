#include "jump.h"
static int c_mbetween(int arglist, int rest, int th);
static int user_scbm(int pred, int arity, int clause, int arglist, int rest, int th);
static int c_mbetween(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Ssave_arg(arglist,th);
return(user_scbm(0,n,0,arglist,rest,th));
}

void init_tpredicate(void){
(deftpred)("mbetween",c_mbetween,3,1);
(deftpred)("append",c_append,3,1);
}
void init_declare(void){
int body,th; th=0;
}
static int user_scbm(int pred, int arity, int clause, int arglist, int rest, int th){
void *next;
int arg1,arg2,arg3,arg4,arg5,aeg6,arg7,arg8,arg9,arg10,subr_number,varX_,varY_,varZ_,varA_,varA,varX,varY,varZ;
np[th] = 0; rp[th] = 0; back_stack[0][AC_SCBM][th] = Jget_ac(th);
Spush_next(&&success,th);
switch(pred){
case 0: goto test;
case 1: goto mappend;
case 2: goto plus;
case 3: goto times;
case 4: goto color;
case 5: goto reverse;
case 6: goto append30;
case 7: goto list30;
case 8: goto bench1;
case 9: goto n;
case 10: goto bench;
case 11: goto test2;
case 12: goto nat;
case 13: goto le;
case 14: goto lt;
case 15: goto quot;
case 16: goto dnd;
case 17: goto df;
case 18: goto prime;
case 19: goto foo;
case 20: goto apptest;
case 21: goto apptest1;
case 22: goto likes;
case 23: goto mbetween;
}
test:
switch(arity){
case 3: goto test_3;
default: goto allfail;
}
mappend:
switch(arity){
case 3: goto mappend_3;
default: goto allfail;
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
color:
switch(arity){
case 1: goto color_1;
default: goto allfail;
}
reverse:
switch(arity){
case 2: goto reverse_2;
default: goto allfail;
}
append30:
switch(arity){
case 1: goto append30_1;
default: goto allfail;
}
list30:
switch(arity){
case 1: goto list30_1;
default: goto allfail;
}
bench1:
switch(arity){
case 0: goto bench1_0;
default: goto allfail;
}
n:
switch(arity){
case 1: goto n_1;
default: goto allfail;
}
bench:
switch(arity){
case 0: goto bench_0;
default: goto allfail;
}
test2:
switch(arity){
case 1: goto test2_1;
default: goto allfail;
}
nat:
switch(arity){
case 1: goto nat_1;
default: goto allfail;
}
le:
switch(arity){
case 2: goto le_2;
default: goto allfail;
}
lt:
switch(arity){
case 2: goto lt_2;
default: goto allfail;
}
quot:
switch(arity){
case 4: goto quot_4;
default: goto allfail;
}
dnd:
switch(arity){
case 2: goto dnd_2;
default: goto allfail;
}
df:
switch(arity){
case 2: goto df_2;
default: goto allfail;
}
prime:
switch(arity){
case 1: goto prime_1;
default: goto allfail;
}
foo:
switch(arity){
case 3: goto foo_3;
default: goto allfail;
}
apptest:
switch(arity){
case 0: goto apptest_0;
default: goto allfail;
}
apptest1:
switch(arity){
case 0: goto apptest1_0;
default: goto allfail;
}
likes:
switch(arity){
case 2: goto likes_2;
default: goto allfail;
}
mbetween:
switch(arity){
case 3: goto mbetween_3;
default: goto allfail;
}
test_3:
Jinc_proof(th);
switch(clause){
case 0: goto test_3_0;
default: goto allfail;
}
mappend_3:
Jinc_proof(th);
switch(clause){
case 0: goto mappend_3_0;
default: goto allfail;
}
plus_3:
Jinc_proof(th);
switch(clause){
case 0: goto plus_3_0;
default: goto allfail;
}
times_3:
Jinc_proof(th);
switch(clause){
case 0: goto times_3_0;
default: goto allfail;
}
color_1:
Jinc_proof(th);
switch(clause){
case 0: goto color_1_0;
default: goto allfail;
}
reverse_2:
Jinc_proof(th);
switch(clause){
case 0: goto reverse_2_0;
default: goto allfail;
}
append30_1:
Jinc_proof(th);
switch(clause){
case 0: goto append30_1_0;
default: goto allfail;
}
list30_1:
Jinc_proof(th);
switch(clause){
case 0: goto list30_1_0;
default: goto allfail;
}
bench1_0:
Jinc_proof(th);
switch(clause){
case 0: goto bench1_0_0;
default: goto allfail;
}
n_1:
Jinc_proof(th);
switch(clause){
case 0: goto n_1_0;
default: goto allfail;
}
bench_0:
Jinc_proof(th);
switch(clause){
case 0: goto bench_0_0;
default: goto allfail;
}
test2_1:
Jinc_proof(th);
switch(clause){
case 0: goto test2_1_0;
default: goto allfail;
}
nat_1:
Jinc_proof(th);
switch(clause){
case 0: goto nat_1_0;
default: goto allfail;
}
le_2:
Jinc_proof(th);
switch(clause){
case 0: goto le_2_0;
default: goto allfail;
}
lt_2:
Jinc_proof(th);
switch(clause){
case 0: goto lt_2_0;
default: goto allfail;
}
quot_4:
Jinc_proof(th);
switch(clause){
case 0: goto quot_4_0;
default: goto allfail;
}
dnd_2:
Jinc_proof(th);
switch(clause){
case 0: goto dnd_2_0;
default: goto allfail;
}
df_2:
Jinc_proof(th);
switch(clause){
case 0: goto df_2_0;
default: goto allfail;
}
prime_1:
Jinc_proof(th);
switch(clause){
case 0: goto prime_1_0;
default: goto allfail;
}
foo_3:
Jinc_proof(th);
switch(clause){
case 0: goto foo_3_0;
default: goto allfail;
}
apptest_0:
Jinc_proof(th);
switch(clause){
case 0: goto apptest_0_0;
default: goto allfail;
}
apptest1_0:
Jinc_proof(th);
switch(clause){
case 0: goto apptest1_0_0;
default: goto allfail;
}
likes_2:
Jinc_proof(th);
switch(clause){
case 0: goto likes_2_0;
default: goto allfail;
}
mbetween_3:
Jinc_proof(th);
switch(clause){
case 0: goto mbetween_3_0;
case 1: goto mbetween_3_1;
case 2: goto mbetween_3_2;
default: goto allfail;
}
test_3_0:
Sreset_back(th);
goto allfail;

mappend_3_0:
Sreset_back(th);
goto allfail;

plus_3_0:
Sreset_back(th);
goto allfail;

times_3_0:
Sreset_back(th);
goto allfail;

color_1_0:
Sreset_back(th);
goto allfail;

reverse_2_0:
Sreset_back(th);
goto allfail;

append30_1_0:
Sreset_back(th);
goto allfail;

list30_1_0:
Sreset_back(th);
goto allfail;

bench1_0_0:
Sreset_back(th);
goto allfail;

n_1_0:
Sreset_back(th);
goto allfail;

bench_0_0:
Sreset_back(th);
goto allfail;

test2_1_0:
Sreset_back(th);
goto allfail;

nat_1_0:
Sreset_back(th);
goto allfail;

le_2_0:
Sreset_back(th);
goto allfail;

lt_2_0:
Sreset_back(th);
goto allfail;

quot_4_0:
Sreset_back(th);
goto allfail;

dnd_2_0:
Sreset_back(th);
goto allfail;

df_2_0:
Sreset_back(th);
goto allfail;

prime_1_0:
Sreset_back(th);
goto allfail;

foo_3_0:
Sreset_back(th);
goto allfail;

apptest_0_0:
Sreset_back(th);
goto allfail;

apptest1_0_0:
Sreset_back(th);
goto allfail;

likes_2_0:
Sreset_back(th);
goto allfail;

mbetween_3_0:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
Srelease(th);
varY = Jmakevariant(th);
varX = Jmakevariant(th);
Sinc_choice(th);
Sset_back(&&mbetween_3_1,th);
if(Junify_var(arg1,varX,th) == YES && Junify_var(arg2,varY,th) == YES && Junify_var(arg3,varX,th) == YES)
{
mbetween_3_0_0:
arglist = Jwlistcons(varX,Jwlistcons(varY,NIL,th),th);
next_stack[np[th]+1][1][th] = varY;
next_stack[np[th]+1][2][th] = varX;
Spush_next(&&mbetween_3_0_1,th);subr_number = 88;
goto builtin_call;
mbetween_3_0_1:
goto success;
}
mbetween_3_1:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
Srelease(th);
varA = Jmakevariant(th);
varX = Jmakevariant(th);
varY = Jmakevariant(th);
varZ = Jmakevariant(th);
Sinc_choice(th);
Sset_back(&&mbetween_3_2,th);
if(Junify_var(arg1,varX,th) == YES && Junify_var(arg2,varY,th) == YES && Junify_var(arg3,varZ,th) == YES)
{
mbetween_3_1_0:
arglist = Jwlistcons(varX,Jwlistcons(varY,NIL,th),th);
next_stack[np[th]+1][1][th] = varA;
next_stack[np[th]+1][2][th] = varX;
next_stack[np[th]+1][3][th] = varY;
next_stack[np[th]+1][4][th] = varZ;
Spush_next(&&mbetween_3_1_1,th);
subr_number = 77;
goto builtin_call;
mbetween_3_1_1:
varA= next_stack[np[th]+1][1][th];
varX= next_stack[np[th]+1][2][th];
varY= next_stack[np[th]+1][3][th];
varZ= next_stack[np[th]+1][4][th];
arglist = Jwlistcons(varA,Jwlistcons(Jwcons(2179,Jwcons(varX,Jwcons(Jmakeint(1),NIL,th),th),th),NIL,th),th);
next_stack[np[th]+1][1][th] = varA;
next_stack[np[th]+1][2][th] = varX;
next_stack[np[th]+1][3][th] = varY;
next_stack[np[th]+1][4][th] = varZ;
Spush_next(&&mbetween_3_1_2,th);
subr_number = 187;
goto builtin_call;
mbetween_3_1_2:
varA= next_stack[np[th]+1][1][th];
varX= next_stack[np[th]+1][2][th];
varY= next_stack[np[th]+1][3][th];
varZ= next_stack[np[th]+1][4][th];
arglist = Jwlistcons(varA,Jwlistcons(varY,Jwlistcons(varZ,NIL,th),th),th);
goto mbetween_3_1_2join;
mbetween_3_1_2back:
varA= next_stack[np[th]+1][1][th];
varX= next_stack[np[th]+1][2][th];
varY= next_stack[np[th]+1][3][th];
varZ= next_stack[np[th]+1][4][th];
mbetween_3_1_2join:
next_stack[np[th]+1][1][th] = varA;
next_stack[np[th]+1][2][th] = varX;
next_stack[np[th]+1][3][th] = varY;
next_stack[np[th]+1][4][th] = varZ;
Spush_next(&&mbetween_3_1_3,th);
clause = Sget_choice(th);
goto mbetween_3;
mbetween_3_1_3:
goto success;
}
mbetween_3_2:
Sreset_back(th);
goto allfail;

success:
if(np[th] == 0){
if(Jprove_all(rest,Jget_sp(th),th) == YES) return(YES);
next = back_goto[rp[th]][th];
clause = Sget_choice(th);
arglist = Sget_arg(th);
Spush_next(&&success,th);
goto *next;
}else{
next = next_goto[np[th]][th];
Spop_next(th);
clause = Sget_choice(th);
goto *next;}
allfail:
if(rp[th]==0) {return(NO);}
next = back_goto[rp[th]][th];
np[th] = Sget_np(th);
Spop_back(th);
arglist = Sget_arg(th);
goto *next;
builtin_call:
if(Jcallsubr(subr_number,arglist,NIL,th) == YES)
goto success;
else goto allfail;
#include "scbm.h"
}
