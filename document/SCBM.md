# SCBM API Specification

## 1. Overview

SCBM (Success Continuation and Backtracking Mechine) is the runtime control mechanism used by the M-Prolog compiler.

SCBM manages two independent control structures:

1. **Success continuations**
2. **Backtracking environments**

Success continuations are managed by `np`, while backtracking environments are managed by `rp`.

These structures are intentionally kept separate.

```c
static void *next_goto[RECURSIZE][THREADSIZE];
static void *back_goto[RECURSIZE][THREADSIZE];
static void *back_goto1[RECURSIZE][THREADSIZE];

static int next_stack[RECURSIZE][256][THREADSIZE];
static int back_stack[RECURSIZE][SCBM_ELT_SIZE][THREADSIZE];

static int np[THREADSIZE];   /* success-continuation pointer */
static int rp[THREADSIZE];   /* backtracking-environment pointer */
```

Each Prolog execution thread has its own `np` and `rp`.

---

# 2. Success Continuation Stack

The success continuation stack represents where execution should continue after a goal succeeds.

The current stack position is held in:

```c
np[th]
```

The continuation address is stored in:

```c
next_goto[np][th]
```

## 2.1 `Spush_next`

```c
static inline void Spush_next(void *cont, int th)
```

Pushes a success continuation.

Operation:

```c
np[th]++;
next_goto[np[th]][th] = cont;
```

Before pushing, the function checks for stack overflow.

### Parameters

* `cont` — GCC computed-goto label address used as the success continuation.
* `th` — thread number.

### Effect

After the operation:

```text
np := np + 1
next_goto[np] := cont
```

The function does not modify `rp`.

---

## 2.2 `Spop_next`

```c
static inline void Spop_next(int th)
```

Removes the current success continuation.

Operation:

```c
np[th]--;
```

The function checks for stack underflow.

### Effect

```text
np := np - 1
```

No continuation address needs to be erased. The value above the current `np` is regarded as invalid.

---

# 3. Backtracking Environment Stack

The backtracking stack stores the execution environment required when Prolog must retry another alternative.

Its current position is:

```c
rp[th]
```

Each entry contains:

```text
SP_SCBM       saved stack pointer
CHOICE_SCBM   current alternative number
WP_SCBM       saved WP value
AC_SCBM       saved AC value
ARGLIST_SCBM  argument list
NP_SCBM       saved success-continuation pointer
```

A backtracking continuation is stored separately in:

```c
back_goto[rp][th]
```

The original continuation is preserved in:

```c
back_goto1[rp][th]
```

---

# 4. Creating a Backtracking Environment

## 4.1 `Spush_back`

```c
static inline void Spush_back(void *cont, int arglist, int th)
```

Creates a new backtracking environment.

The function first increments `rp`:

```c
rp[th]++;
```

It then saves the current execution state:

```c
back_stack[rp[th]][SP_SCBM][th]      = Jget_sp(th);
back_stack[rp[th]][CHOICE_SCBM][th]  = 0;
back_stack[rp[th]][WP_SCBM][th]      = Jget_wp(th);
back_stack[rp[th]][AC_SCBM][th]      = Jget_ac(th);
back_stack[rp[th]][ARGLIST_SCBM][th] = arglist;
back_stack[rp[th]][NP_SCBM][th]      = np[th];
```

The backtracking continuation is stored twice:

```c
back_goto[rp[th]][th]  = cont;
back_goto1[rp[th]][th] = cont;
```

### Purpose of `back_goto1`

`back_goto1` preserves the original backtracking destination.

`back_goto` may later be temporarily changed by `Sset_back()`.

The original value can therefore be recovered using `Sreset_back()`.

### Initial choice value

A newly created environment always begins with:

```text
choice = 0
```

---

# 5. Backtracking Continuation Control

## 5.1 `Sset_back`

```c
static inline void Sset_back(void *cont, int th)
```

Changes the active backtracking continuation of the current environment.

```c
back_goto[rp[th]][th] = cont;
```

It does not modify the original continuation stored in `back_goto1`.

---

## 5.2 `Sreset_back`

```c
static inline void Sreset_back(int th)
```

Restores the active backtracking continuation to the continuation originally installed by `Spush_back()`.

```c
back_goto[rp[th]][th] =
    back_goto1[rp[th]][th];
```

Conceptually:

```text
active_back_continuation :=
    original_back_continuation
```

This permits temporary redirection of failure without destroying the original backtracking destination.

---

# 6. Choice Management

## 6.1 `Sinc_choice`

```c
static inline void Sinc_choice(int th)
```

Advances the alternative number associated with the current backtracking environment.

