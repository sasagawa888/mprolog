# SCBM API Specification

## 1. Overview

SCBM (**Success Continuation and Backtracking Machine**) manages the execution state required for Prolog conjunctions, recursion, clause selection, disjunctions, success continuations, and backtracking.

The main SCBM frame is addressed by conjunction depth, recursion depth, and thread:

```text
scbmstack[CONJ][RECUR][FIELD][THREAD]
```

The current positions are held in:

```c
scp[CONJ][th]
scp[RECUR][th]
```

SCBM also uses three auxiliary stacks:

```c
next_stack[success_depth][conjunction][thread]
back_stack[recursion_depth][conjunction][thread]
var_stack[variable_depth][thread]
```

- `next_stack` stores success continuations.
- `back_stack` stores active failure continuations.
- `back_stack1` preserves the original failure continuation of each recursion frame.
- `var_stack` preserves generated variables across continuation jumps.

---

## 2. SCBM Frame Fields

| Field | Description |
|---|---|
| `SP_SCBM` | Saved variable-binding stack position |
| `CHOICE_SCBM` | Current clause-selection number |
| `WP_SCBM` | Saved work-area pointer |
| `AC_SCBM` | Saved argument or temporary-area counter |
| `DISJ_SCBM` | Choice number inside a disjunction |
| `CHOICE_BACKUP_SCBM` | Clause-selection number saved before entering a disjunction |
| `ARGLIST_SCBM` | Saved argument list |
| `VP_SCBM` | Saved variable-stack position |
| `NP_SCBM` | Saved success-continuation stack position |
| `SUCC_SCBM` | Success state of the conjunction frame |

`UNBIND` indicates that a field has not yet been assigned a valid value.

---

## 3. Frame Management

### `push_conj`

```c
int push_conj(int th);
```

Creates a new conjunction frame.

It increments `scp[CONJ][th]`, resets `scp[RECUR][th]` to zero, saves the current execution state, and initializes clause and disjunction fields.

Saved values:

```c
SP_SCBM = sp[th]
WP_SCBM = wp[th]
AC_SCBM = ac[th]
```

Initialized values:

```c
CHOICE_SCBM = 0
DISJ_SCBM = 0
CHOICE_BACKUP_SCBM = 0
ARGLIST_SCBM = UNBIND
```

Raises `RESOURCE_ERR` if the conjunction depth reaches `CONJSIZE`.

---

### `discard_conj`

```c
int discard_conj(int th);
```

Discards the current conjunction frame and returns to the enclosing frame.

After decrementing the conjunction depth, it restores the recursion depth from the enclosing frame:

```c
scp[RECUR][th] =
    scbmstack[scp[CONJ][th]][0][SUCC_SCBM][th];
```

The caller must ensure that an enclosing conjunction frame exists.

---

### `push_recur`

```c
int push_recur(int arglist, int vp, int np, int th);
```

Creates a recursion or choice-point frame within the current conjunction.

Saved values:

```c
SP_SCBM = sp[th]
WP_SCBM = wp[th]
AC_SCBM = ac[th]
ARGLIST_SCBM = arglist
VP_SCBM = vp
NP_SCBM = np
```

Initialized values:

```c
CHOICE_SCBM = 0
DISJ_SCBM = 0
CHOICE_BACKUP_SCBM = 0
```

Raises `RESOURCE_ERR` if the recursion depth reaches `RECURSIZE`.

---

### `pop_recur`

```c
int pop_recur(int th);
```

Removes the current recursion frame by decrementing `scp[RECUR][th]`.

Recursion depth zero is the base frame and cannot be removed. A `RESOURCE_ERR` is raised if no removable recursion frame exists.

---

## 4. Clause Choice and State Restoration

### `inc_choice`

```c
int inc_choice(int th);
```

Increments `CHOICE_SCBM` in the current frame. It is normally called before installing the next clause as a failure continuation.

---

### `get_choice`

```c
int get_choice(int th);
```

Returns `CHOICE_SCBM` from the current frame.

This function also increments `proof[th]`, so it is not a pure getter.

---

### `release`

```c
int release(int th);
```

Restores the variable-binding and temporary-area state saved in the current frame:

