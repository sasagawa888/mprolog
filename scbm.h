/* SCBM builtin nondet predicate */

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