```c
back_stack[rp[th]][CHOICE_SCBM][th]++;
```

The compiler may use this value to select the appropriate clause or alternative after backtracking.

---

## 6.2 `Sget_choice`

```c
static inline int Sget_choice(int th)
```

Returns the current alternative number.

```c
return back_stack[rp[th]][CHOICE_SCBM][th];
```

A newly pushed backtracking environment has:

```text
choice = 0
```

Repeated calls to `Sinc_choice()` produce:

```text
0 -> 1 -> 2 -> 3 -> ...
```

---

# 7. Environment Restoration

## 7.1 `Srelease`

```c
static inline void Srelease(int th)
{
    Junbind(back_stack[rp[th]][SP_SCBM][th], th);
    Jset_ac(back_stack[rp[th]][AC_SCBM][th], th);
}
```

`Srelease()` restores the parts of the execution environment that must be rewound when retrying an alternative.

It performs two operations.

### 1. Undo variable bindings

```c
Junbind(saved_sp, th);
```

All bindings made after the saved `SP` are undone.

Conceptually:

```text
bindings := state at backtracking-point creation
```

### 2. Restore AC

```c
Jset_ac(saved_ac, th);
```

`AC` is restored to the value recorded by `Spush_back()`.

This is required because local variables generated by compiled predicates depend on the AC-based environment.

---

# 8. Important Rule: WP Is Not Restored by `Srelease`

Although `Spush_back()` records:

```c
back_stack[rp[th]][WP_SCBM][th] = Jget_wp(th);
```

`Srelease()` deliberately does **not** execute:

```c
Jset_wp(back_stack[rp[th]][WP_SCBM][th], th);
```

and does not otherwise clear or restore WP.

This behavior is intentional.

Restoring WP during `Srelease()` causes the current SCBM execution model to malfunction.

Therefore the SCBM rule is:

```text
Srelease restores SP-related bindings and AC.
Srelease does NOT restore or clear WP.
```

The saved `WP_SCBM` field remains part of the backtracking environment, but it is not currently used by `Srelease()`.

This distinction must be preserved when modifying the SCBM implementation.

---

# 9. Argument List Management

## 9.1 `Sget_arg`

```c
static inline int Sget_arg(int th)
```

Returns the argument list stored in the current backtracking environment.

```c
return back_stack[rp[th]][ARGLIST_SCBM][th];
```

This allows the compiled predicate to reconstruct its arguments when execution re-enters through a backtracking path.

---

## 9.2 `Ssave_arg`

```c
static inline void Ssave_arg(int x, int th)
```

Replaces the argument list stored in the current backtracking environment.

```c
back_stack[rp[th]][ARGLIST_SCBM][th] = x;
```

This does not create a new backtracking environment.

It modifies the `ARGLIST_SCBM` field of the environment identified by the current `rp`.

---

# 10. Saved Success-Continuation Position

## 10.1 `Sget_np`

```c
static inline int Sget_np(int th)
```

Returns the `np` value that was active when the current backtracking environment was created.

```c
return back_stack[rp[th]][NP_SCBM][th];
```

`Spush_back()` saves:

```c
back_stack[rp[th]][NP_SCBM][th] = np[th];
```

Thus a backtracking environment records the success-continuation depth associated with its creation.

`Sget_np()` only retrieves this saved value. It does not modify `np`.

---

# 11. Removing a Backtracking Environment

## 11.1 `Spop_back`

```c
static inline void Spop_back(int th)
```

Removes the current backtracking environment.

```c
rp[th]--;
```

The function checks for stack underflow.

The contents of the removed entry do not need to be cleared. They become inaccessible after `rp` is decremented.

---

# 12. SCBM State Model

SCBM contains two principally independent stack pointers:

```text
np : success-continuation depth
rp : backtracking-environment depth
```

Their responsibilities are different.

### Success direction

```text
Spush_next
    |
    v
next_goto[np]
    |
 goal succeeds
    |
    v
goto success continuation
```

### Failure direction

```text
Spush_back
    |
    v
back_goto[rp]
    |
 goal fails
    |
    v
Srelease
    |
    +-- undo bindings to saved SP
    |
    +-- restore saved AC
    |
    +-- WP remains unchanged
    |
    v
goto backtracking continuation
```

The two mechanisms cooperate but must not be treated as a single stack.

---

# 13. Backtracking Environment Layout

Conceptually, one `rp` entry has the following form:

```text
Backtracking Environment
+-------------------------+
| SP                      |
| choice                  |
| WP                      |
| AC                      |
| arglist                 |
| saved np                |
+-------------------------+
| active back goto        |
| original back goto      |
+-------------------------+
```