```c
unbind(SP_SCBM, th);
ac[th] = AC_SCBM;
```

Although `WP_SCBM` is saved, the supplied implementation does not restore `wp[th]` in this function.

---

## 5. Argument and Saved-State Access

### `save_arg`

```c
int save_arg(int arglist, int th);
```

Stores `arglist` in `ARGLIST_SCBM` of the current frame.

---

### `get_arg`

```c
int get_arg(int th);
```

Returns `ARGLIST_SCBM` from the current frame. It returns `UNBIND` if no argument list has been stored.

---

### `get_vp`

```c
int get_vp(int th);
```

Returns the saved `VP_SCBM` value from the current recursion frame.

---

### `get_np`

```c
int get_np(int th);
```

Returns the saved `NP_SCBM` value from the current recursion frame.

---

### `get_scp`

```c
int get_scp(int type, int th);
```

Returns the requested SCBM stack position:

```c
scp[type][th]
```

`type` is normally `CONJ` or `RECUR`.

---

### `get_succ`

```c
int get_succ(int th);
```

Returns the success state stored in the base recursion frame of the current conjunction:

```c
scbmstack[scp[CONJ][th]][0][SUCC_SCBM][th]
```

---

### `arity_count`

```c
int arity_count(int arglist);
```

Returns the arity of an argument list. If the arity has not yet been cached, the function computes the list length and stores it in the argument-list object.

---

## 6. Success Continuation API

### `Jpush_next`

```c
void Jpush_next(void *cont, int th);
```

Pushes a success-continuation address onto `next_stack` for the current conjunction frame.

```c
np[Jget_scp(CONJ, th)][th]++;
next_stack
    [np[Jget_scp(CONJ, th)][th]]
    [Jget_scp(CONJ, th)]
    [th] = cont;
```

The continuation is normally the address of a GCC computed-goto label.

---

### `Jpop_next`

```c
void Jpop_next(int th);
```

Removes the top success continuation by decrementing the current `np` value.

```c
np[Jget_scp(CONJ, th)][th]--;
```

The caller must ensure that the stack is not empty.

---

## 7. Failure Continuation API

### `Jpush_back`

```c
void Jpush_back(
    void *cont,
    int arglist,
    int vp,
    int np,
    int th
);
```

Creates a recursion or choice-point frame and installs its failure continuation.

It first calls:

```c
Jpush_recur(arglist, vp, np, th);
```

It then stores `cont` in both continuation stacks:

```c
back_stack[RECUR][CONJ][th]  = cont;
back_stack1[RECUR][CONJ][th] = cont;
```

`back_stack` is the active failure continuation. `back_stack1` preserves the original continuation of the frame.

---

### `Jset_back`

```c
void Jset_back(void *cont, int th);
```

Replaces the active failure continuation of the current recursion frame.

It does not create or remove a frame.

Typical use:

```c
Jset_back(&&next_clause, th);
```

If the current clause fails, execution continues at `next_clause`.

---

### `Jpop_back`

```c
void Jpop_back(int th);
```

Restores the active failure continuation from `back_stack1`.

```c
back_stack[RECUR][CONJ][th] =
    back_stack1[RECUR][CONJ][th];
```

Despite its name, this function does not remove a recursion frame. Frame removal is performed by `pop_recur` or `Jpop_recur`.

---

## 8. Temporary Variable Stack

### `Jpush_var`

```c
void Jpush_var(int value, int th);
```

Pushes a generated variable or temporary value onto `var_stack`.

```c
vp[th]++;
var_stack[vp[th]][th] = value;
```

---

### `Jpop_var`

```c
int Jpop_var(int th);
```

Returns and removes the most recently saved value.

```c
int value = var_stack[vp[th]][th];
vp[th]--;
return value;
```

Values must be restored in reverse order because `var_stack` is a LIFO stack.

---

## 9. Typical Control Sequences

### Success continuation

```c
Jpush_next(&&next_goal, th);
goto called_predicate;

next_goal:
    /* continue after success */
```

The common `success` handler retrieves the top entry from `next_stack`, calls `Jpop_next`, and jumps to the saved label.

### Clause backtracking

