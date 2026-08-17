/* SCBM builtin nondet predicate */

//------------append/3------------------------
append:
switch(arity){
case 3: goto append_3;
default: goto allfail;
}
append_3:
Jinc_proof(th);
switch(clause){
case 0: goto append_3_0;
case 1: goto append_3_1;
case 2: goto append_3_2;
default: goto allfail;
}
append_3_0:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
Srelease(th);
varX_ = Jmakevariant(th);
Sinc_choice(th);
Sset_back(&&append_3_1,th);
if(Junify_nil(arg1,th) == YES && Junify_var(arg2,varX_,th) == YES && Junify_var(arg3,varX_,th) == YES)
{
goto success;
}
append_3_1:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
Srelease(th);
varX_ = Jmakevariant(th);
varY_ = Jmakevariant(th);
varA_ = Jmakevariant(th);
varZ_ = Jmakevariant(th);
Sinc_choice(th);
Sset_back(&&append_3_2,th);
if(Junify_pair(arg1,Jwlistcons(varA_,varX_,th),th) == YES && Junify_var(arg2,varY_,th) == YES && Junify_pair(arg3,Jwlistcons(varA_,varZ_,th),th) == YES)
{
append_3_1_0:
arglist = Jwlistcons(varX_,Jwlistcons(varY_,Jwlistcons(varZ_,NIL,th),th),th);
Spush_back(&&append_3_2,arglist,th);
goto append_3_1_0join;
append_3_1_0back:
varX_= next_stack[np[th]+1][1][th];
varY_= next_stack[np[th]+1][2][th];
varA_= next_stack[np[th]+1][3][th];
varZ_= next_stack[np[th]+1][4][th];
append_3_1_0join:
next_stack[np[th]+1][1][th] = varX_;
next_stack[np[th]+1][2][th] = varY_;
next_stack[np[th]+1][3][th] = varA_;
next_stack[np[th]+1][4][th] = varZ_;
Spush_next(&&append_3_1_1,th);
clause = Sget_choice(th);
goto append_3;
append_3_1_1:
goto success;
}
append_3_2:
Sreset_back(th);
goto allfail;

//--------between/3------------------

between_3:
Jinc_proof(th);
switch(clause){
case 0: goto between_3_0;
case 1: goto between_3_1;
case 2: goto between_3_2;
default: goto allfail;
}
between_3_0:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
Srelease(th);
varY_ = Jmakevariant(th);
varX_ = Jmakevariant(th);
Sinc_choice(th);
Sset_back(&&between_3_1,th);
if(Junify_var(arg1,varX_,th) == YES && Junify_var(arg2,varY_,th) == YES && Junify_var(arg3,varX_,th) == YES)
{
between_3_0_0:
arglist = Jwlistcons(varX_,Jwlistcons(varY_,NIL,th),th);
next_stack[np[th]+1][1][th] = varY_;
next_stack[np[th]+1][2][th] = varX_;
Spush_next(&&between_3_0_1,th);subr_number = 88;
goto builtin_call;
between_3_0_1:
goto success;
}
between_3_1:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
Srelease(th);
varA_ = Jmakevariant(th);
varX_ = Jmakevariant(th);
varY_ = Jmakevariant(th);
varZ_ = Jmakevariant(th);
Sinc_choice(th);
Sset_back(&&between_3_2,th);
if(Junify_var(arg1,varX_,th) == YES && Junify_var(arg2,varY_,th) == YES && Junify_var(arg3,varZ_,th) == YES)
{
between_3_1_0:
arglist = Jwlistcons(varX_,Jwlistcons(varY_,NIL,th),th);
next_stack[np[th]+1][1][th] = varA_;
next_stack[np[th]+1][2][th] = varX_;
next_stack[np[th]+1][3][th] = varY_;
next_stack[np[th]+1][4][th] = varZ_;
Spush_next(&&between_3_1_1,th);
subr_number = 77;
goto builtin_call;
between_3_1_1:
varA_= next_stack[np[th]+1][1][th];
varX_= next_stack[np[th]+1][2][th];
varY_= next_stack[np[th]+1][3][th];
varZ_= next_stack[np[th]+1][4][th];
arglist = Jwlistcons(varA_,Jwlistcons(Jwcons(2179,Jwcons(varX_,Jwcons(Jmakeint(1),NIL,th),th),th),NIL,th),th);
next_stack[np[th]+1][1][th] = varA_;
next_stack[np[th]+1][2][th] = varX_;
next_stack[np[th]+1][3][th] = varY_;
next_stack[np[th]+1][4][th] = varZ_;
Spush_next(&&between_3_1_2,th);
subr_number = 187;
goto builtin_call;
between_3_1_2:
varA_= next_stack[np[th]+1][1][th];
varX_= next_stack[np[th]+1][2][th];
varY_= next_stack[np[th]+1][3][th];
varZ_= next_stack[np[th]+1][4][th];
arglist = Jwlistcons(varA_,Jwlistcons(varY_,Jwlistcons(varZ_,NIL,th),th),th);
goto between_3_1_2join;
between_3_1_2back:
varA_= next_stack[np[th]+1][1][th];
varX_= next_stack[np[th]+1][2][th];
varY_= next_stack[np[th]+1][3][th];
varZ_= next_stack[np[th]+1][4][th];
between_3_1_2join:
next_stack[np[th]+1][1][th] = varA_;
next_stack[np[th]+1][2][th] = varX_;
next_stack[np[th]+1][3][th] = varY_;
next_stack[np[th]+1][4][th] = varZ_;
Spush_next(&&between_3_1_3,th);
clause = Sget_choice(th);
goto between_3;
between_3_1_3:
goto success;
}
between_3_2:
Sreset_back(th);
goto allfail;