where:

```text
SP       = trail/binding restoration boundary
choice   = current alternative number
WP       = saved WP value
AC       = local-variable/environment base state
arglist  = predicate argument list
saved np = success-continuation depth
```

The saved WP value is currently metadata only as far as `Srelease()` is concerned.

---

# 14. Basic API Semantics

| API                             | Main effect                             |
| ------------------------------- | --------------------------------------- |
| `Spush_next(cont, th)`          | Push success continuation               |
| `Spop_next(th)`                 | Pop success continuation                |
| `Spush_back(cont, arglist, th)` | Create backtracking environment         |
| `Spop_back(th)`                 | Remove backtracking environment         |
| `Sset_back(cont, th)`           | Temporarily change failure continuation |
| `Sreset_back(th)`               | Restore original failure continuation   |
| `Sinc_choice(th)`               | Advance alternative number              |
| `Sget_choice(th)`               | Read alternative number                 |
| `Srelease(th)`                  | Undo bindings and restore AC            |
| `Sget_arg(th)`                  | Retrieve saved argument list            |
| `Ssave_arg(x, th)`              | Replace saved argument list             |
| `Sget_np(th)`                   | Retrieve `np` saved at `Spush_back()`   |

---

# 15. Invariants

The following invariants are fundamental to the current SCBM implementation.

### Invariant 1

`np` and `rp` represent different concepts and must be maintained independently.

### Invariant 2

Every active backtracking environment has an original backtracking continuation:

```c
back_goto1[rp][th]
```

even when its active continuation in `back_goto` has been changed.

### Invariant 3

`Spush_back()` initializes:

```text
choice = 0
```

### Invariant 4

`Srelease()` returns AC to the value associated with the current backtracking environment.

### Invariant 5

`Srelease()` undoes bindings using the SP stored in the current backtracking environment.

### Invariant 6

`Srelease()` must not restore or clear WP.

In particular, the following must not be added to `Srelease()`:

```c
Jset_wp(back_stack[rp[th]][WP_SCBM][th], th);
```

unless the execution model itself is redesigned.

### Invariant 7

`Sget_np()` retrieves the saved success-continuation position but does not itself restore `np`.

### Invariant 8

`Sset_back()` changes only the active failure continuation.

`Sreset_back()` must always be able to recover the continuation originally supplied to `Spush_back()`.

---

# 16. Design Principle

SCBM does not attempt to save and restore the entire state of the Prolog machine.

Instead, it stores only the information required by the compiled control-flow model.

This is an important design rule.

A backtracking operation is therefore not:

```text
restore every machine register
```

but rather:

```text
restore only the state whose logical lifetime belongs
to the current backtracking environment
```

In the current implementation this means, in particular:

```text
bindings -> restored using saved SP
AC       -> restored
WP       -> preserved
choice   -> maintained by SCBM
arglist  -> available for reconstruction
np       -> saved and explicitly accessible
```

This selective restoration is part of the SCBM execution semantics, not merely an implementation optimization.


# SCBM Generated Code Explained Using `append/3`

## 1. Introduction

This document explains the C code generated by the M-Prolog SCBM compiler using the standard Prolog predicate `append/3` as an example.

The source predicate is internally named `mappend`, but throughout this document it should be understood simply as:

```prolog
append/3
```

Conceptually, the predicate corresponds to the usual Prolog definition:

```prolog
append([], X, X).

append([A|X], Y, [A|Z]) :-
    append(X, Y, Z).
```

Although this is a very small predicate, it demonstrates most of the essential mechanisms of SCBM:

* predicate dispatch
* clause selection
* unification
* choice management
* failure continuations
* success continuations
* recursive calls
* preservation of local variables
* backtracking
* restoration of arguments
* final success and failure handling

For this reason, `append/3` is a useful minimal example for understanding generated SCBM code.

---

# 2. Entry Function

The externally visible compiled predicate is:

```c
static int c_mappend(int arglist, int rest, int th)
{
    int n;

    n = Jlength(arglist);
    Ssave_arg(arglist,th);

    return(user_scbm(0,n,0,arglist,rest,th));
}
```

This small function acts as an interface between the M-Prolog runtime and the SCBM-generated code.

The predicate is registered by:

```c
void init_tpredicate(void)
{
    (deftpred)("mappend",c_mappend,3,1);
}
```

The logical predicate is therefore:

```text
append/3
```

with C entry function:

```text
c_mappend()
```

---

# 3. Arguments Passed to SCBM

The call:

```c
user_scbm(0,n,0,arglist,rest,th)
```