```c
Jpush_back(&&outer_failure, arglist, vp[th], np_value, th);

clause_1:
Jset_back(&&clause_2, th);
/* try clause 1 */

clause_2:
Jset_back(&&clause_3, th);
/* try clause 2 */

clause_3:
Jpop_back(th);
goto allfail;
```

`Jset_back` installs clause-local alternatives. `Jpop_back` restores the enclosing failure continuation after all local alternatives have been exhausted.

### Variable preservation

```c
Jpush_var(varX, th);
Jpush_var(varY, th);
Jpush_next(&&continuation, th);
goto called_predicate;

continuation:
varY = Jpop_var(th);
varX = Jpop_var(th);
```

---

## 10. API Summary

| Function | Purpose |
|---|---|
| `push_conj` | Creates a conjunction frame |
| `discard_conj` | Discards the current conjunction frame |
| `push_recur` | Creates a recursion or choice-point frame |
| `pop_recur` | Removes the current recursion frame |
| `inc_choice` | Advances the clause-selection number |
| `get_choice` | Returns the current clause-selection number |
| `release` | Restores bindings and temporary-area state |
| `save_arg` / `get_arg` | Stores and retrieves the current argument list |
| `get_vp` / `get_np` | Retrieves saved stack positions |
| `get_scp` | Returns a conjunction or recursion depth |
| `get_succ` | Returns the conjunction success state |
| `arity_count` | Returns and caches argument-list arity |
| `Jpush_next` / `Jpop_next` | Manages success continuations |
| `Jpush_back` | Creates a backtracking frame and installs its continuation |
| `Jset_back` | Replaces the active failure continuation |
| `Jpop_back` | Restores the original failure continuation |
| `Jpush_var` / `Jpop_var` | Preserves temporary variables across jumps |

SCBM separates forward execution from backtracking: `next_stack` controls execution after success, while `back_stack` and the SCBM frames control restoration and transfer after failure or forced backtracking.

# Code Generation for `nondet` Predicates

## 1. Predicate Classification in M-Prolog

M-Prolog classifies predicates according to their characteristics and generates different C code for each type.

The current predicate types are as follows:

| Type     | Description                                                                                |
| -------- | ------------------------------------------------------------------------------------------ |
| `nondet` | A nondeterministic predicate that may produce multiple solutions and requires backtracking |
| `det`    | A deterministic predicate that produces at most one solution                               |
| `tail`   | A predicate that can be optimized using tail recursion                                     |
| `dyn`    | A dynamic predicate that may be added or removed at runtime                                |

In the future, M-Prolog will introduce an additional predicate type whose input and output modes can be inferred through mode analysis.

This type is provisionally called `mut`, meaning **mutant type**.

This document explains code generation for `nondet` predicates using SCBM, one of the main distinguishing features of M-Prolog.

The `nondet` category includes both predicates with multiple clauses and recursive predicates that create multiple choice points during execution.

---

## 2. Overview of SCBM

SCBM is an execution mechanism for explicitly managing two kinds of control information required by Prolog:

1. The location to continue execution after a predicate succeeds
2. The location to resume execution after a predicate fails

The former is called the **success continuation**, and the latter is called the **failure continuation**.

M-Prolog stores these two continuations in separate stacks.

| Continuation         | Storage                      |
| -------------------- | ---------------------------- |
| Success continuation | `next_stack`                 |
| Failure continuation | `SCBM_stack` or `back_stack` |

Predicate execution is controlled not only through ordinary C function calls, but also through direct jumps between generated labels using `goto`.

---

## 3. One Large C Function

The bodies of `nondet` predicates are generated inside one large C function.

For user-defined predicates, the function has the following general form:

```c
static int user_scbm(
    int pred,
    int arity,
    int clause,
    int arglist,
    int rest,
    int th
);
```

The arguments have the following meanings:

| Argument  | Description                                     |
| --------- | ----------------------------------------------- |
| `pred`    | Predicate number                                |
| `arity`   | Number of predicate arguments                   |
| `clause`  | Clause number from which execution begins       |
| `arglist` | List of actual arguments                        |
| `rest`    | Remaining Prolog goals after the predicate call |
| `th`      | Prolog execution thread number                  |

Each predicate and clause is represented as a label inside the large function rather than as an independent C function.

For example:

```c
color:
color_1:
color_1_0:
color_1_1:
color_1_2:
success:
allfail:
```

The initial execution position is selected by `switch` statements that inspect `pred`, `arity`, and `clause`.

```c
switch(pred){
case 0: goto color;
}
```

The arity is then selected:

```c
color:
switch(arity){
case 1: goto color_1;
default: goto allfail;
}
```

Finally, the clause is selected:

```c
color_1:
switch(clause){
case 0: goto color_1_0;
case 1: goto color_1_1;
case 2: goto color_1_2;
default: goto allfail;
}
```

This structure expresses predicate calls, clause selection, and re-execution after backtracking as jumps between labels.

---

## 4. Computed Goto

SCBM uses computed goto, a GCC extension.

A label address is obtained using the following syntax:

```c
&&success
&&color_1_1
```

Execution can jump to a stored label address using:

```c
goto *next;
```

Instead of reconstructing every backtracking destination through a `switch` statement, SCBM can jump directly to a label address saved at runtime.

This makes it possible to store success and failure continuations as actual C execution positions.

---

## 5. Success and Failure Continuations

A Prolog predicate call must maintain at least two possible destinations.

### 5.1 Success Continuation

The success continuation indicates where execution should continue when the current goal succeeds.

Success continuations are stored in `next_stack`, which is managed by the stack pointer `np`.

```c
Jpush_next(&&success, th);
```

In this example, the `success` label is registered as the initial success continuation.

When unification or execution of a clause body succeeds, control normally moves to the success handler:

```c
goto success;
```

### 5.2 Failure Continuation

The failure continuation indicates where execution should resume when the current clause or goal fails.

Before executing `color(red).`, for example, the label for the next clause, `color(green).`, is registered as its failure continuation.

```c
Jset_back(&&color_1_1, th);
```

If the first clause fails, execution can therefore continue at `color_1_1`.

A failure continuation contains not only the jump destination, but also the execution state required to resume processing from that position.

---

## 6. Data Stored in the SCBM Stack

Backtracking requires more than returning to a previous code position.

Variable bindings, work areas, arguments, clause numbers, success continuations, and other state modified during execution must be restored to the values they had when the choice point was created.

The SCBM stack stores the following information:

| Field                | Description                                                 |
| -------------------- | ----------------------------------------------------------- |
| `SP_SCBM`            | Position of the variable-binding stack                      |
| `CHOICE_SCBM`        | Current clause-selection number                             |
| `WP_SCBM`            | Work-area pointer                                           |
| `AC_SCBM`            | Argument-area or temporary-area counter                     |
| `DISJ_SCBM`          | Choice number inside a disjunction                          |
| `CHOICE_BACKUP_SCBM` | Clause-selection number saved before entering a disjunction |
| `ARGLIST_SCBM`       | Argument list at the time of the call                       |
| `VP_SCBM`            | Variable-area pointer                                       |
| `NP_SCBM`            | Saved success-continuation position                         |
| `SUCC_SCBM`          | Success state of the conjunction frame                      |

By restoring these values, M-Prolog can resume execution from an earlier choice point.

---

## 7. A Simple Nondeterministic Predicate

Consider the following predicate:

```prolog
color(red).
color(green).
color(blue).
```

This predicate contains three clauses.

For the following query:

```prolog
?- color(X).
```

the first result is:

```text
X = red
```

When the user enters a semicolon to request another solution, forced backtracking occurs, producing the remaining results:

```text
X = red ;
X = green ;
X = blue ;
no
```

---

## 8. Entry Function

The generated entry function saves the Prolog argument list and calls the large SCBM function.

```c
static int c_color(int arglist, int rest, int th)
{
    int n;

    n = Jlength(arglist);
    Jsave_arg(arglist, th);

    return user_scbm(0, n, 0, arglist, rest, th);
}
```

In this call:

* The predicate number is `0`
* The initial clause number is `0`
* The actual arguments are passed through `arglist`

`Jsave_arg` saves the original argument list so that it can be restored during backtracking.

---

## 9. Predicate Registration

The generated C function is registered with the Prolog system during initialization.

```c
void init_tpredicate(void)
{
    (deftpred)("color", c_color, 1, 1);
}
```

