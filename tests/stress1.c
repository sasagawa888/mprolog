#include "jump.h"
static int c_color(int arglist, int rest, int th);
static int c_warm(int arglist, int rest, int th);
static int c_is_warm(int arglist, int rest, int th);
static int c_letter(int arglist, int rest, int th);
static int c_digit(int arglist, int rest, int th);
static int c_pair(int arglist, int rest, int th);
static int c_animal(int arglist, int rest, int th);
static int c_likes_milk(int arglist, int rest, int th);
static int c_milk_drinker(int arglist, int rest, int th);
static int c_bit(int arglist, int rest, int th);
static int c_two_bits(int arglist, int rest, int th);
static int c_nat(int arglist, int rest, int th);
static int c_count(int arglist, int rest, int th);
static int c_copy_count(int arglist, int rest, int th);
static int c_zero(int arglist, int rest, int th);
static int c_strip(int arglist, int rest, int th);
static int user_scbm(int pred, int arity, int clause, int arglist, int rest, int th);
static int c_color(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Ssave_arg(arglist,th);
return(user_scbm(0,n,0,arglist,rest,th));
}

static int c_warm(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Ssave_arg(arglist,th);
return(user_scbm(1,n,0,arglist,rest,th));
}

static int c_is_warm(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Ssave_arg(arglist,th);
return(user_scbm(2,n,0,arglist,rest,th));
}

static int c_letter(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Ssave_arg(arglist,th);
return(user_scbm(3,n,0,arglist,rest,th));
}

static int c_digit(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Ssave_arg(arglist,th);
return(user_scbm(4,n,0,arglist,rest,th));
}

static int c_pair(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Ssave_arg(arglist,th);
return(user_scbm(5,n,0,arglist,rest,th));
}

static int c_animal(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Ssave_arg(arglist,th);
return(user_scbm(6,n,0,arglist,rest,th));
}

static int c_likes_milk(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Ssave_arg(arglist,th);
return(user_scbm(7,n,0,arglist,rest,th));
}

static int c_milk_drinker(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Ssave_arg(arglist,th);
return(user_scbm(8,n,0,arglist,rest,th));
}

static int c_bit(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Ssave_arg(arglist,th);
return(user_scbm(9,n,0,arglist,rest,th));
}

static int c_two_bits(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Ssave_arg(arglist,th);
return(user_scbm(10,n,0,arglist,rest,th));
}

static int c_nat(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Ssave_arg(arglist,th);
return(user_scbm(11,n,0,arglist,rest,th));
}

static int c_count(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Ssave_arg(arglist,th);
return(user_scbm(12,n,0,arglist,rest,th));
}

static int c_copy_count(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Ssave_arg(arglist,th);
return(user_scbm(13,n,0,arglist,rest,th));
}

static int c_zero(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Ssave_arg(arglist,th);
return(user_scbm(14,n,0,arglist,rest,th));
}

static int c_strip(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Ssave_arg(arglist,th);
return(user_scbm(15,n,0,arglist,rest,th));
}