contains the following information:

```text
pred     predicate number
arity    predicate arity
clause   initial clause number
arglist  current argument list
rest     remaining Prolog goals
th       thread number
```

For `append/3`:

```text
pred   = 0
arity  = 3
clause = 0
```

Thus the first execution begins with the first clause of predicate number zero.

---

# 4. Initial SCBM State

At the beginning of `user_scbm()`:

```c
np[th] = 0;
rp[th] = 0;

back_stack[0][AC_SCBM][th] = Jget_ac(th);

Spush_next(&&success,th);
```

SCBM initializes its two control-stack pointers:

```text
np = 0   success continuation depth
rp = 0   backtracking environment depth
```

The current AC is also recorded at backtracking level zero.

The first success continuation is:

```c
&&success
```

Therefore the initial continuation stack is conceptually:

```text
next stack

np = 1
+---------+
| success |
+---------+
```

This means that when `append/3` succeeds at the top level, control eventually reaches the common `success` label.

---

# 5. Predicate Dispatch

SCBM uses ordinary C `switch` statements and GCC computed goto labels instead of a bytecode interpreter.

The first dispatch is:

```c
switch(pred){
case 0: goto mappend;
}
```

For predicate zero:

```text
pred = 0
   |
   v
append
```

The next dispatch selects the arity:

```c
mappend:
switch(arity){
case 3: goto mappend_3;
default: goto allfail;
}
```

Only `append/3` exists here.

Therefore:

```text
append
  |
arity = 3
  |
  v
append_3
```

---

# 6. Clause Dispatch

The generated clause dispatcher is:

```c
mappend_3:
Jinc_proof(th);

switch(clause){
case 0: goto mappend_3_0;
case 1: goto mappend_3_1;
case 2: goto mappend_3_2;
default: goto allfail;
}
```

The compiler has generated three labels:

```text
append_3_0   first clause
append_3_1   second clause
append_3_2   terminal failure label
```

The third entry is not a Prolog source clause.

It represents the condition:

```text
there are no more clauses
```

and ultimately transfers control to `allfail`.

Thus the clause sequence is:

```text
clause 0
   |
   v
clause 1
   |
   v
terminal failure
```

---

# 7. First Clause

The first Prolog clause is:

```prolog
append([], X, X).
```

The generated label begins:

```c
mappend_3_0:
```

First, the three arguments are extracted:

```c
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
```

Conceptually:

```text
arg1 = first argument
arg2 = second argument
arg3 = third argument
```

---

# 8. Restoring the Clause Environment

Before attempting the clause, SCBM calls:

```c
Srelease(th);
```

In the current SCBM implementation, `Srelease()` performs:

```text
undo bindings back to saved SP
restore saved AC
```

It does not restore WP.

This is important because each clause must begin from the logical state associated with the current backtracking environment.

If an earlier clause partially unified arguments and then failed, those bindings must not remain when the next clause is tried.

Thus clause execution begins from a clean logical state.

---

# 9. Creating Clause Variables

The source clause:

```prolog
append([], X, X).
```

contains one logical variable:

```text
X
```

The generated code creates it with:

```c
varX = Jmakevariant(th);
```

This produces a fresh Prolog variable.

---

# 10. Preparing the Next Alternative

Before attempting the first clause:

```c
Sinc_choice(th);
Sset_back(&&mappend_3_1,th);
```

SCBM records that the next alternative is clause 1.

Conceptually:

```text
current clause : clause 0
failure target : clause 1
choice         : incremented
```

The active failure continuation becomes:

```text
append_3_1
```

Therefore, if clause 0 fails, execution does not search for an address dynamically.

It already knows exactly where the next alternative is located.

---

# 11. Unification of the First Clause

The head:

```prolog
append([], X, X)
```

is compiled directly into:

```c
if(
    Junify_nil(arg1,th) == YES &&
    Junify_var(arg2,varX,th) == YES &&
    Junify_var(arg3,varX,th) == YES
)
{
    goto success;
}
```

This corresponds almost literally to:

```text
arg1 = []
arg2 = X
arg3 = X
```

The same generated variable `varX` is used for both the second and third arguments.

Therefore a call such as:

```prolog
append([], [1,2], X)
```

produces:

```prolog
X = [1,2]
```

If all three unifications succeed:

```c
goto success;
```

The clause has no body, so success is immediate.

---

# 12. Failure of the First Clause

If any unification fails, execution simply falls through to:

```c
mappend_3_1:
```

There is no interpreter-level search loop.

The next clause is physically represented by the next generated label.

This is one of the basic ideas of SCBM:

```text
Prolog alternative selection
        ↓
native C control flow
```

---

# 13. Second Clause

The second source clause is:

```prolog
append([A|X], Y, [A|Z]) :-
    append(X, Y, Z).
```

Its generated code begins:

```c
mappend_3_1:
```

Again, the predicate arguments are reconstructed:

```c
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
```

and the logical environment is restored:

```c
Srelease(th);
```

---

# 14. Local Variables of the Recursive Clause

The second clause contains four logical variables:

```text
X
Y
A
Z
```

They are created as fresh variables:

```c
varX = Jmakevariant(th);
varY = Jmakevariant(th);
varA = Jmakevariant(th);
varZ = Jmakevariant(th);
```

These correspond to:

```prolog
append([A|X], Y, [A|Z])
```

---

# 15. Preparing the End-of-Clause Alternative

The second clause is the final real clause.

Therefore its failure continuation is:

```c
Sset_back(&&mappend_3_2,th);
```

After this clause, there are no more source clauses.

The generated control sequence is therefore:

```text
append_3_0
     |
     v
append_3_1
     |
     v
append_3_2
     |
     v
allfail
```

---

# 16. Unification of the Recursive Clause

The head:

```prolog
append([A|X], Y, [A|Z])
```

becomes:

```c
if(
    Junify_pair(arg1,Jwlistcons(varA,varX,th),th) == YES &&
    Junify_var(arg2,varY,th) == YES &&
    Junify_pair(arg3,Jwlistcons(varA,varZ,th),th) == YES
)
```

This represents:

```text
arg1 = [A|X]
arg2 = Y
arg3 = [A|Z]
```

Notice that the same `varA` occurs in both list cells.

This directly represents the sharing of the Prolog variable `A`.

For example:

```prolog
append([1,2], [3], R)
```

initially matches:

```text
A = 1
X = [2]
Y = [3]
R = [1|Z]
```

The body then has to solve:

```prolog
append([2], [3], Z)
```

---

# 17. Construction of the Recursive Call

The body call:

```prolog
append(X,Y,Z)
```

is converted into an argument list:

```c
arglist =
    Jwlistcons(
        varX,
        Jwlistcons(
            varY,
            Jwlistcons(varZ,NIL,th),
            th),
        th);
```

Conceptually:

```text
arglist = [X,Y,Z]
```

This argument list becomes the input for the recursive invocation of `append/3`.

---

# 18. Creating a Backtracking Environment

Before entering the recursive call, SCBM executes:

```c
Spush_back(&&mappend_3_2,arglist,th);
```

A new backtracking environment is created.

It records information including:

```text
SP
choice
WP
AC
arglist
np
failure continuation
```

The backtracking continuation supplied here is:

```text
append_3_2
```

because failure of this recursive path means that no further source clauses remain at this level.

The important point is that recursion in SCBM is not implemented using the C call stack.

Instead, the logical continuation state is explicitly represented by SCBM.

---

# 19. Why Local Variables Must Be Saved

The recursive call will reuse the same generated C function:

```c
user_scbm()
```

and therefore ordinary C local variables such as:

```text
varX
varY
varA
varZ
```

cannot be relied upon to preserve their logical values across SCBM control transfers.

SCBM therefore stores the variables required after the recursive call in:

```c
next_stack
```

The generated code is:

```c
next_stack[np[th]+1][1][th] = varX;
next_stack[np[th]+1][2][th] = varY;
next_stack[np[th]+1][3][th] = varA;
next_stack[np[th]+1][4][th] = varZ;
```

Conceptually:

```text
next continuation frame

slot 1 = X
slot 2 = Y
slot 3 = A
slot 4 = Z
```

Thus `next_stack` also acts as storage for values whose lifetime crosses a continuation boundary.

---

# 20. The `join` Label

The generated code contains:

```c
mappend_3_1_0join:
```

This is the common point shared by:

```text
normal forward execution
and
execution re-entered after backtracking
```

The generated structure is:

```c
mappend_3_1_0back:
    ...
    
mappend_3_1_0join:
    ...
```

This separation is important.

On normal forward execution, the variables already exist in ordinary C locals.

On backtracking re-entry, those locals must first be reconstructed.

Both paths can then continue through the same `join` label.

---

# 21. Backtracking Re-entry

The backtracking entry is:

```c
mappend_3_1_0back:
```

The clause variables are reconstructed from the saved continuation frame:

```c
varX = next_stack[np[th]+1][1][th];
varY = next_stack[np[th]+1][2][th];
varA = next_stack[np[th]+1][3][th];
varZ = next_stack[np[th]+1][4][th];
```