This associates the Prolog predicate `color/1` with the C function `c_color`.

---

## 10. Clause Dispatch

At the beginning of `user_scbm`, the success-continuation stack and variable area are initialized, and the top-level success continuation is registered.

```c
np[Jget_scp(CONJ, th)][th] = 0;
vp[th] = 0;

Jpush_next(&&success, th);
```

The execution position is then selected in the order of predicate number, arity, and clause number.

```c
switch(pred){
case 0: goto color;
}
```

```c
color:
switch(arity){
case 1: goto color_1;
default: goto allfail;
}
```

```c
color_1:
switch(clause){
case 0: goto color_1_0;
case 1: goto color_1_1;
case 2: goto color_1_2;
default: goto allfail;
}
```

---

## 11. Execution of Individual Clauses

The first clause is generated as follows:

```c
color_1_0:
arg1 = Jcar(arglist);
Jrelease(th);
Jinc_choice(th);
Jset_back(&&color_1_1, th);

if(Junify_atom(arg1, Jmakeconst("red"), th) == YES)
{
    goto success;
}
```

The operations are performed in the following order:

1. Extract the first argument from `arglist`
2. Release temporary areas created by the previous clause
3. Advance the current clause-selection number
4. Register the next clause as the failure continuation
5. Unify the argument with the atom `red`
6. Jump to `success` if unification succeeds

The second clause has the same structure:

```c
color_1_1:
arg1 = Jcar(arglist);
Jrelease(th);
Jinc_choice(th);
Jset_back(&&color_1_2, th);

if(Junify_atom(arg1, Jmakeconst("green"), th) == YES)
{
    goto success;
}
```

For the third clause, there is no ordinary clause following it. Therefore, a terminal label is registered as the failure continuation.

```c
color_1_2:
arg1 = Jcar(arglist);
Jrelease(th);
Jinc_choice(th);
Jset_back(&&color_1_3, th);

if(Junify_atom(arg1, Jmakeconst("blue"), th) == YES)
{
    goto success;
}
```

When every clause has been tried, execution reaches:

```c
color_1_3:
Jpop_back(th);
goto allfail;
```

The failure continuation created for this predicate is removed, and control moves to the outer failure handler.

---

## 12. Processing at `success`

When a predicate or clause succeeds, control moves to the `success` label.

```c
success:
if(np[Jget_scp(CONJ, th)][th] == 0){
    if(Jprove_all(rest, Jget_sp(th), th) == YES)
        return YES;

    next =
        back_stack
        [Jget_scp(RECUR, th)]
        [Jget_scp(CONJ, th)]
        [th];

    clause = Jget_choice(th);
    arglist = Jget_arg(th);

    Jpush_next(&&success, th);
    goto *next;
}
else{
    next =
        next_stack
        [np[Jget_scp(CONJ, th)][th]]
        [Jget_scp(CONJ, th)]
        [th];

    Jpop_next(th);
    clause = Jget_choice(th);

    goto *next;
}
```

The `success` handler has two main cases.

### 12.1 A Success Continuation Remains

If a success continuation remains in `next_stack`, its destination is retrieved.

```c
next =
    next_stack
    [np[Jget_scp(CONJ, th)][th]]
    [Jget_scp(CONJ, th)]
    [th];
```

The used continuation is then removed from the stack.

```c
Jpop_next(th);
```

Finally, execution jumps to the stored continuation.

```c
goto *next;
```

This moves execution to the next generated goal, such as the following goal in a conjunction.

Consider:

```prolog
p(X) :- q(X), r(X).
```

When `q(X)` succeeds, the starting position of `r(X)` is stored as its success continuation.

Execution therefore jumps directly to the label for `r(X)` instead of returning through an ordinary C function call.

### 12.2 No Success Continuation Remains

If `np` is zero, there is no remaining success continuation in the current SCBM frame.

```c
if(np[Jget_scp(CONJ, th)][th] == 0)
```

The remaining Prolog goals stored in `rest` are then executed.

```c
if(Jprove_all(rest, Jget_sp(th), th) == YES)
    return YES;
```

If every remaining goal succeeds, `YES` is returned as the result of the entire query.

---

## 13. Forced Backtracking after Success

In Prolog, another solution may be requested even after a solution has already been found.