//-------------length/3-----------------
length_2:
Jinc_proof(th);
switch(clause){
case 0: goto length_2_0;
case 1: goto length_2_1;
case 2: goto length_2_2;
default: goto allfail;
}
length_2_0:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
Srelease(th);
Sinc_choice(th);
Sset_back(&&length_2_1,th);
if(Junify_nil(arg1,th) == YES && Junify_int(arg2,Jmakeint(0),th) == YES)
{
goto success;
}
length_2_1:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
Srelease(th);
varZ_ = Jmakevariant(th);
varA_ = Jmakevariant(th);
varX_ = Jmakevariant(th);
varY_ = Jmakevariant(th);
Sinc_choice(th);
Sset_back(&&length_2_2,th);
if(Junify_pair(arg1,Jwlistcons(varA_,varX_,th),th) == YES && Junify_var(arg2,varY_,th) == YES)
{
length_2_1_0:
arglist = Jwlistcons(varX_,Jwlistcons(varZ_,NIL,th),th);
Spush_back(&&length_2_2,arglist,th);
goto length_2_1_0join;
length_2_1_0back:
varZ_= next_stack[np[th]+1][1][th];
varA_= next_stack[np[th]+1][2][th];
varX_= next_stack[np[th]+1][3][th];
varY_= next_stack[np[th]+1][4][th];
length_2_1_0join:
next_stack[np[th]+1][1][th] = varZ_;
next_stack[np[th]+1][2][th] = varA_;
next_stack[np[th]+1][3][th] = varX_;
next_stack[np[th]+1][4][th] = varY_;
Spush_next(&&length_2_1_1,th);
clause = Sget_choice(th);
goto length_2;
length_2_1_1:
varZ_= next_stack[np[th]+1][1][th];
varA_= next_stack[np[th]+1][2][th];
varX_= next_stack[np[th]+1][3][th];
varY_= next_stack[np[th]+1][4][th];
arglist = Jwlistcons(varY_,Jwlistcons(Jwcons(2179,Jwcons(varZ_,Jwcons(Jmakeint(1),NIL,th),th),th),NIL,th),th);
Spush_back(&&length_2_1_0back,arglist,th);
next_stack[np[th]+1][1][th] = varZ_;
next_stack[np[th]+1][2][th] = varA_;
next_stack[np[th]+1][3][th] = varX_;
next_stack[np[th]+1][4][th] = varY_;
Spush_next(&&length_2_1_2,th);subr_number = 187;
goto builtin_call;
length_2_1_2:
goto success;
}
length_2_2:
Sreset_back(th);
goto allfail;


//------------------------member/2-----------------
member_2:
Jinc_proof(th);
switch(clause){
case 0: goto member_2_0;
case 1: goto member_2_1;
case 2: goto member_2_2;
default: goto allfail;
}
member_2_0:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
Srelease(th);
varX_ = Jmakevariant(th);
varA_ = Jmakevariant(th);
Sinc_choice(th);
Sset_back(&&member_2_1,th);
if(Junify_var(arg1,varX_,th) == YES && Junify_pair(arg2,Jwlistcons(varX_,varA_,th),th) == YES)
{
goto success;
}
member_2_1:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
Srelease(th);
varX_ = Jmakevariant(th);
varA_ = Jmakevariant(th);
varY_ = Jmakevariant(th);
Sinc_choice(th);
Sset_back(&&member_2_2,th);
if(Junify_var(arg1,varX_,th) == YES && Junify_pair(arg2,Jwlistcons(varA_,varY_,th),th) == YES)
{
member_2_1_0:
arglist = Jwlistcons(varX_,Jwlistcons(varY_,NIL,th),th);
Spush_back(&&member_2_2,arglist,th);
goto member_2_1_0join;
member_2_1_0back:
varX_= next_stack[np[th]+1][1][th];
varA_= next_stack[np[th]+1][2][th];
varY_= next_stack[np[th]+1][3][th];
member_2_1_0join:
next_stack[np[th]+1][1][th] = varX_;
next_stack[np[th]+1][2][th] = varA_;
next_stack[np[th]+1][3][th] = varY_;
Spush_next(&&member_2_1_1,th);
clause = Sget_choice(th);
goto member_2;
member_2_1_1:
goto success;
}
member_2_2:
Sreset_back(th);
goto allfail;