void init_tpredicate(void){
(deftpred)("color",c_color,1,1);
(deftpred)("warm",c_warm,1,1);
(deftpred)("is_warm",c_is_warm,1,1);
(deftpred)("letter",c_letter,1,1);
(deftpred)("digit",c_digit,1,1);
(deftpred)("pair",c_pair,2,1);
(deftpred)("animal",c_animal,1,1);
(deftpred)("likes_milk",c_likes_milk,1,1);
(deftpred)("milk_drinker",c_milk_drinker,1,1);
(deftpred)("bit",c_bit,1,1);
(deftpred)("two_bits",c_two_bits,2,1);
(deftpred)("nat",c_nat,1,1);
(deftpred)("count",c_count,1,1);
(deftpred)("copy_count",c_copy_count,1,1);
(deftpred)("zero",c_zero,1,1);
(deftpred)("strip",c_strip,2,1);
}
void init_declare(void){
int body,th; th=0;
}
static int user_scbm(int pred, int arity, int clause, int arglist, int rest, int th){
void *next;
int arg1,arg2,arg3,arg4,arg5,aeg6,arg7,arg8,arg9,arg10,subr_number,varX_,varY_,varZ_,varA_,varX,varY,varZ;
np[th] = 0; rp[th] = 0; back_stack[0][AC_SCBM][th] = Jget_ac(th);
Spush_next(&&success,th);
switch(pred){
case 0: goto color;
case 1: goto warm;
case 2: goto is_warm;
case 3: goto letter;
case 4: goto digit;
case 5: goto pair;
case 6: goto animal;
case 7: goto likes_milk;
case 8: goto milk_drinker;
case 9: goto bit;
case 10: goto two_bits;
case 11: goto nat;
case 12: goto count;
case 13: goto copy_count;
case 14: goto zero;
case 15: goto strip;
}
color:
switch(arity){
case 1: goto color_1entry;
default: goto allfail;
}
warm:
switch(arity){
case 1: goto warm_1entry;
default: goto allfail;
}
is_warm:
switch(arity){
case 1: goto is_warm_1entry;
default: goto allfail;
}
letter:
switch(arity){
case 1: goto letter_1entry;
default: goto allfail;
}
digit:
switch(arity){
case 1: goto digit_1entry;
default: goto allfail;
}
pair:
switch(arity){
case 2: goto pair_2entry;
default: goto allfail;
}
animal:
switch(arity){
case 1: goto animal_1entry;
default: goto allfail;
}
likes_milk:
switch(arity){
case 1: goto likes_milk_1entry;
default: goto allfail;
}
milk_drinker:
switch(arity){
case 1: goto milk_drinker_1entry;
default: goto allfail;
}
bit:
switch(arity){
case 1: goto bit_1entry;
default: goto allfail;
}
two_bits:
switch(arity){
case 2: goto two_bits_2entry;
default: goto allfail;
}
nat:
switch(arity){
case 1: goto nat_1entry;
default: goto allfail;
}
count:
switch(arity){
case 1: goto count_1entry;
default: goto allfail;
}
copy_count:
switch(arity){
case 1: goto copy_count_1entry;
default: goto allfail;
}
zero:
switch(arity){
case 1: goto zero_1entry;
default: goto allfail;
}
strip:
switch(arity){
case 2: goto strip_2entry;
default: goto allfail;
}
color_1entry:
Spush_back(&&color_1,arglist,th);
color_1:
Jinc_proof(th);
switch(clause){
case 0: goto color_1_0;
case 1: goto color_1_1;
case 2: goto color_1_2;
case 3: goto color_1_3;
default: goto allfail;
}
warm_1entry:
Spush_back(&&warm_1,arglist,th);
warm_1:
Jinc_proof(th);
switch(clause){
case 0: goto warm_1_0;
case 1: goto warm_1_1;
case 2: goto warm_1_2;
default: goto allfail;
}
is_warm_1entry:
Spush_back(&&is_warm_1,arglist,th);
is_warm_1:
Jinc_proof(th);
switch(clause){
case 0: goto is_warm_1_0;
case 1: goto is_warm_1_1;
default: goto allfail;
}
letter_1entry:
Spush_back(&&letter_1,arglist,th);
letter_1:
Jinc_proof(th);
switch(clause){
case 0: goto letter_1_0;
case 1: goto letter_1_1;
case 2: goto letter_1_2;
default: goto allfail;
}
digit_1entry:
Spush_back(&&digit_1,arglist,th);
digit_1:
Jinc_proof(th);
switch(clause){
case 0: goto digit_1_0;
case 1: goto digit_1_1;
case 2: goto digit_1_2;
default: goto allfail;
}
pair_2entry:
Spush_back(&&pair_2,arglist,th);
pair_2:
Jinc_proof(th);
switch(clause){
case 0: goto pair_2_0;
case 1: goto pair_2_1;
default: goto allfail;
}
animal_1entry:
Spush_back(&&animal_1,arglist,th);
animal_1:
Jinc_proof(th);
switch(clause){
case 0: goto animal_1_0;
case 1: goto animal_1_1;
case 2: goto animal_1_2;
case 3: goto animal_1_3;
default: goto allfail;
}
likes_milk_1entry:
Spush_back(&&likes_milk_1,arglist,th);
likes_milk_1:
Jinc_proof(th);
switch(clause){
case 0: goto likes_milk_1_0;
case 1: goto likes_milk_1_1;
case 2: goto likes_milk_1_2;
default: goto allfail;
}
milk_drinker_1entry:
Spush_back(&&milk_drinker_1,arglist,th);
milk_drinker_1:
Jinc_proof(th);
switch(clause){
case 0: goto milk_drinker_1_0;
case 1: goto milk_drinker_1_1;
default: goto allfail;
}
bit_1entry:
Spush_back(&&bit_1,arglist,th);
bit_1:
Jinc_proof(th);
switch(clause){
case 0: goto bit_1_0;
case 1: goto bit_1_1;
case 2: goto bit_1_2;
default: goto allfail;
}
two_bits_2entry:
Spush_back(&&two_bits_2,arglist,th);
two_bits_2:
Jinc_proof(th);
switch(clause){
case 0: goto two_bits_2_0;
case 1: goto two_bits_2_1;
default: goto allfail;
}
nat_1entry:
Spush_back(&&nat_1,arglist,th);
nat_1:
Jinc_proof(th);
switch(clause){
case 0: goto nat_1_0;
case 1: goto nat_1_1;
case 2: goto nat_1_2;
default: goto allfail;
}
count_1entry:
Spush_back(&&count_1,arglist,th);
count_1:
Jinc_proof(th);
switch(clause){
case 0: goto count_1_0;
case 1: goto count_1_1;
case 2: goto count_1_2;
case 3: goto count_1_3;
default: goto allfail;
}
copy_count_1entry:
Spush_back(&&copy_count_1,arglist,th);
copy_count_1:
Jinc_proof(th);
switch(clause){
case 0: goto copy_count_1_0;
case 1: goto copy_count_1_1;
default: goto allfail;
}
zero_1entry:
Spush_back(&&zero_1,arglist,th);
zero_1:
Jinc_proof(th);
switch(clause){
case 0: goto zero_1_0;
case 1: goto zero_1_1;
default: goto allfail;
}
strip_2entry:
Spush_back(&&strip_2,arglist,th);
strip_2:
Jinc_proof(th);
switch(clause){
case 0: goto strip_2_0;
case 1: goto strip_2_1;
case 2: goto strip_2_2;
default: goto allfail;
}
color_1_0:
arg1 = Jcar(arglist);
Srelease(th);
Sinc_choice(th);
if(Junify_atom(arg1,Jmakeconst("red"),th) == YES)
{
goto success;
}
color_1_1:
arg1 = Jcar(arglist);
Srelease(th);
Sinc_choice(th);
if(Junify_atom(arg1,Jmakeconst("green"),th) == YES)
{
goto success;
}
color_1_2:
arg1 = Jcar(arglist);
Srelease(th);
Sinc_choice(th);
if(Junify_atom(arg1,Jmakeconst("blue"),th) == YES)
{
goto success;
}
color_1_3:
goto allfail;

warm_1_0:
arg1 = Jcar(arglist);
Srelease(th);
Sinc_choice(th);
if(Junify_atom(arg1,Jmakeconst("red"),th) == YES)
{
goto success;
}
warm_1_1:
arg1 = Jcar(arglist);
Srelease(th);
Sinc_choice(th);
if(Junify_atom(arg1,Jmakeconst("orange"),th) == YES)
{
goto success;
}
warm_1_2:
goto allfail;

is_warm_1_0:
arg1 = Jcar(arglist);
Srelease(th);
varX = Jmakevariant(th);
Sinc_choice(th);
if(Junify_var(arg1,varX,th) == YES)
{
is_warm_1_0_0:
arglist = Jwlistcons(varX,NIL,th);
back_stack[rp[th]+1][1][th] = varX;
Spush_back(&&is_warm_1_1,arglist,th);
goto is_warm_1_0_0join;
is_warm_1_0_0back:
varX= back_stack[rp[th]+1][1][th];
is_warm_1_0_0join:
next_stack[np[th]+1][1][th] = varX;
Spush_next(&&is_warm_1_0_1,th);
clause = Sget_choice(th);
goto warm_1;
is_warm_1_0_1:
Spush_back(&&is_warm_1_0,arglist,th);
goto success;
}
is_warm_1_1:
goto allfail;

letter_1_0:
arg1 = Jcar(arglist);
Srelease(th);
Sinc_choice(th);
if(Junify_atom(arg1,Jmakeconst("a"),th) == YES)
{
goto success;
}
letter_1_1:
arg1 = Jcar(arglist);
Srelease(th);
Sinc_choice(th);
if(Junify_atom(arg1,Jmakeconst("b"),th) == YES)
{
goto success;
}
letter_1_2:
goto allfail;

digit_1_0:
arg1 = Jcar(arglist);
Srelease(th);
Sinc_choice(th);
if(Junify_int(arg1,Jmakeint(1),th) == YES)
{
goto success;
}
digit_1_1:
arg1 = Jcar(arglist);
Srelease(th);
Sinc_choice(th);
if(Junify_int(arg1,Jmakeint(2),th) == YES)
{
goto success;
}
digit_1_2:
goto allfail;

pair_2_0:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
Srelease(th);
varX = Jmakevariant(th);
varY = Jmakevariant(th);
Sinc_choice(th);
if(Junify_var(arg1,varX,th) == YES && Junify_var(arg2,varY,th) == YES)
{
pair_2_0_0:
arglist = Jwlistcons(varX,NIL,th);
back_stack[rp[th]+1][1][th] = varX;
back_stack[rp[th]+1][2][th] = varY;
Spush_back(&&pair_2_1,arglist,th);
goto pair_2_0_0join;
pair_2_0_0back:
varX= back_stack[rp[th]+1][1][th];
varY= back_stack[rp[th]+1][2][th];
pair_2_0_0join:
next_stack[np[th]+1][1][th] = varX;
next_stack[np[th]+1][2][th] = varY;
Spush_next(&&pair_2_0_1,th);
clause = Sget_choice(th);
goto letter_1;
pair_2_0_1:
varX= next_stack[np[th]+1][1][th];
varY= next_stack[np[th]+1][2][th];
arglist = Jwlistcons(varY,NIL,th);
back_stack[rp[th]+1][1][th] = varX;
back_stack[rp[th]+1][2][th] = varY;
Spush_back(&&pair_2_0_0back,arglist,th);
goto pair_2_0_1join;
pair_2_0_1back:
varX= back_stack[rp[th]+1][1][th];
varY= back_stack[rp[th]+1][2][th];
pair_2_0_1join:
next_stack[np[th]+1][1][th] = varX;
next_stack[np[th]+1][2][th] = varY;
Spush_next(&&pair_2_0_2,th);
clause = Sget_choice(th);
goto digit_1;
pair_2_0_2:
Spush_back(&&pair_2_0_1back,arglist,th);
goto success;
}
pair_2_1:
goto allfail;

animal_1_0:
arg1 = Jcar(arglist);
Srelease(th);
Sinc_choice(th);
if(Junify_atom(arg1,Jmakeconst("cat"),th) == YES)
{
goto success;
}
animal_1_1:
arg1 = Jcar(arglist);
Srelease(th);
Sinc_choice(th);
if(Junify_atom(arg1,Jmakeconst("dog"),th) == YES)
{
goto success;
}
animal_1_2:
arg1 = Jcar(arglist);
Srelease(th);
Sinc_choice(th);
if(Junify_atom(arg1,Jmakeconst("bird"),th) == YES)
{
goto success;
}
animal_1_3:
goto allfail;

likes_milk_1_0:
arg1 = Jcar(arglist);
Srelease(th);
Sinc_choice(th);
if(Junify_atom(arg1,Jmakeconst("cat"),th) == YES)
{
goto success;
}
likes_milk_1_1:
arg1 = Jcar(arglist);
Srelease(th);
Sinc_choice(th);
if(Junify_atom(arg1,Jmakeconst("dog"),th) == YES)
{
goto success;
}
likes_milk_1_2:
goto allfail;

milk_drinker_1_0:
arg1 = Jcar(arglist);
Srelease(th);
varX = Jmakevariant(th);
Sinc_choice(th);
if(Junify_var(arg1,varX,th) == YES)
{
milk_drinker_1_0_0:
arglist = Jwlistcons(varX,NIL,th);
back_stack[rp[th]+1][1][th] = varX;
Spush_back(&&milk_drinker_1_1,arglist,th);
goto milk_drinker_1_0_0join;
milk_drinker_1_0_0back:
varX= back_stack[rp[th]+1][1][th];
milk_drinker_1_0_0join:
next_stack[np[th]+1][1][th] = varX;
Spush_next(&&milk_drinker_1_0_1,th);
clause = Sget_choice(th);
goto animal_1;
milk_drinker_1_0_1:
varX= next_stack[np[th]+1][1][th];
arglist = Jwlistcons(varX,NIL,th);
back_stack[rp[th]+1][1][th] = varX;
Spush_back(&&milk_drinker_1_0_0back,arglist,th);
goto milk_drinker_1_0_1join;
milk_drinker_1_0_1back:
varX= back_stack[rp[th]+1][1][th];
milk_drinker_1_0_1join:
next_stack[np[th]+1][1][th] = varX;
Spush_next(&&milk_drinker_1_0_2,th);
clause = Sget_choice(th);
goto likes_milk_1;
milk_drinker_1_0_2:
Spush_back(&&milk_drinker_1_0_1back,arglist,th);
goto success;
}
milk_drinker_1_1:
goto allfail;

bit_1_0:
arg1 = Jcar(arglist);
Srelease(th);
Sinc_choice(th);
if(Junify_int(arg1,Jmakeint(0),th) == YES)
{
goto success;
}
bit_1_1:
arg1 = Jcar(arglist);
Srelease(th);
Sinc_choice(th);
if(Junify_int(arg1,Jmakeint(1),th) == YES)
{
goto success;
}
bit_1_2:
goto allfail;

two_bits_2_0:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
Srelease(th);
varX = Jmakevariant(th);
varY = Jmakevariant(th);
Sinc_choice(th);
if(Junify_var(arg1,varX,th) == YES && Junify_var(arg2,varY,th) == YES)
{
two_bits_2_0_0:
arglist = Jwlistcons(varX,NIL,th);
back_stack[rp[th]+1][1][th] = varX;
back_stack[rp[th]+1][2][th] = varY;
Spush_back(&&two_bits_2_1,arglist,th);
goto two_bits_2_0_0join;
two_bits_2_0_0back:
varX= back_stack[rp[th]+1][1][th];
varY= back_stack[rp[th]+1][2][th];
two_bits_2_0_0join:
next_stack[np[th]+1][1][th] = varX;
next_stack[np[th]+1][2][th] = varY;
Spush_next(&&two_bits_2_0_1,th);
clause = Sget_choice(th);
goto bit_1;
two_bits_2_0_1:
varX= next_stack[np[th]+1][1][th];
varY= next_stack[np[th]+1][2][th];
arglist = Jwlistcons(varY,NIL,th);
back_stack[rp[th]+1][1][th] = varX;
back_stack[rp[th]+1][2][th] = varY;
Spush_back(&&two_bits_2_0_0back,arglist,th);
goto two_bits_2_0_1join;
two_bits_2_0_1back:
varX= back_stack[rp[th]+1][1][th];
varY= back_stack[rp[th]+1][2][th];
two_bits_2_0_1join:
next_stack[np[th]+1][1][th] = varX;
next_stack[np[th]+1][2][th] = varY;
Spush_next(&&two_bits_2_0_2,th);
clause = Sget_choice(th);
goto bit_1;
two_bits_2_0_2:
Spush_back(&&two_bits_2_0_1back,arglist,th);
goto success;
}
two_bits_2_1:
goto allfail;

nat_1_0:
arg1 = Jcar(arglist);
Srelease(th);
Sinc_choice(th);
if(Junify_int(arg1,Jmakeint(0),th) == YES)
{
goto success;
}
nat_1_1:
arg1 = Jcar(arglist);
Srelease(th);
varX = Jmakevariant(th);
Sinc_choice(th);
if(Junify(arg1,Jwcons(Jmakepred("s"),Jwcons(varX,NIL,th),th),th) == YES)
{
nat_1_1_0:
arglist = Jwlistcons(varX,NIL,th);
back_stack[rp[th]+1][1][th] = varX;
Spush_back(&&nat_1_2,arglist,th);
goto nat_1_1_0join;
nat_1_1_0back:
varX= back_stack[rp[th]+1][1][th];
nat_1_1_0join:
next_stack[np[th]+1][1][th] = varX;
Spush_next(&&nat_1_1_1,th);
clause = Sget_choice(th);
goto nat_1;
nat_1_1_1:
goto success;
}
nat_1_2:
goto allfail;

count_1_0:
arg1 = Jcar(arglist);
Srelease(th);
Sinc_choice(th);
if(Junify_int(arg1,Jmakeint(0),th) == YES)
{
goto success;
}
count_1_1:
arg1 = Jcar(arglist);
Srelease(th);
Sinc_choice(th);
if(Junify(arg1,Jwcons(Jmakepred("s"),Jwcons(Jmakeint(0),NIL,th),th),th) == YES)
{
goto success;
}
count_1_2:
arg1 = Jcar(arglist);
Srelease(th);
Sinc_choice(th);
if(Junify(arg1,Jwcons(Jmakepred("s"),Jwcons(Jwcons(Jmakepred("s"),Jwcons(Jmakeint(0),NIL,th),th),NIL,th),th),th) == YES)
{
goto success;
}
count_1_3:
goto allfail;

copy_count_1_0:
arg1 = Jcar(arglist);
Srelease(th);
varX = Jmakevariant(th);
Sinc_choice(th);
if(Junify_var(arg1,varX,th) == YES)
{
copy_count_1_0_0:
arglist = Jwlistcons(varX,NIL,th);
back_stack[rp[th]+1][1][th] = varX;
Spush_back(&&copy_count_1_1,arglist,th);
goto copy_count_1_0_0join;
copy_count_1_0_0back:
varX= back_stack[rp[th]+1][1][th];
copy_count_1_0_0join:
next_stack[np[th]+1][1][th] = varX;
Spush_next(&&copy_count_1_0_1,th);
clause = Sget_choice(th);
goto count_1;
copy_count_1_0_1:
Spush_back(&&copy_count_1_0,arglist,th);
goto success;
}
copy_count_1_1:
goto allfail;

zero_1_0:
arg1 = Jcar(arglist);
Srelease(th);
Sinc_choice(th);
if(Junify_int(arg1,Jmakeint(0),th) == YES)
{
goto success;
}
zero_1_1:
goto allfail;

strip_2_0:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
Srelease(th);
Sinc_choice(th);
if(Junify_int(arg1,Jmakeint(0),th) == YES && Junify_int(arg2,Jmakeint(0),th) == YES)
{
goto success;
}
strip_2_1:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
Srelease(th);
varZ = Jmakevariant(th);
varX = Jmakevariant(th);
varY = Jmakevariant(th);
Sinc_choice(th);
if(Junify(arg1,Jwcons(Jmakepred("s"),Jwcons(varX,NIL,th),th),th) == YES && Junify_var(arg2,varY,th) == YES)
{
strip_2_1_0:
arglist = Jwlistcons(varX,Jwlistcons(varZ,NIL,th),th);
back_stack[rp[th]+1][1][th] = varZ;
back_stack[rp[th]+1][2][th] = varX;
back_stack[rp[th]+1][3][th] = varY;
Spush_back(&&strip_2_2,arglist,th);
goto strip_2_1_0join;
strip_2_1_0back:
varZ= back_stack[rp[th]+1][1][th];
varX= back_stack[rp[th]+1][2][th];
varY= back_stack[rp[th]+1][3][th];
strip_2_1_0join:
next_stack[np[th]+1][1][th] = varZ;
next_stack[np[th]+1][2][th] = varX;
next_stack[np[th]+1][3][th] = varY;
Spush_next(&&strip_2_1_1,th);
clause = Sget_choice(th);
goto strip_2;
strip_2_1_1:
varZ= next_stack[np[th]+1][1][th];
varX= next_stack[np[th]+1][2][th];
varY= next_stack[np[th]+1][3][th];
arglist = Jwlistcons(varZ,NIL,th);
back_stack[rp[th]+1][1][th] = varZ;
back_stack[rp[th]+1][2][th] = varX;
back_stack[rp[th]+1][3][th] = varY;
Spush_back(&&strip_2_1_0back,arglist,th);
goto strip_2_1_1join;
strip_2_1_1back:
varZ= back_stack[rp[th]+1][1][th];
varX= back_stack[rp[th]+1][2][th];
varY= back_stack[rp[th]+1][3][th];
strip_2_1_1join:
next_stack[np[th]+1][1][th] = varZ;
next_stack[np[th]+1][2][th] = varX;
next_stack[np[th]+1][3][th] = varY;
Spush_next(&&strip_2_1_2,th);
clause = Sget_choice(th);
goto zero_1;
strip_2_1_2:
varZ= next_stack[np[th]+1][1][th];
varX= next_stack[np[th]+1][2][th];
varY= next_stack[np[th]+1][3][th];
arglist = Jwlistcons(varY,Jwlistcons(Jwcons(Jmakepred("s"),Jwcons(varX,NIL,th),th),NIL,th),th);
back_stack[rp[th]+1][1][th] = varZ;
back_stack[rp[th]+1][2][th] = varX;
back_stack[rp[th]+1][3][th] = varY;
Spush_back(&&strip_2_1_1back,arglist,th);
next_stack[np[th]+1][1][th] = varZ;
next_stack[np[th]+1][2][th] = varX;
next_stack[np[th]+1][3][th] = varY;
Spush_next(&&strip_2_1_3,th);subr_number = 198;
goto builtin_call;
strip_2_1_3:
goto success;
}
strip_2_2:
goto allfail;

success:
if(np[th] == 0){
if(Jprove_all(rest,Jget_sp(th),th) == YES) return(YES);
next = back_goto[rp[th]][th];
clause = Sget_choice(th);
arglist = Sget_arg(th);
np[th] = Sget_np(th);
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
clause = Sget_choice(th);
Spop_back(th);
arglist = Sget_arg(th);
goto *next;
false:
if(rp[th]==0) {return(NO);}
next = back_goto[rp[th]][th];
np[th] = Sget_np(th);
clause = Sget_choice(th);
arglist = Sget_arg(th);
goto *next;
builtin_call:
if(Jcallsubr(subr_number,Jderef(arglist,th),NIL,th) == YES)
goto success;
else goto false;
}