For example:

```prolog
?- color(X).
X = red ;
```

When the user enters a semicolon, the current solution is valid, but the system must search for another one.

This differs from ordinary failure.

`color(red)` has already succeeded. However, the system intentionally follows the saved failure continuation to explore another branch. This operation is called **forced backtracking**.

When `Jprove_all` reports a solution and another solution is requested, the current success is not treated as the final result. Instead, the saved backtracking destination is obtained.

```c
next =
    back_stack
    [Jget_scp(RECUR, th)]
    [Jget_scp(CONJ, th)]
    [th];
```

The clause number and original argument list are restored.

```c
clause = Jget_choice(th);
arglist = Jget_arg(th);
```

A success continuation is registered again so that a later solution can return to `success`.

```c
Jpush_next(&&success, th);
```

Execution then jumps to the saved failure continuation.

```c
goto *next;
```

After `color(red)` succeeds, the saved failure continuation is:

```c
&&color_1_1
```

Forced backtracking therefore transfers control to `color_1_1`, where unification with `green` is attempted.

Forced backtracking is not an error-handling operation.

It is a normal control operation that moves from an already successful execution path to another saved alternative.

---

## 14. Processing at `allfail`

When the current clause, predicate, or conjunction fails, control moves to the `allfail` label.

```c
allfail:
if(Jget_scp(RECUR, th) == 0){
    Jdiscard_conj(th);
    return NO;
}

next =
    back_stack
    [Jget_scp(RECUR, th)]
    [Jget_scp(CONJ, th)]
    [th];

Jpop_recur(th);
Jpop_next(th);

clause = Jget_choice(th);
arglist = Jget_arg(th);
vp[th] = Jget_vp(th);
np[Jget_scp(CONJ, th)][th] = Jget_np(th);

goto *next;
```

### 14.1 No Outer Choice Point Exists

If no recursive or backtracking frame exists, there are no remaining alternatives.

```c
if(Jget_scp(RECUR, th) == 0)
```

The current conjunction frame is discarded, and `NO` is returned as the final result.

```c
Jdiscard_conj(th);
return NO;
```

### 14.2 An Outer Choice Point Exists

If a failure continuation exists, its destination is retrieved from the SCBM stack.

```c
next =
    back_stack
    [Jget_scp(RECUR, th)]
    [Jget_scp(CONJ, th)]
    [th];
```

The completed recursion frame and success continuation are then removed.

```c
Jpop_recur(th);
Jpop_next(th);
```

The state required by the backtracking destination is restored.

```c
clause = Jget_choice(th);
arglist = Jget_arg(th);
vp[th] = Jget_vp(th);
np[Jget_scp(CONJ, th)][th] = Jget_np(th);
```

The restored information includes:

* The next clause number
* The argument list at the time of the call
* The variable-area position
* The success-continuation stack position

Execution finally jumps to the saved failure continuation.

```c
goto *next;
```

This allows execution to resume from a caller predicate or an earlier choice point.

---

## 15. Ordinary Failure and Forced Backtracking

Ordinary failure and forced backtracking both use failure continuations, but they occur for different reasons.

| Operation           | Meaning                                                            |
| ------------------- | ------------------------------------------------------------------ |
| Ordinary failure    | Unification or execution of a body goal actually failed            |
| Forced backtracking | The current solution succeeded, but another solution was requested |
| Final failure       | Every saved alternative has been exhausted                         |

For example:

```prolog
?- color(white).
```

Unification with `red`, `green`, and `blue` all fails. This is ordinary failure.

In contrast:

```prolog
?- color(X).
X = red ;
```

unification with `red` succeeded. However, the user requested another solution, so execution intentionally follows the next failure continuation. This is forced backtracking.

When another solution is requested after `blue`, every clause has already been exhausted, and the final result is `no`.

---

# Recursive `nondet` Predicates

## 16. Recursion Uses the Same SCBM Mechanism

Consider the following recursive predicates:

```prolog
plus(0, Y, Y).
plus(s(X), Y, s(Z)) :-
    plus(X, Y, Z).
```

```prolog
times(0, _, 0).
times(s(X), Y, Z) :-
    times(X, Y, Z1),
    plus(Z1, Y, Z).
```