This restores the logical environment required by the generated continuation.

Execution then falls through into:

```c
mappend_3_1_0join:
```

Thus the pattern is:

```text
normal execution --------+
                         |
                         v
                       join
                         ^
                         |
backtracking -> restore -+
```

This avoids duplicating the continuation code.

---

# 22. Installing the Success Continuation

After saving the local variables, SCBM installs:

```c
Spush_next(&&mappend_3_1_1,th);
```

The label:

```text
append_3_1_1
```

means:

```text
continue here after the recursive append succeeds
```

Conceptually:

```text
append(X,Y,Z)
     |
     | success
     v
append_3_1_1
```

This is the explicit SCBM equivalent of a return address.

---

# 23. Entering the Recursive Predicate

The generated code obtains the clause to execute:

```c
clause = Sget_choice(th);
```

and jumps back to the predicate dispatcher:

```c
goto mappend_3;
```

Therefore recursion is implemented as:

```text
construct arguments
       |
push backtracking state
       |
save local variables
       |
push success continuation
       |
       v
goto append_3
```

There is no recursive C call such as:

```c
c_mappend(...)
```

Instead, control stays inside the large generated SCBM function.

This is one of the central implementation ideas of SCBM.

---

# 24. Success After the Recursive Call

When the recursive `append/3` succeeds, the generic `success` handler takes the continuation from `next_goto`.

Eventually control reaches:

```c
mappend_3_1_1:
    goto success;
```

There is nothing else to execute in the body.

Therefore success of the recursive goal means success of the entire second clause.

This corresponds directly to:

```prolog
append([A|X],Y,[A|Z]) :-
    append(X,Y,Z).
```

The body contains only one goal.

---

# 25. Terminal Clause Label

After the two real clauses, the compiler generates:

```c
mappend_3_2:
    Sreset_back(th);
    goto allfail;
```

This means:

```text
no more append/3 clauses exist at this level
```

Before propagating failure, the original backtracking continuation is restored:

```c
Sreset_back(th);
```

This is necessary because the active backtracking destination may previously have been changed with:

```c
Sset_back(...)
```

The original failure route stored by `Spush_back()` is therefore recovered before failure propagates outward.

---

# 26. Common Success Handler

All successful compiled goals eventually reach:

```c
success:
```

The first distinction is:

```c
if(np[th] == 0)
```

This tells SCBM whether another compiled success continuation remains.

There are therefore two cases.

---

# 27. Success with No Compiled Continuation

If:

```text
np == 0
```

the current compiled SCBM chain has completed.

SCBM then executes the remaining Prolog goals:

```c
if(Jprove_all(rest,Jget_sp(th),th) == YES)
    return(YES);
```

If the remaining goals succeed:

```text
return YES
```

The entire query succeeds.

---

# 28. Failure of the Remaining Goals

Suppose the compiled `append/3` succeeded, but some goal in `rest` later fails.

SCBM then resumes from the current backtracking environment:

```c
next = back_goto[rp[th]][th];
clause = Sget_choice(th);
arglist = Sget_arg(th);
Spush_next(&&success,th);
goto *next;
```

This is where Prolog's ability to ask for another solution is implemented.

SCBM retrieves:

```text
failure continuation
choice number
saved arguments
```

and resumes the appropriate generated code.

Thus successful completion of one predicate does not destroy the possibility of later backtracking.

---

# 29. Success with a Pending Continuation

If:

```text
np != 0
```

there is still a compiled goal waiting for control.

SCBM executes:

```c
next = next_goto[np[th]][th];
Spop_next(th);
clause = Sget_choice(th);
goto *next;
```

This is analogous to returning from a subroutine.

But instead of a hardware or C return stack, SCBM explicitly selects the continuation address.

Conceptually:

```text
current goal succeeds
       |
       v
next = next_goto[np]
       |
pop next
       |
       v
goto *next
```

For the recursive `append/3` example, this eventually reaches:

```text
append_3_1_1
```

---

# 30. Common Failure Handler

Failure reaches:

```c
allfail:
```

The first test is:

```c
if(rp[th] == 0)
    return(NO);
```

If no backtracking environment exists, the entire computation has failed.

This is the final Prolog failure condition.

---

# 31. Backtracking to an Earlier Environment

If:

```text
rp != 0
```

SCBM has an earlier alternative.

The generated code performs:

```c
next = back_goto[rp[th]][th];
np[th] = Sget_np(th);
Spop_back(th);
arglist = Sget_arg(th);
goto *next;
```

Conceptually:

```text
failure
   |
   v
find current backtracking continuation
   |
restore saved np
   |
pop backtracking level
   |
restore argument list
   |
   v
goto alternative
```

This is the core SCBM backtracking operation.

---

# 32. Why `np` Is Restored

A backtracking environment records:

```c
back_stack[rp][NP_SCBM][th]
```

When failure propagates, SCBM performs:

```c
np[th] = Sget_np(th);
```

This discards success continuations that belong to the failed branch.

For example:

```text
A
 |
 B
 |
 C fails
```

continuations installed while evaluating `B` or `C` must not survive if execution returns to an alternative belonging to `A`.

The saved `np` identifies the success-continuation depth that belongs to that backtracking environment.

---

# 33. Built-in Predicate Path

The generated SCBM function also contains:

```c
builtin_call:
```

with:

```c
if(Jcallsubr(subr_number,arglist,NIL,th) == YES)
    goto success;
else
    goto allfail;
```

This gives built-in predicates the same continuation semantics as compiled predicates.

A built-in predicate therefore does not need its own special control model.

Its result is reduced to the two fundamental SCBM outcomes:

```text
YES -> success
NO  -> allfail
```

---

# 34. Complete Forward Execution Example

Consider:

```prolog
append([1], [2], X).
```

The second clause is selected.

The head unification produces approximately:

```text
A = 1
X1 = []
Y = [2]
X = [1|Z]
```

The recursive body becomes:

```prolog
append([], [2], Z)
```

Before entering it, SCBM:

```text
pushes a backtracking environment
saves local variables
pushes append_3_1_1 as success continuation
```

The recursive call enters clause 0:

```prolog
append([], X, X)
```

and obtains:

```text
Z = [2]
```

The recursive call succeeds.

SCBM takes the success continuation:

```text
append_3_1_1
```

which immediately transfers to:

```text
success
```

The final result is therefore:

```prolog
X = [1,2]
```

---

# 35. Recursive Control Flow

The essential generated control flow can be visualized as:

```text
append/3
   |
   v
clause 0
   |
   | failure
   v
clause 1
   |
   | unify head
   v
construct append(X,Y,Z)
   |
   v
Spush_back
   |
   v
save local variables
   |
   v
Spush_next(after_recursive_call)
   |
   v
goto append/3
   |
   | recursive success
   v
success
   |
   v
pop next continuation
   |
   v
after_recursive_call
   |
   v
success
```

Failure follows the opposite path through the explicit backtracking stack.

---

# 36. Relationship Between the Two SCBM Stacks

The generated `append/3` clearly shows why SCBM maintains two different control structures.

## Success stack

Controlled by:

```text
np
next_goto
next_stack
```

It answers:

```text
Where should execution continue if this goal succeeds?
```

For example:

```text
append_3_1_1
```

---

## Backtracking stack

Controlled by:

```text
rp
back_goto
back_goto1
back_stack
```

It answers:

```text
Where should execution continue if this computation later fails?
```

For example:

```text
append_3_2
```

These are fundamentally different continuations.

A recursive Prolog goal normally requires both.

---

# 37. `next_stack` and C Local Variables

One subtle but important aspect of generated SCBM code is:

```c
next_stack[np[th]+1][...][th]
```

C local variables are convenient while control flows normally through generated labels.

However, they cannot by themselves represent a Prolog environment whose lifetime spans:

```text
recursive execution
success continuation
backtracking
```

Therefore values such as:

```text
X
Y
A
Z
```

are copied into an SCBM-managed continuation frame.

On normal execution:

```text
C locals -> next_stack
```

On backtracking re-entry:

```text
next_stack -> C locals
```

The generated `back` and `join` labels implement this transformation explicitly.

---

# 38. The Meaning of the Generated Labels

For `append/3`, label names have a systematic interpretation.

For example:

```text
mappend_3_1
```

means approximately:

```text
predicate append
arity 3
clause 1
```

while:

```text
mappend_3_1_0
```

identifies a body goal inside that clause.

Likewise:

```text
mappend_3_1_0back
```

is its backtracking-entry path,

and:

```text
mappend_3_1_0join
```

is the common path after environment reconstruction.

Finally:

```text
mappend_3_1_1
```

is the continuation after successful execution of the body goal.

This naming scheme makes the generated C control-flow graph visible directly in the source code.

---

# 39. SCBM Does Not Simulate the C Call Stack

A conventional implementation might recursively call a C function:

```text
append()
    -> append()
        -> append()
```

SCBM instead produces:

```text
append label
    |
    v
append label
    |
    v
append label
```

while explicit SCBM data structures contain the information normally associated with procedure calls.

In simplified form:

```text
C call stack                    SCBM

return address        ->        next_goto
local continuation    ->        next_stack
failure return        ->        back_goto
backtracking state    ->        back_stack
call depth/state      ->        np / rp
```

This allows Prolog's non-deterministic control flow to be represented directly using native C jumps.

---

# 40. Why `append/3` Is an Important Example

Although `append/3` consists of only two clauses, it already contains:

```text
base clause
recursive clause
shared logical variables
recursive invocation
success continuation
failure continuation
argument reconstruction
environment preservation
backtracking state
```

It therefore demonstrates the essential structure of SCBM-generated code without requiring a large example such as Queens.

The recursive source:

```prolog
append([A|X],Y,[A|Z]) :-
    append(X,Y,Z).
```

is transformed into a native control-flow graph consisting primarily of:

```text
unification
explicit continuation storage
computed goto
```

rather than an instruction stream for a virtual machine.

---

# 41. Summary

SCBM compiles Prolog control flow directly into C labels and jumps.

For `append/3`, the main transformation can be summarized as follows:

```text
Prolog clause selection
        ->
C switch and labels

Prolog head unification
        ->
Junify_* calls

Prolog success
        ->
next_goto / success

Prolog failure
        ->
back_goto / allfail

Prolog recursive call
        ->
save environment
push success continuation
goto predicate label

Prolog backtracking
        ->
restore SCBM environment
goto saved failure continuation
```

The generated C code therefore preserves the essential semantics of Prolog while avoiding a traditional bytecode dispatch loop.

The central idea is simple:

> **Success and failure are explicit continuations, and both are compiled into native C control flow.**

`append/3` shows this mechanism particularly clearly.

Its Prolog recursion:

```prolog
append([A|X],Y,[A|Z]) :-
    append(X,Y,Z).
```

becomes an SCBM cycle:

```text
save environment
      |
push failure continuation
      |
push success continuation
      |
goto append
      |
   success
      |
goto saved continuation
```

while failure follows the independently maintained backtracking path.

This separation of success continuation and failure continuation is the foundation of the SCBM execution model.

# 42. All codes

```
#include "jump.h"
static int c_mappend(int arglist, int rest, int th);
static int user_scbm(int pred, int arity, int clause, int arglist, int rest, int th);
static int c_mappend(int arglist, int rest, int th){
int n;
n = Jlength(arglist);
Ssave_arg(arglist,th);
return(user_scbm(0,n,0,arglist,rest,th));
}

void init_tpredicate(void){
(deftpred)("mappend",c_mappend,3,1);
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
case 0: goto mappend;
}
mappend:
switch(arity){
case 3: goto mappend_3;
default: goto allfail;
}
mappend_3:
Jinc_proof(th);
switch(clause){
case 0: goto mappend_3_0;
case 1: goto mappend_3_1;
case 2: goto mappend_3_2;
default: goto allfail;
}
mappend_3_0:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
Srelease(th);
varX = Jmakevariant(th);
Sinc_choice(th);
Sset_back(&&mappend_3_1,th);
if(Junify_nil(arg1,th) == YES && Junify_var(arg2,varX,th) == YES && Junify_var(arg3,varX,th) == YES)
{
goto success;
}
mappend_3_1:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
Srelease(th);
varX = Jmakevariant(th);
varY = Jmakevariant(th);
varA = Jmakevariant(th);
varZ = Jmakevariant(th);
Sinc_choice(th);
Sset_back(&&mappend_3_2,th);
if(Junify_pair(arg1,Jwlistcons(varA,varX,th),th) == YES && Junify_var(arg2,varY,th) == YES && Junify_pair(arg3,Jwlistcons(varA,varZ,th),th) == YES)
{
mappend_3_1_0:
arglist = Jwlistcons(varX,Jwlistcons(varY,Jwlistcons(varZ,NIL,th),th),th);
Spush_back(&&mappend_3_2,arglist,th);
goto mappend_3_1_0join;
mappend_3_1_0back:
varX= next_stack[np[th]+1][1][th];
varY= next_stack[np[th]+1][2][th];
varA= next_stack[np[th]+1][3][th];
varZ= next_stack[np[th]+1][4][th];
mappend_3_1_0join:
next_stack[np[th]+1][1][th] = varX;
next_stack[np[th]+1][2][th] = varY;
next_stack[np[th]+1][3][th] = varA;
next_stack[np[th]+1][4][th] = varZ;
Spush_next(&&mappend_3_1_1,th);
clause = Sget_choice(th);
goto mappend_3;
mappend_3_1_1:
goto success;
}
mappend_3_2:
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


```