These predicates require both clause selection and recursive calls inside clause bodies.

SCBM does not need a fundamentally different execution mechanism for recursive predicates.

Both nonrecursive and recursive predicates can be expressed using:

* The location to continue after success
* The location to return to after failure

Recursive calls are therefore handled by stacking success and failure continuations.

---

## 17. Entry Functions for Recursive Predicates

An ordinary entry function is generated for each predicate.

```c
static int c_plus(int arglist, int rest, int th)
{
    int n;

    n = Jlength(arglist);
    Jsave_arg(arglist, th);

    return user_scbm(0, n, 0, arglist, rest, th);
}
```

```c
static int c_times(int arglist, int rest, int th)
{
    int n;

    n = Jlength(arglist);
    Jsave_arg(arglist, th);

    return user_scbm(1, n, 0, arglist, rest, th);
}
```

Rather than generating a separate recursive C function for each predicate, the predicate number selects a different label inside the same `user_scbm` function.

---

## 18. Base Clause of `plus/3`

The base clause is:

```prolog
plus(0, Y, Y).
```

Its generated code has the following general structure:

```c
plus_3_0:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist, 2);
arg3 = Jnth(arglist, 3);

Jrelease(th);

varY = Jmakevariant(th);

Jinc_choice(th);
Jset_back(&&plus_3_1, th);

if(
    Junify_int(arg1, Jmakeint(0), th) == YES &&
    Junify_var(arg2, varY, th) == YES &&
    Junify_var(arg3, varY, th) == YES
){
    goto success;
}
```

In this clause, the second and third arguments correspond to the same Prolog variable, `Y`.

The generated code therefore creates one internal variable, `varY`, and unifies both arguments with it.

```c
Junify_var(arg2, varY, th)
Junify_var(arg3, varY, th)
```

The recursive clause label `plus_3_1` is registered as the failure continuation so that it can be attempted if the base clause fails.

```c
Jset_back(&&plus_3_1, th);
```

---

## 19. Recursive Clause of `plus/3`

The recursive clause is:

```prolog
plus(s(X), Y, s(Z)) :-
    plus(X, Y, Z).
```

Head unification requires the following operations:

1. Unify the first argument with `s(X)`
2. Unify the second argument with `Y`
3. Unify the third argument with `s(Z)`
4. Invoke the body goal `plus(X,Y,Z)`

Before the recursive call, M-Prolog saves both:

* The success continuation used when the recursive call succeeds
* The failure continuation used when the recursive call fails

Conceptually, execution proceeds as follows:

```text
plus(s(X),Y,s(Z))
        |
        | head unification succeeds
        v
save success continuation
save failure continuation
        |
        v
plus(X,Y,Z)
```

If the recursive call succeeds, execution returns through the saved success continuation.

If it fails, the saved failure continuation is used, and the caller's variable area, arguments, clause number, and other execution state are restored.

---

## 20. Conjunction in `times/3`

The recursive clause of `times/3` contains two body goals.

```prolog
times(s(X), Y, Z) :-
    times(X, Y, Z1),
    plus(Z1, Y, Z).
```

The first goal is:

```prolog
times(X, Y, Z1)
```

After this goal succeeds, execution must continue with:

```prolog
plus(Z1, Y, Z)
```

Before calling `times(X,Y,Z1)`, the starting position of `plus(Z1,Y,Z)` is therefore saved in `next_stack` as a success continuation.

Conceptually:

```text
times(X,Y,Z1)
      |
      | success
      v
plus(Z1,Y,Z)
      |
      | success
      v
success continuation of caller
```

If `plus(Z1,Y,Z)` fails, M-Prolog must search for another solution of `times(X,Y,Z1)`.

The failure continuation created by `times(X,Y,Z1)` must therefore remain available even after that call initially succeeds.

This allows execution to backtrack from the later `plus/3` call into the earlier `times/3` call.

---

## 21. Backtracking across a Conjunction

Consider the conjunction:

```prolog
A, B
```

Its basic SCBM execution is as follows.

### Step 1: Execute `A`

Before calling `A`, the starting position of `B` is saved as a success continuation.

```text
next_stack <- address of B
```

### Step 2: `A` Succeeds

When `A` succeeds, control moves to `success`.

The `success` handler retrieves the starting position of `B` from `next_stack` and jumps to it.

### Step 3: Execute `B`

If `B` succeeds, the conjunction succeeds.

### Step 4: `B` Fails

If `B` fails, execution returns to the failure continuation saved by `A`.

The system then searches for the next clause or next solution of `A`.

### Step 5: Re-execute `B`

If another solution of `A` is found, `B` is executed again using the new variable bindings.

Thus, success continuations control left-to-right execution of a conjunction, while failure continuations control right-to-left backtracking.

---

## 22. Recursive Frames

SCBM creates a recursion frame for each recursive call.

Each recursion frame must preserve at least the following information:

* Arguments at the time of the call
* Clause number at the time of the call
* Variable-binding stack position
* Work-area position
* Success-continuation stack position
* Jump destination used on failure

When a recursive call succeeds, the success continuation stored in its frame is used.

When it fails, the frame state is restored, and execution moves to its failure continuation.

As a result, Prolog recursion and backtracking can be managed on the SCBM stack without depending on the ordinary C call stack.

---

## 23. Clause Choice and Recursion

The `clause` variable indicates the clause from which execution should begin.

For an initial call, its value is normally:

```c
clause = 0;
```

Before executing a clause, the clause-selection number is advanced.

```c
Jinc_choice(th);
```

During backtracking, the saved clause number is restored.

```c
clause = Jget_choice(th);
```

Execution then jumps to the saved label.

```c
goto *next;
```

This allows each recursive call to preserve the next clause that should be attempted, regardless of recursion depth.

---

## 24. Why Recursive and Nonrecursive Predicates Can Be Unified

A simple predicate such as `color/1` and recursive predicates such as `plus/3` and `times/3` appear to perform very different operations.

However, they require the same fundamental control information.

| Requirement                      | `color/1` | `plus/3`, `times/3` |
| -------------------------------- | --------: | ------------------: |
| Selection of the next clause     |       Yes |                 Yes |
| Restoration of unification state |       Yes |                 Yes |
| Success continuation             |       Yes |                 Yes |
| Failure continuation             |       Yes |                 Yes |
| Argument restoration             |       Yes |                 Yes |
| Nested recursion frames          |        No |                 Yes |

Recursive predicates merely introduce nested frames. Their fundamental success and failure control mechanisms remain the same.

M-Prolog can therefore generate both ordinary nondeterministic predicates and recursive nondeterministic predicates using the unified `nondet` code-generation model.

---

## 25. Overall Control Flow

The overall execution flow of an SCBM-generated `nondet` predicate can be summarized as follows:

```text
predicate entry
      |
      v
select predicate
      |
      v
select arity
      |
      v
select clause
      |
      v
save failure continuation
      |
      v
head unification
      |
      +---------------- failure ----------------+
      |                                         |
      v                                         v
execute body                              next clause
      |
      +---------------- failure ----------------+
      |                                         |
      v                                         v
success continuation                 restore SCBM state
      |                                         |
      v                                         v
next goal                      jump to failure continuation
      |
      v
return solution
      |
      v
forced backtracking
      |
      v
restore saved choice point
      |
      v
search for another solution
```

---

## 26. Summary

Code generation for `nondet` predicates in M-Prolog has the following characteristics:

* User-defined predicates are generated inside one large C function
* Predicates, arities, clauses, and body goals are represented as labels
* GCC computed goto is used for control transfer
* Success continuations are stored in `next_stack`
* Failure continuations are stored in the SCBM stack
* Variables, arguments, clause numbers, and continuation positions are restored during backtracking
* Ordinary failure and forced backtracking are treated as distinct operations
* Following goals in a conjunction are represented as success continuations
* Recursive calls use the same success- and failure-continuation mechanism
* Simple nondeterministic predicates and recursive predicates are handled uniformly as `nondet` predicates

SCBM does not delegate Prolog search control to the implicit C function-call mechanism.

Instead, it explicitly saves the destination to use after success and the destination to use after failure, and transfers control directly to those continuations using `goto`.

This structure expresses Prolog clause selection, conjunction, recursion, failure, backtracking, and next-solution search as relatively straightforward generated C code.

