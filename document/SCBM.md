# SCBM
Sasagawa & Chat backtracking Mecanism

# SCBM API Specification

## 1. Overview

SCBM is a stack mechanism for managing the execution state required for Prolog recursion, conjunctions, clause selection, disjunctions, and backtracking.

Conceptually, the SCBM stack has the following two-dimensional structure:

```text
SCBM[CONJ][RECUR]
```

- `CONJ`
  - Depth of conjunctions or predicate-call frames.
- `RECUR`
  - Depth of recursive calls within the current conjunction frame.
- `th`
  - Execution thread number.

Each SCBM frame stores the following information required for backtracking:

| Field | Description |
|---|---|
| `SP_SCBM` | Position of the variable-binding stack |
| `CHOICE_SCBM` | Current clause-selection number |
| `WP_SCBM` | Work-area pointer |
| `AC_SCBM` | Argument or temporary-area counter |
| `DISJ_SCBM` | Choice number inside a disjunction |
| `CHOICE_BACKUP_SCBM` | Saved clause-selection number from before entering a disjunction |
| `ARGLIST_SCBM` | Argument list at the time of the call |
| `VP_SCBM` | Variable-area pointer |
| `NP_SCBM` | Saved continuation or next execution position |
| `SUCC_SCBM` | Success state of the conjunction frame |

Most state-changing functions return `NIL` on normal completion. Getter functions return the stored value.

---

## 2. Underlying Data

### 2.1 SCBM Stack Position

```c
scp[CONJ][th]
scp[RECUR][th]
```

The current SCBM frame is addressed as follows:

```c
scbmstack[scp[CONJ][th]][scp[RECUR][th]][field][th]
```

### 2.2 Stack Size Limits

```c
CONJSIZE
RECURSIZE
```

- `CONJSIZE`
  - Maximum conjunction-stack depth.
- `RECURSIZE`
  - Maximum recursion-stack depth.

If either limit is exceeded, a `RESOURCE_ERR` exception is raised.

### 2.3 Uninitialized Value

```c
UNBIND
```

`UNBIND` indicates that a field such as `ARGLIST_SCBM` has not yet been assigned a valid value.

---

## 3. Frame Management API

### 3.1 `push_conj`

```c
int push_conj(int th);
```

#### Purpose

Creates a new conjunction frame on the SCBM stack.

#### Parameters

| Parameter | Description |
|---|---|
| `th` | Execution thread number |

#### Behavior

1. Increments the `CONJ` position.
2. Resets the `RECUR` position to zero.
3. Checks the conjunction-stack limit.
4. Saves the current execution state in the new frame.
5. Initializes clause-selection and disjunction-related fields.

#### Initialized Fields

```c
CHOICE_SCBM = 0
DISJ_SCBM = 0
CHOICE_BACKUP_SCBM = 0
ARGLIST_SCBM = UNBIND
```

#### Saved Fields

```c
SP_SCBM = sp[th]
WP_SCBM = wp[th]
AC_SCBM = ac[th]
```

#### Return Value

```c
NIL
```

#### Exceptions

Raises `RESOURCE_ERR` if:

```c
scp[CONJ][th] >= CONJSIZE
```

#### Example

```c
push_conj(th);
```

---

### 3.2 `discard_conj`

```c
int discard_conj(int th);
```

#### Purpose

Discards the current conjunction frame and returns to the enclosing conjunction frame.

#### Parameters

| Parameter | Description |
|---|---|
| `th` | Execution thread number |

#### Behavior

1. Decrements the `CONJ` position.
2. Restores the `RECUR` position from the success state stored in the base frame of the enclosing conjunction.

```c
scp[RECUR][th] =
    scbmstack[scp[CONJ][th]][0][SUCC_SCBM][th];
```

#### Return Value

```c
NIL
```

#### Notes

This function does not check whether the `CONJ` position becomes negative. The caller must ensure that a valid enclosing conjunction frame exists.

---

### 3.3 `push_recur`

```c
int push_recur(int arglist, int vp, int np, int th);
```

#### Purpose

Creates a new recursion frame within the current conjunction frame.

#### Parameters

| Parameter | Description |
|---|---|
| `arglist` | Argument list of the recursive call |
| `vp` | Variable-area pointer to save |
| `np` | Continuation or next execution position to save |
| `th` | Execution thread number |

#### Behavior

1. Checks the recursion-stack limit.
2. Increments the `RECUR` position.
3. Saves the current execution state in the new recursion frame.
4. Initializes clause-selection and disjunction-related fields.

#### Saved Fields

```c
SP_SCBM = sp[th]
WP_SCBM = wp[th]
AC_SCBM = ac[th]
ARGLIST_SCBM = arglist
VP_SCBM = vp
NP_SCBM = np
```

#### Initialized Fields

```c
CHOICE_SCBM = 0
DISJ_SCBM = 0
CHOICE_BACKUP_SCBM = 0
```

#### Return Value

```c
NIL
```

#### Exceptions

Raises `RESOURCE_ERR` if:

```c
scp[RECUR][th] + 1 >= RECURSIZE
```

#### Example

```c
push_recur(arglist, vp, np, th);
```

---

### 3.4 `pop_recur`

```c
int pop_recur(int th);
```

#### Purpose

Discards the current recursion frame and returns to the preceding recursion frame.

#### Parameters

| Parameter | Description |
|---|---|
| `th` | Execution thread number |

#### Behavior

```c
scp[RECUR][th]--;
```

#### Return Value

```c
NIL
```

#### Exceptions

Raises `RESOURCE_ERR` if:

```c
scp[RECUR][th] <= 0
```

#### Notes

Recursion depth zero is treated as the base frame of the conjunction and cannot be removed by `pop_recur`.

---

## 4. Clause-Choice Management API

### 4.1 `inc_choice`

```c
int inc_choice(int th);
```

#### Purpose

Increments the clause-selection number in the current SCBM frame.

#### Parameters

| Parameter | Description |
|---|---|
| `th` | Execution thread number |

#### Behavior

```c
CHOICE_SCBM++;
```

#### Return Value

```c
NIL
```

#### Intended Use

Used to advance to the next clause after the current clause fails.

---

### 4.2 `max_choice`

```c
int max_choice(int th);
```

#### Purpose

Sets the current clause-selection number to a very large value.

#### Behavior

```c
CHOICE_SCBM = 999999999;
```

#### Return Value

```c
NIL
```

#### Intended Use

Used to represent a state in which no further clause choices are available.

#### Notes

The value `999999999` is used directly as a sentinel value. For readability and maintainability, defining it as a named constant would be preferable.

```c
#define MAX_CHOICE 999999999
```

---

### 4.3 `get_choice`

```c
int get_choice(int th);
```

#### Purpose

Returns the clause-selection number stored in the current SCBM frame.

#### Side Effects

```c
proof[th]++;
```

Each call increments the proof-attempt counter.

#### Return Value

The current value of `CHOICE_SCBM`.

#### Example

```c
switch (get_choice(th)) {
case 0:
    /* First clause */
    break;
case 1:
    /* Second clause */
    break;
}
```

#### Notes

This is not a pure getter because it modifies `proof[th]`.

---

## 5. Disjunction Management API

### 5.1 `inc_disj_choice`

```c
int inc_disj_choice(int th);
```

#### Purpose

Increments the current choice number inside a disjunction.

#### Behavior

```c
DISJ_SCBM++;
```

#### Return Value

```c
NIL
```

---

### 5.2 `get_disj_choice`

```c
int get_disj_choice(int th);
```

#### Purpose

Returns the current choice number inside a disjunction.

#### Behavior

The function reads the current value of `DISJ_SCBM`.

If the value is zero, it decrements the normal clause-selection number:

```c
if (choice == 0)
    CHOICE_SCBM--;
```

#### Return Value

The current value of `DISJ_SCBM`.

#### Notes

This function is not a pure getter because it conditionally modifies `CHOICE_SCBM`.

The adjustment appears to prevent the first branch of a disjunction from being counted as an ordinary clause choice.

---

### 5.3 `reset_disj`

```c
int reset_disj(int th);
```

#### Purpose

Resets the execution state of the current disjunction.

#### Behavior

```c
DISJ_SCBM = 0;
CHOICE_SCBM = CHOICE_BACKUP_SCBM;
```

#### Return Value

```c
NIL
```

#### Intended Use

Used when retrying an entire disjunction. It resets the internal disjunction choice and restores the clause-selection number saved before entering the disjunction.

#### Notes

The supplied code does not include a function that stores a value in `CHOICE_BACKUP_SCBM`. Such a value must therefore be written elsewhere.

---

## 6. State Restoration API

### 6.1 `release`

```c
int release(int th);
```

#### Purpose

Rolls variable bindings back to the state recorded when the current SCBM frame was created.

#### Parameters

| Parameter | Description |
|---|---|
| `th` | Execution thread number |

#### Behavior

```c
unbind(SP_SCBM, th);
ac[th] = AC_SCBM;
```

More specifically, it:

1. Removes variable bindings created after the saved `SP_SCBM` position.
2. Restores `ac[th]` from the saved `AC_SCBM` value.

#### Return Value

```c
NIL
```

#### Notes

`WP_SCBM` is saved by both `push_conj` and `push_recur`, but this function does not restore `wp[th]`.

The supplied code alone does not show whether this is intentional or whether `wp[th]` is restored elsewhere.

---

## 7. Argument-List Management API

### 7.1 `get_arg`

```c
int get_arg(int th);
```

#### Purpose

Returns the argument list stored in the current SCBM frame.

#### Return Value

```c
ARGLIST_SCBM
```

If no argument list has been stored, the function returns `UNBIND`.

---

### 7.2 `save_arg`

```c
int save_arg(int x, int th);
```

#### Purpose

Stores an argument list in the current SCBM frame.

#### Parameters

| Parameter | Description |
|---|---|
| `x` | Argument list to store |
| `th` | Execution thread number |

#### Behavior

```c
ARGLIST_SCBM = x;
```

#### Return Value

```c
NIL
```

---

### 7.3 `restore_arg`

```c
int restore_arg(int x, int th);
```

#### Purpose

Returns the argument list stored in the current SCBM frame if one exists. Otherwise, it returns the argument list supplied by the caller.

#### Parameters

| Parameter | Description |
|---|---|
| `x` | Default argument list to use when no saved value exists |
| `th` | Execution thread number |

#### Return Value

If the saved value is not `UNBIND`:

```c
ARGLIST_SCBM
```

If the saved value is `UNBIND`:

```c
x
```

#### Example

```c
arglist = restore_arg(arglist, th);
```

#### Meaning

When execution returns through backtracking, the saved argument list is used. During the initial execution, the current argument list is left unchanged.

---

### 7.4 `arity_count`

```c
int arity_count(int arglist);
```

#### Purpose

Returns the arity of an argument list.

If the arity has not yet been computed, the function calculates the list length and caches the result in the argument-list object.

#### Parameters

| Parameter | Description |
|---|---|
| `arglist` | Argument list whose arity is required |

#### Behavior

If the arity is uninitialized:

```c
n = length(arglist);
SET_ARITY(arglist, n);
return n;
```

If the arity has already been cached:

```c
return GET_ARITY(arglist);
```

#### Return Value

The number of elements in the argument list.

#### Side Effects

If the arity has not yet been computed, the result is stored in `arglist`.

#### Notes

This function does not directly manipulate an SCBM frame, but it is a helper API for argument lists stored in SCBM.

---

## 8. Saved-Pointer Access API

### 8.1 `get_vp`

```c
int get_vp(int th);
```

#### Purpose

Returns the variable-area pointer stored in the current recursion frame.

#### Return Value

```c
VP_SCBM
```

---

### 8.2 `get_np`

```c
int get_np(int th);
```

#### Purpose

Returns the `np` value stored in the current recursion frame.

#### Return Value

```c
NP_SCBM
```

#### Inferred Meaning

`np` may represent a success continuation, the next execution position, or a continuation identifier used by the code generator.

Its exact meaning depends on the calling code.

---

### 8.3 `get_scp`

```c
int get_scp(int x, int th);
```

#### Purpose

Returns the requested SCBM stack position.

#### Parameters

| Parameter | Description |
|---|---|
| `x` | Stack-position type, such as `CONJ` or `RECUR` |
| `th` | Execution thread number |

#### Return Value

```c
scp[x][th]
```

#### Example

```c
int conj_depth = get_scp(CONJ, th);
int recur_depth = get_scp(RECUR, th);
```

---

## 9. Success-State Management API

### 9.1 `success`

```c
int success(int arglist, int th);
```

#### Purpose

Records the current conjunction frame as successful.

#### Parameters

| Parameter | Description |
|---|---|
| `arglist` | Argument list at the time of success |
| `th` | Execution thread number |

#### Behavior

The following values are stored in the recursion-depth-zero base frame:

```c
SUCC_SCBM = 1;
ARGLIST_SCBM = arglist;
```

#### Return Value

```c
NIL
```

#### Notes

The success state is stored at recursion depth zero rather than at the current `RECUR` position:

```c
scbmstack[scp[CONJ][th]][0]
```

Therefore, success is managed per conjunction frame rather than per recursion frame.

---

### 9.2 `get_succ`

```c
int get_succ(int th);
```

#### Purpose

Returns the success state of the current conjunction frame.

#### Return Value

```c
scbmstack[scp[CONJ][th]][0][SUCC_SCBM][th]
```

#### Notes

Like `success`, this function accesses the recursion-depth-zero base frame.


# Code Generation for `nondet` Predicates

## 1. Prolog Source Code

The following Prolog predicate is used to explain code generation for the `nondet` predicate type.

```prolog
color(red).
color(green).
color(blue).
```

The predicate `color/1` consists of three clauses.

```prolog
color(red).
color(green).
color(blue).
```

When called with a variable, it returns three solutions in sequence.

```prolog
?- color(X).
X = red ;
X = green ;
X = blue ;
no
```

A predicate that can return multiple solutions from multiple clauses is compiled as a `nondet` predicate.

---

## 2. Relationship Between `nondet` and the Large Function

A `nondet` predicate is generated as an independent C function for each predicate.

For `color/1`, the following function is generated:

```c
static int c_color(int arglist, int rest, int th);
```

All processing for `color/1` is generated inside this `c_color` function.

In contrast, the following function appearing later in the generated code is the large function used to execute `recur` predicates:

```c
static int recur_scbm(
    int pred,
    int arity,
    int clause,
    int arglist,
    int rest,
    int th);
```

`recur_scbm` is used only for predicates classified as `recur`, that is, predicates involving recursive control handled by SCBM.

Because `color/1` is a `nondet` predicate, it is not incorporated into `recur_scbm`, and `recur_scbm` is not used when `color/1` is executed.

Therefore, the relevant part for explaining `nondet` code generation is only:

```c
static int c_color(int arglist, int rest, int th)
```

---

## 3. Generated Function

The following C function is generated from `color/1`.

```c
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
        return(NO);
    }

    Jerrorcomp(
        Jmakeint(ARITY_ERR),
        Jmakecomp("color"),
        arglist
    );

    return(NO);
}
```

This function returns one solution per invocation.

When another solution is requested, the function uses the saved `choice` value and resumes execution from the next clause.

---

## 4. Function Arguments

The function declaration is:

```c
static int c_color(int arglist, int rest, int th);
```

The arguments have the following roles.

| Argument | Meaning |
|---|---|
| `arglist` | The argument list passed to the Prolog predicate |
| `rest` | The remaining goals |
| `th` | The execution thread number |

Because `color/1` consists only of simple facts, the function mainly uses `arglist` and `th`.

---

## 5. Arity Check

The function first obtains the number of arguments.

```c
n = Jarity_count(arglist);
```

Because `color/1` has arity 1, the predicate body is executed only when the number of arguments is one.

```c
if(n == 1){
```

If the number of arguments is not one, an arity error is raised at the end of the function.

```c
Jerrorcomp(
    Jmakeint(ARITY_ERR),
    Jmakecomp("color"),
    arglist
);
```

---

## 6. Retrieving the First Argument

When the arity is correct, the first argument is retrieved.

```c
arg1 = Jcar(arglist);
```

For example, in the following query:

```prolog
color(X).
```

`arg1` contains the Prolog variable `X`.

In the following query:

```prolog
color(green).
```

`arg1` contains the atom `green`.

---

## 7. Retrieving the Choice Value

The current clause selection value is then obtained.

```c
clause = Jget_choice(th);
```

The `choice` value indicates the clause from which execution should begin.

On the first invocation, `choice` is normally 0.

When the same predicate is invoked again to request another solution, `choice` contains the number of the next clause to be tried.

---

## 8. Selecting the Starting Clause

The function jumps to the appropriate clause label according to the value of `choice`.

```c
switch(clause){
case 0: goto clause_1_0;
case 1: goto clause_1_1;
case 2: goto clause_1_2;
default: goto allfail;
}
```

This `switch` is not used to select a predicate in the large SCBM function.

It is only a local dispatch inside `c_color`, used to determine the clause from which execution resumes.

The mapping is:

| `choice` | Destination | Corresponding Prolog Clause |
|---:|---|---|
| 0 | `clause_1_0` | `color(red).` |
| 1 | `clause_1_1` | `color(green).` |
| 2 | `clause_1_2` | `color(blue).` |
| 3 or greater | `allfail` | No remaining clause |

---

## 9. Code for the First Clause

The first Prolog clause is:

```prolog
color(red).
```

The corresponding C code is:

```c
clause_1_0:
Jinc_choice(th);

if(Junify_atom(
       arg1,
       Jmakeconst("red"),
       th) == YES)
    return(YES);
```

### 9.1 Advancing the Choice Value

```c
Jinc_choice(th);
```

Before trying the first clause, the `choice` value is incremented.

On the first invocation, `choice` is 0, so it becomes 1.

This allows execution to resume from the second clause when another solution is requested after the first clause succeeds.

### 9.2 Unification with `red`

```c
Junify_atom(
    arg1,
    Jmakeconst("red"),
    th)
```

`Jmakeconst("red")` creates the Prolog atom `red`.

`Junify_atom` unifies the first argument with `red`.

For the query:

```prolog
color(X).
```

the variable `X` is bound to `red`.

```prolog
X = red
```

If unification succeeds, the function immediately returns `YES`.

```c
return(YES);
```

---

## 10. Failure of the First Clause

If the first argument cannot be unified with `red`, the `return` statement is not executed.

Control then falls through to the next label.

```c
clause_1_1:
```

Thus, when a clause fails, the next clause is tried within the same invocation of the C function.

For example, with:

```prolog
color(green).
```

the first attempted unification is:

```text
green = red
```

This fails, so execution continues with the second clause.

---

## 11. Code for the Second Clause

The second clause is:

```prolog
color(green).
```

The corresponding code is:

```c
clause_1_1:
Jrelease(th);
Jinc_choice(th);

if(Junify_atom(
       arg1,
       Jmakeconst("green"),
       th) == YES)
    return(YES);
```

### 11.1 Releasing Bindings from the Previous Clause

```c
Jrelease(th);
```

Bindings created while trying the previous clause are undone.

In Prolog, when one clause fails and the next clause is tried, the effects of unification performed by the failed clause must be rolled back.

For that reason, `Jrelease` is called at the beginning of the second and subsequent clauses.

### 11.2 Advancing the Choice Value

```c
Jinc_choice(th);
```

When the second clause is entered, `choice` is 1.

It is incremented to 2, so that execution can resume from the third clause if another solution is requested after the second clause succeeds.

### 11.3 Unification with `green`

```c
Junify_atom(
    arg1,
    Jmakeconst("green"),
    th)
```

The first argument is unified with `green`.

If the unification succeeds, the function returns `YES`.

---

## 12. Code for the Third Clause

The third clause is:

```prolog
color(blue).
```

The corresponding code is:

```c
clause_1_2:
Jrelease(th);
Jinc_choice(th);

if(Junify_atom(
       arg1,
       Jmakeconst("blue"),
       th) == YES)
    return(YES);
```

The processing is the same as for the second clause.

1. `Jrelease` removes the bindings created by the previous clause.
2. `Jinc_choice` advances the clause number for the next invocation.
3. The first argument is unified with `blue`.
4. If unification succeeds, the function returns `YES`.

Before the third clause is tried, `choice` is 2.

After `Jinc_choice`, it becomes 3.

Therefore, if another solution is requested after the third clause succeeds, no corresponding clause remains.

---

## 13. Failure of All Clauses

If unification also fails in the third clause, control continues to:

```c
clause_1_3:
Jrelease(th);
```

The bindings created while trying the final clause are released, after which execution continues to `allfail`.

```c
allfail:
Jdiscard_conj(th);
return(NO);
```

### 13.1 Discarding the Nondeterministic State

```c
Jdiscard_conj(th);
```

The conjunction or nondeterministic state associated with the current predicate call is discarded.

At this point, no clause of `color/1` remains to be tried.

### 13.2 Returning `NO`

```c
return(NO);
```

The function informs the caller that no further solution exists.

---

## 14. Execution of `color(X)`

Consider the query:

```prolog
?- color(X).
```

### 14.1 First Invocation

Execution begins with:

```text
choice = 0
```

The local `switch` transfers control to the first clause.

```c
goto clause_1_0;
```

`Jinc_choice` changes the value to:

```text
choice = 1
```

The variable `X` is then unified with `red`.

```text
X = red
```

The function returns `YES`.

```prolog
X = red
```

### 14.2 Second Solution

When the user requests another solution, `c_color` is invoked again.

The saved value is now:

```text
choice = 1
```

Execution therefore resumes from the second clause.

```c
goto clause_1_1;
```

`Jrelease` removes the previous binding:

```text
X = red
```

The choice value is incremented to 2, and `X` is unified with `green`.

```text
X = green
```

The function returns `YES`.

```prolog
X = green
```

### 14.3 Third Solution

When another solution is requested, the saved value is:

```text
choice = 2
```

Execution resumes from the third clause.

```c
goto clause_1_2;
```

The previous binding is released, and `X` is unified with `blue`.

```text
X = blue
```

The function returns `YES`.

```prolog
X = blue
```

### 14.4 No More Solutions

When another solution is requested, the saved value is:

```text
choice = 3
```

No corresponding clause exists, so the `default` branch transfers control to `allfail`.

```c
default: goto allfail;
```

The nondeterministic state is discarded, and the function returns `NO`.

```prolog
no
```

---

## 15. Execution of `color(green)`

Consider:

```prolog
?- color(green).
```

The first clause attempts:

```text
green = red
```

This fails.

Execution continues to the second clause, where `Jrelease` rolls back the first unification attempt.

The next unification is:

```text
green = green
```

This succeeds, so the function returns `YES`.

```prolog
yes
```

If another solution is requested, the third clause attempts:

```text
green = blue
```

This fails, and the predicate eventually returns `NO`.

---

## 16. Execution of `color(yellow)`

In the following query, none of the clauses match:

```prolog
?- color(yellow).
```

The clauses are tried in sequence.

```text
yellow = red
yellow = green
yellow = blue
```

All unifications fail.

The function then calls `Jdiscard_conj` and returns `NO`.

```prolog
no
```

---

## 17. Predicate Registration

The generated `c_color` function is registered with the Prolog system by the initialization function.

```c
void init_tpredicate(void){
    (deftpred)("color",c_color,1,1);
}
```

This registration causes the C function `c_color` to be called when Prolog invokes `color/1`.

The main registration arguments are:

| Argument | Meaning |
|---|---|
| `"color"` | The Prolog predicate name |
| `c_color` | The generated C function |
| `1` | The arity |
| `1` | A predicate registration attribute |

---

## 18. General Form of `nondet` Code

A `nondet` predicate consisting of multiple facts is generally generated in the following form.

```c
static int c_predicate(int arglist, int rest, int th)
{
    int arg1;
    int clause;

    arg1 = Jcar(arglist);
    clause = Jget_choice(th);

    switch(clause){
    case 0: goto clause_0;
    case 1: goto clause_1;
    default: goto allfail;
    }

clause_0:
    Jinc_choice(th);

    if(/* unification for the first clause */)
        return(YES);

clause_1:
    Jrelease(th);
    Jinc_choice(th);

    if(/* unification for the second clause */)
        return(YES);

    Jrelease(th);

allfail:
    Jdiscard_conj(th);
    return(NO);
}
```

This structure implements the following behavior:

- The first invocation starts from the first clause.
- If a clause fails, execution continues to the next clause inside the same C function.
- If a clause succeeds, the next clause number is saved and the function returns `YES`.
- When another solution is requested, execution resumes from the saved clause number.
- Bindings created by the previous clause are removed by `Jrelease`.
- When all clauses have been exhausted, the function returns `NO`.

---

## 19. Summary

Because `color/1` contains multiple non-recursive clauses, it is compiled as a `nondet` predicate.

A `nondet` predicate is generated as an independent C function for each predicate.

For this example, the generated function is:

```c
static int c_color(int arglist, int rest, int th)
```

The function uses the `choice` value to manage the next clause to be tried.

The main APIs are:

| API | Role |
|---|---|
| `Jarity_count` | Obtains the number of arguments |
| `Jcar` | Retrieves the first argument |
| `Jget_choice` | Obtains the number of the next clause to try |
| `Jinc_choice` | Advances the saved clause number |
| `Junify_atom` | Unifies an argument with an atom |
| `Jrelease` | Removes bindings created by the previous clause |
| `Jdiscard_conj` | Discards the nondeterministic state |

When one clause succeeds, the function returns `YES`.

When another solution is requested, the same C function is invoked again and resumes from the clause indicated by the saved `choice` value.

This mechanism is independent of the large `recur_scbm` function.

`recur_scbm` is used only for `recur` predicates and is not involved in the execution of the `nondet` predicate `color/1`.


# Code Generation for `recur` Predicates

## 1. Prolog Source Code

The following two predicates are used to explain code generation for the `recur` predicate type.

```prolog
plus(0, Y, Y).
plus(s(X), Y, s(Z)) :-
    plus(X, Y, Z).


times(0, _, 0).
times(s(X), Y, Z) :-
    times(X, Y, Z1),
    plus(Z1, Y, Z).
```

`plus/3` defines addition using Peano numbers.

```prolog
plus(0, Y, Y).
plus(s(X), Y, s(Z)) :-
    plus(X, Y, Z).
```

`times/3` defines multiplication of Peano numbers using `plus/3`.

```prolog
times(0, _, 0).
times(s(X), Y, Z) :-
    times(X, Y, Z1),
    plus(Z1, Y, Z).
```

Because both predicates contain recursive calls, they are compiled as `recur` predicates.

---

## 2. The `recur` Type and the Large Function

For `recur` predicates, the compiler does not generate a separate large recursive C function for each predicate.

Instead, multiple `recur` predicates are combined into a single large function.

```c
static int recur_scbm(
    int pred,
    int arity,
    int clause,
    int arglist,
    int rest,
    int th);
```

In this example, the following two predicates are incorporated into `recur_scbm`.

```text
pred = 0    plus/3
pred = 1    times/3
```

Inside `recur_scbm`, C labels are generated for predicates, arities, clauses, and positions within clause bodies.

```text
plus
plus_3
plus_3_0
plus_3_1
plus_3_1_0
plus_3_1_1

times
times_3
times_3_0
times_3_1
times_3_1_0
times_3_1_1
times_3_1_2
```

Recursive calls and backtracking are performed by `goto` statements to these labels, rather than by recursive C function calls.

---

## 3. Entry Functions

When Prolog calls `plus/3` or `times/3`, a small entry function is executed first.

```c
static int c_plus(int arglist, int rest, int th){
    int n;

    n = Jlength(arglist);
    Jsave_arg(arglist,th);

    return(recur_scbm(
        0,
        n,
        0,
        arglist,
        rest,
        th));
}
```

```c
static int c_times(int arglist, int rest, int th){
    int n;

    n = Jlength(arglist);
    Jsave_arg(arglist,th);

    return(recur_scbm(
        1,
        n,
        0,
        arglist,
        rest,
        th));
}
```

The role of each entry function is limited to the following operations:

1. Obtain the number of arguments.
2. Save the initial argument list.
3. Call `recur_scbm` with the appropriate predicate number.

Clause selection, unification, recursive calls, success continuations, and failure continuations are all handled inside `recur_scbm`.

---

## 4. Entry Function Arguments

An entry function has the following form:

```c
static int c_plus(int arglist, int rest, int th);
```

| Argument  | Meaning                                                 |
| --------- | ------------------------------------------------------- |
| `arglist` | The argument list passed to the Prolog predicate        |
| `rest`    | The remaining goals to execute after the predicate call |
| `th`      | The execution thread number                             |

`Jlength` obtains the length of the argument list.

```c
n = Jlength(arglist);
```

For `plus/3` and `times/3`, the value is normally:

```text
n = 3
```

---

## 5. Saving the Initial Argument List

Before calling `recur_scbm`, the entry function saves the argument list.

```c
Jsave_arg(arglist,th);
```

During recursive execution, `arglist` is repeatedly replaced with the arguments of the predicate currently being called.

For example, in the following call:

```prolog
plus(s(s(0)), Y, Z).
```

`arglist` changes conceptually as follows:

```text
plus(s(s(0)), Y, Z)
plus(s(0),    Y, Z1)
plus(0,       Y, Z2)
```

After the top-level call succeeds, the original argument information may be required to execute the remaining goals or to resume backtracking.

For that reason, the initial `arglist` is saved at the entry point.

---

## 6. Predicate Registration

The generated entry functions are registered with the Prolog system by an initialization function.

```c
void init_tpredicate(void){
    (deftpred)("plus",c_plus,3,6);
    (deftpred)("times",c_times,3,6);
}
```

The main registration information is as follows:

| Registration item        | `plus/3` | `times/3` |
| ------------------------ | -------- | --------- |
| Prolog predicate name    | `"plus"` | `"times"` |
| Entry C function         | `c_plus` | `c_times` |
| Arity                    | `3`      | `3`       |
| Predicate type attribute | `6`      | `6`       |

The final value, `6`, is the registration attribute used for the `recur` predicate type in this implementation.

---

## 7. Arguments of `recur_scbm`

The large function has the following form:

```c
static int recur_scbm(
    int pred,
    int arity,
    int clause,
    int arglist,
    int rest,
    int th)
```

The arguments have the following meanings:

| Argument  | Meaning                                                     |
| --------- | ----------------------------------------------------------- |
| `pred`    | The predicate number to execute                             |
| `arity`   | The predicate arity                                         |
| `clause`  | The clause number from which execution begins               |
| `arglist` | The argument list of the predicate currently being executed |
| `rest`    | The remaining goals following the top-level call            |
| `th`      | The execution thread number                                 |

In this example, predicate numbers are assigned as follows:

| `pred` | Predicate |
| -----: | --------- |
|      0 | `plus/3`  |
|      1 | `times/3` |

---

## 8. Initializing the Execution State

At the beginning of `recur_scbm`, the success-continuation stack position and variable-stack position are initialized.

```c
np[Jget_scp(CONJ,th)][th] = 0;
vp[th] = 0;
```

`np` indicates the current position in the success-continuation stack.

```text
np = next pointer
```

`vp` indicates the position used to save logical variables that must survive across predicate calls.

```text
vp = variable pointer
```

The top-level `success` label is then registered as the initial success continuation.

```c
Jpush_next(&&success,th);
```

This causes control to move to the common `success` processing when the top-level predicate succeeds.

---

## 9. Predicate Selection

The first `switch` in the large function selects the predicate to execute.

```c
switch(pred){
case 0: goto plus;
case 1: goto times;
}
```

This `switch` does not select a clause.

It selects one of the `recur` predicates incorporated into the large function.

```text
pred = 0 → plus
pred = 1 → times
```

The entry function `c_plus` passes `pred = 0`.

```c
return(recur_scbm(0,n,0,arglist,rest,th));
```

The entry function `c_times` passes `pred = 1`.

```c
return(recur_scbm(1,n,0,arglist,rest,th));
```

---

## 10. Arity Selection

After control reaches a predicate label, the appropriate arity label is selected.

```c
plus:
switch(arity){
case 3: goto plus_3;
default: goto allfail;
}
```

```c
times:
switch(arity){
case 3: goto times_3;
default: goto allfail;
}
```

Because both predicates have arity 3, execution moves to:

```text
plus_3
times_3
```

If the arity does not match, control moves to the common failure handler, `allfail`.

---

## 11. Clause Selection

At each arity-specific label, the value of `clause` determines the clause from which execution begins.

```c
plus_3:
switch(clause){
case 0: goto plus_3_0;
case 1: goto plus_3_1;
default: goto allfail;
}
```

```c
times_3:
switch(clause){
case 0: goto times_3_0;
case 1: goto times_3_1;
default: goto allfail;
}
```

The mappings are as follows.

### `plus/3`

| `clause` | Label      | Prolog clause                       |
| -------: | ---------- | ----------------------------------- |
|        0 | `plus_3_0` | `plus(0,Y,Y).`                      |
|        1 | `plus_3_1` | `plus(s(X),Y,s(Z)) :- plus(X,Y,Z).` |

### `times/3`

| `clause` | Label       | Prolog clause                                     |
| -------: | ----------- | ------------------------------------------------- |
|        0 | `times_3_0` | `times(0,_,0).`                                   |
|        1 | `times_3_1` | `times(s(X),Y,Z) :- times(X,Y,Z1), plus(Z1,Y,Z).` |

---

# Code Generation for `plus/3`

## 12. The First Clause of `plus/3`

The first Prolog clause is:

```prolog
plus(0, Y, Y).
```

The generated code is:

```c
plus_3_0:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);

Jrelease(th);

varY = Jmakevariant(th);

Jinc_choice(th);
Jset_back(&&plus_3_1,th);

if(Junify_int(arg1,Jmakeint(0),th) == YES &&
   Junify_var(arg2,varY,th) == YES &&
   Junify_var(arg3,varY,th) == YES)
{
    goto success;
}
```

---

## 13. Retrieving the Arguments

The three arguments are retrieved from `arglist`.

```c
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
```

For example, in the following call:

```prolog
plus(0, s(0), Z).
```

the variables conceptually contain:

```text
arg1 = 0
arg2 = s(0)
arg3 = Z
```

---

## 14. Releasing the Working State

Before beginning unification for a clause, the temporary state created by the previous clause attempt is released.

```c
Jrelease(th);
```

When backtracking causes another clause of the same predicate to be tried, bindings and working data created by the previous clause cannot remain active.

`Jrelease` restores the state required to begin trying the current clause.

---

## 15. Creating Clause Variables

An internal variable corresponding to the clause variable `Y` is created.

```c
varY = Jmakevariant(th);
```

In the Prolog clause, the same `Y` occurs in two positions.

```prolog
plus(0, Y, Y).
        ^  ^
```

Therefore, the second and third arguments are unified with the same internal variable, `varY`.

```c
Junify_var(arg2,varY,th)
Junify_var(arg3,varY,th)
```

This implements the condition that the second and third arguments must be equal.

---

## 16. Failure Continuation to the Next Clause

Before attempting the first clause, the next clause is registered as the failure continuation.

```c
Jinc_choice(th);
Jset_back(&&plus_3_1,th);
```

`Jinc_choice` advances the current clause number.

```text
0 → 1
```

`Jset_back` sets the second clause label as the destination to use if the first clause fails.

```text
failure continuation = plus_3_1
```

This failure continuation is used not only when the clause head immediately fails, but also when execution later backtracks into this predicate.

---

## 17. Unification for the First Clause

The head of the first clause is generated as three unification operations.

```c
Junify_int(arg1,Jmakeint(0),th)
```

This unifies the first argument with `0`.

```c
Junify_var(arg2,varY,th)
```

This unifies the second argument with the clause variable `Y`.

```c
Junify_var(arg3,varY,th)
```

This also unifies the third argument with the same `Y`.

If all three unifications succeed, the clause succeeds.

```c
goto success;
```

Because the first clause has no body, execution moves directly to the common success handler after successful head unification.

---

## 18. The Second Clause of `plus/3`

The second Prolog clause is:

```prolog
plus(s(X), Y, s(Z)) :-
    plus(X, Y, Z).
```

The generated code begins as follows:

```c
plus_3_1:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);

Jrelease(th);

varX = Jmakevariant(th);
varY = Jmakevariant(th);
varZ = Jmakevariant(th);

Jinc_choice(th);
Jset_back(&&plus_3_2,th);

if(Junify(
       arg1,
       Jwcons(
           Jmakepred("s"),
           Jwcons(varX,NIL,th),
           th),
       th) == YES &&
   Junify_var(arg2,varY,th) == YES &&
   Junify(
       arg3,
       Jwcons(
           Jmakepred("s"),
           Jwcons(varZ,NIL,th),
           th),
       th) == YES)
{
    ...
}
```

---

## 19. Constructing the Structure `s(X)`

The Prolog term

```prolog
s(X)
```

is constructed by the following code:

```c
Jwcons(
    Jmakepred("s"),
    Jwcons(varX,NIL,th),
    th)
```

Conceptually, this creates the following structure:

```text
functor = s
arguments = [varX]
```

The first argument is unified with this structure.

```c
Junify(arg1, s(varX), th)
```

Similarly, the third argument is unified with `s(varZ)`.

```c
Junify(arg3, s(varZ), th)
```

---

## 20. Final Failure Continuation of the Second Clause

Before attempting the second clause, the next failure continuation is set.

```c
Jinc_choice(th);
Jset_back(&&plus_3_2,th);
```

There is no clause after the second clause of `plus/3`.

Therefore, `plus_3_2` represents complete failure of `plus/3`.

```c
plus_3_2:
Jpop_back(th);
goto allfail;
```

---

## 21. Constructing Arguments for the Recursive Call

The body of the second clause is:

```prolog
plus(X, Y, Z).
```

A new argument list is constructed for this call.

```c
arglist =
    Jwlistcons(
        varX,
        Jwlistcons(
            varY,
            Jwlistcons(
                varZ,
                NIL,
                th),
            th),
        th);
```

The resulting argument list is:

```text
[varX, varY, varZ]
```

At this point, `arglist` no longer represents the arguments of the outer `plus/3` call. It represents the arguments of the recursive inner call.

---

## 22. Saving the Failure State for the Recursive Call

Before the recursive call, the state required for backtracking is saved in SCBM.

```c
Jpush_back(
    &&plus_3_2,
    arglist,
    vp[th],
    np[Jget_scp(CONJ,th)][th],
    th);
```

The main saved values are:

| Saved value  | Meaning                                        |
| ------------ | ---------------------------------------------- |
| `&&plus_3_2` | Continuation if the entire clause fails        |
| `arglist`    | Argument list required when resuming execution |
| `vp[th]`     | Variable-stack position                        |
| `np[...]`    | Success-continuation-stack position            |

In the second clause of `plus/3`, no `Jpush_var` operation is required.

After the recursive call succeeds, no clause variable is needed by another body goal. The success of the recursive call immediately makes the entire clause succeed.

---

## 23. Registering the Success Continuation

The position to execute after the recursive call succeeds is registered on the success-continuation stack.

```c
Jpush_next(&&plus_3_1_1,th);
```

The registered label is:

```text
plus_3_1_1
```

This is the position executed after the recursive call

```prolog
plus(X, Y, Z)
```

succeeds.

Because there is no later goal in the second clause, `plus_3_1_1` simply succeeds.

```c
plus_3_1_1:
goto success;
```

---

## 24. No Recursive C Function Call

The recursive call to `plus/3` is performed as follows:

```c
clause = Jget_choice(th);
goto plus_3;
```

With ordinary C recursion, the compiler might generate a function call such as:

```c
c_plus(new_arglist, rest, th);
```

However, the generated code does not recursively call a C function.

Instead, it jumps directly to the arity-specific label inside the same large function.

```text
goto plus_3
```

This is the central feature of `recur` code generation.

Recursion is managed using SCBM and labeled `goto` statements rather than the C call stack.

---

## 25. The `plus_3_1_0back` Label

Immediately before the recursive call, the following label is generated:

```c
plus_3_1_0back:
Jpush_next(&&plus_3_1_1,th);
clause = Jget_choice(th);
goto plus_3;
```

This label is used as a restart point when backtracking into the inner recursive call.

During the first execution, control reaches `plus_3_1_0back` by falling through from the preceding code.

During backtracking, a stored failure continuation can return control to this area so that the next clause or next solution of the inner `plus/3` call can be tried.

---

# Code Generation for `times/3`

## 26. The First Clause of `times/3`

The first Prolog clause is:

```prolog
times(0, _, 0).
```

The generated code is:

```c
times_3_0:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);

Jrelease(th);

ano_1 = Jmakevariant(th);

Jinc_choice(th);
Jset_back(&&times_3_1,th);

if(Junify_int(arg1,Jmakeint(0),th) == YES &&
   Junify_var(arg2,ano_1,th) == YES &&
   Junify_int(arg3,Jmakeint(0),th) == YES)
{
    goto success;
}
```

---

## 27. Creating an Anonymous Variable

The second argument of the first clause is an anonymous variable.

```prolog
times(0, _, 0).
         ^
```

The generated code still creates an internal variable for it.

```c
ano_1 = Jmakevariant(th);
```

The second argument is unified with this internal variable.

```c
Junify_var(arg2,ano_1,th)
```

However, the anonymous variable is not referenced from any other position in the clause.

Therefore, it may match any value.

---

## 28. The Second Clause of `times/3`

The second Prolog clause is:

```prolog
times(s(X), Y, Z) :-
    times(X, Y, Z1),
    plus(Z1, Y, Z).
```

This clause contains two body goals.

```text
First goal:  times(X, Y, Z1)
Second goal: plus(Z1, Y, Z)
```

The generated code contains labels and success continuations corresponding to each body goal.

```text
times_3_1_0    Preparation for the first goal
times_3_1_1    After the first goal succeeds
times_3_1_2    After the second goal succeeds
```

---

## 29. Head Unification for the Second Clause

The head processing for the second clause begins as follows:

```c
times_3_1:
arg1 = Jcar(arglist);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);

Jrelease(th);

varZ1 = Jmakevariant(th);
varX  = Jmakevariant(th);
varY  = Jmakevariant(th);
varZ  = Jmakevariant(th);

Jinc_choice(th);
Jset_back(&&times_3_2,th);
```

The clause uses four variables:

```prolog
X
Y
Z
Z1
```

An internal variable is allocated for each one.

```c
varZ1 = Jmakevariant(th);
varX  = Jmakevariant(th);
varY  = Jmakevariant(th);
varZ  = Jmakevariant(th);
```

The head is unified as follows:

```c
if(Junify(
       arg1,
       Jwcons(
           Jmakepred("s"),
           Jwcons(varX,NIL,th),
           th),
       th) == YES &&
   Junify_var(arg2,varY,th) == YES &&
   Junify_var(arg3,varZ,th) == YES)
{
    ...
}
```

This corresponds to the following Prolog head:

```prolog
times(s(X), Y, Z)
```

---

## 30. The First Body Goal

The first body goal is:

```prolog
times(X, Y, Z1)
```

The corresponding argument list is constructed.

```c
times_3_1_0:
arglist =
    Jwlistcons(
        varX,
        Jwlistcons(
            varY,
            Jwlistcons(
                varZ1,
                NIL,
                th),
            th),
        th);
```

The new `arglist` contains:

```text
[varX, varY, varZ1]
```

---

## 31. Saving Clause Variables

In the second clause of `times/3`, clause variables are still required after the first recursive call succeeds.

The following goal must be executed afterward:

```prolog
plus(Z1, Y, Z)
```

Therefore, the variables are saved before entering the recursive call.

```c
Jpush_var(varZ1,th);
Jpush_var(varX,th);
Jpush_var(varY,th);
Jpush_var(varZ,th);
```

This is necessary because the same C local variable names are reused inside recursive calls.

When control enters an inner `times/3` call, the following code is executed again:

```c
varZ1 = Jmakevariant(th);
varX  = Jmakevariant(th);
varY  = Jmakevariant(th);
varZ  = Jmakevariant(th);
```

Without saving the outer variables, the values required by the outer clause would be overwritten.

The outer clause variables are therefore stored on a dedicated variable stack.

---

## 32. Variable Save and Restore Order

The variables are saved in the following order:

```c
Jpush_var(varZ1,th);
Jpush_var(varX,th);
Jpush_var(varY,th);
Jpush_var(varZ,th);
```

Because the stack is LIFO, they are restored in reverse order.

```c
varZ  = Jpop_var(th);
varY  = Jpop_var(th);
varX  = Jpop_var(th);
varZ1 = Jpop_var(th);
```

The correspondence is:

| Save order | Saved variable | Restore order |
| ---------: | -------------- | ------------: |
|          1 | `varZ1`        |             4 |
|          2 | `varX`         |             3 |
|          3 | `varY`         |             2 |
|          4 | `varZ`         |             1 |

---

## 33. Saving the Failure Continuation for the First Goal

Before entering the recursive call, the failure state is saved.

```c
Jpush_back(
    &&times_3_2,
    arglist,
    vp[th],
    np[Jget_scp(CONJ,th)][th],
    th);
```

The final failure destination is:

```text
times_3_2
```

This label handles failure of the entire second clause of `times/3`.

```c
times_3_2:
Jpop_back(th);
goto allfail;
```

The following state is also saved:

```text
The argument list for the first goal
The variable-stack position, vp
The success-continuation-stack position, np
```

---

## 34. Success Continuation for the First Goal

The position to execute after the first goal succeeds is registered.

```c
Jpush_next(&&times_3_1_1,th);
```

The current clause number is then obtained, and control jumps to the same `times/3` predicate entry.

```c
clause = Jget_choice(th);
goto times_3;
```

This executes the following Prolog call:

```prolog
times(X, Y, Z1)
```

---

## 35. After the First Goal Succeeds

When the recursive call `times(X,Y,Z1)` succeeds, the success continuation returns control to:

```c
times_3_1_1:
```

The saved clause variables are first restored.

```c
varZ  = Jpop_var(th);
varY  = Jpop_var(th);
varX  = Jpop_var(th);
varZ1 = Jpop_var(th);
```

This restores the C local variables that belonged to the outer clause and were overwritten by the recursive call.

An important point is that the logical variable referenced by `varZ1` contains the binding produced by the recursive call.

What is restored is the value that identifies the logical variable.

The binding made to that logical variable remains intact.

---

## 36. The Second Body Goal

The next goal is:

```prolog
plus(Z1, Y, Z)
```

A new argument list is constructed using the restored variables.

```c
arglist =
    Jwlistcons(
        varZ1,
        Jwlistcons(
            varY,
            Jwlistcons(
                varZ,
                NIL,
                th),
            th),
        th);
```

The resulting argument list is:

```text
[varZ1, varY, varZ]
```

---

## 37. Backtracking from the Second Goal to the First Goal

Before calling the second goal, the following failure continuation is saved:

```c
Jpush_back(
    &&times_3_1_0back,
    arglist,
    vp[th],
    np[Jget_scp(CONJ,th)][th],
    th);
```

The failure continuation label is:

```text
times_3_1_0back
```

If the second goal

```prolog
plus(Z1,Y,Z)
```

fails, or if all of its solutions are exhausted, control must return to the first goal

```prolog
times(X,Y,Z1)
```

to request another solution.

For a Prolog conjunction

```prolog
A, B
```

if `B` fails, the system must search for another solution of `A`.

In this clause:

```text
A = times(X,Y,Z1)
B = plus(Z1,Y,Z)
```

Therefore, after failure of `plus/3`, execution must backtrack into the recursive `times/3` call.

The continuation `&&times_3_1_0back` represents this control flow.

---

## 38. Success Continuation for the Second Goal

The position to execute after the second goal succeeds is registered.

```c
Jpush_next(&&times_3_1_2,th);
```

Control then jumps directly to the clause selector for `plus/3`.

```c
clause = Jget_choice(th);
goto plus_3;
```

Again, the C entry function `c_plus` is not called.

Execution jumps directly to the `plus_3` label inside the large function.

```text
goto plus_3
```

Calls between `recur` predicates are therefore also implemented as jumps between labels within the same large function.

---

## 39. After the Second Goal Succeeds

When `plus(Z1,Y,Z)` succeeds, control returns to:

```c
times_3_1_2:
goto success;
```

The second goal is the final goal of the clause.

Therefore, its success means that the entire second clause of `times/3` has succeeded.

Control moves to the common success handler.

---

# Success Processing

## 40. The Common `success` Label

Success of all `recur` predicates is handled by the common `success` label.

```c
success:
if(np[Jget_scp(CONJ,th)][th] == 0){
    if(Jprove_all(
           rest,
           Jget_sp(th),
           th) == YES)
        return(YES);

    next =
        back_stack
        [Jget_scp(RECUR,th)]
        [Jget_scp(CONJ,th)]
        [th];

    clause = Jget_choice(th);
    arglist = Jget_arg(th);

    Jpush_next(&&success,th);
    goto *next;
}else{
    next =
        next_stack
        [np[Jget_scp(CONJ,th)][th]]
        [Jget_scp(CONJ,th)]
        [th];

    Jpop_next(th);
    clause = Jget_choice(th);

    goto *next;
}
```

The processing depends on whether another success continuation remains.

---

## 41. Success of an Internal Goal

If `np` is not zero, another body goal remains to be executed.

```c
}else{
```

The next label is obtained from the success-continuation stack.

```c
next =
    next_stack
    [np[Jget_scp(CONJ,th)][th]]
    [Jget_scp(CONJ,th)]
    [th];
```

The continuation is then removed from the stack.

```c
Jpop_next(th);
```

The clause number is restored, and control jumps to the retrieved label.

```c
clause = Jget_choice(th);
goto *next;
```

For example, in the second clause of `times/3`, control moves as follows:

```text
times(X,Y,Z1) succeeds
    ↓
times_3_1_1

plus(Z1,Y,Z) succeeds
    ↓
times_3_1_2
```

---

## 42. Success of the Top-Level Predicate

If `np` is zero, no success continuation remains inside the large function.

```c
if(np[Jget_scp(CONJ,th)][th] == 0){
```

This means that execution of the top-level predicate body has completed.

The remaining goals are then executed.

```c
if(Jprove_all(
       rest,
       Jget_sp(th),
       th) == YES)
    return(YES);
```

If the remaining goals also succeed, the entire Prolog call succeeds.

```c
return(YES);
```

---

## 43. Failure of the Remaining Goals

Even if the top-level `recur` predicate succeeds, a later goal contained in `rest` may fail.

In that case, execution must return to the `recur` predicate and search for another solution.

The restart position is obtained from the failure-continuation stack.

```c
next =
    back_stack
    [Jget_scp(RECUR,th)]
    [Jget_scp(CONJ,th)]
    [th];
```

The clause number and argument list are restored.

```c
clause = Jget_choice(th);
arglist = Jget_arg(th);
```

The common `success` label is registered again so that a later successful alternative can return to top-level success processing.

```c
Jpush_next(&&success,th);
```

Finally, control moves to the saved failure continuation.

```c
goto *next;
```

This connects failure of the remaining goals to backtracking inside the `recur` predicate.

---

# Failure Processing

## 44. The Common `allfail` Label

When all applicable clauses fail, control moves to the common `allfail` label.

```c
allfail:
if(Jget_scp(RECUR,th)==0) {
    Jdiscard_conj(th);
    return(NO);
}

next =
    back_stack
    [Jget_scp(RECUR,th)]
    [Jget_scp(CONJ,th)]
    [th];

Jpop_recur(th);
Jpop_next(th);

clause = Jget_choice(th);
arglist = Jget_arg(th);

vp[th] = Jget_vp(th);
np[Jget_scp(CONJ,th)][th] = Jget_np(th);

goto *next;
```

---

## 45. Complete Failure at the Top Level

If the recursive stack is empty,

```c
Jget_scp(RECUR,th) == 0
```

there is no caller to which execution can return.

```c
Jdiscard_conj(th);
return(NO);
```

The current conjunction state is discarded, and `NO` is returned to indicate complete failure of the Prolog call.

---

## 46. Backtracking to the Caller

If the recursive stack is not empty, execution must return to a caller.

First, the saved failure-continuation label is obtained.

```c
next =
    back_stack
    [Jget_scp(RECUR,th)]
    [Jget_scp(CONJ,th)]
    [th];
```

The current recursive frame and success continuation are then removed.

```c
Jpop_recur(th);
Jpop_next(th);
```

The clause number and argument list required for backtracking are restored.

```c
clause = Jget_choice(th);
arglist = Jget_arg(th);
```

The variable-stack position and success-continuation-stack position are also restored.

```c
vp[th] = Jget_vp(th);
np[Jget_scp(CONJ,th)][th] = Jget_np(th);
```

Finally, execution jumps to the saved failure continuation.

```c
goto *next;
```

This allows execution to resume from the correct position in the calling clause.

---

## 47. `Jpush_next` and `Jpush_back`

In `recur` code, success continuations and failure continuations are managed separately.

### Success Continuations

A success continuation specifies the next goal to execute after the current goal succeeds.

```c
Jpush_next(&&label,th);
```

It is stored in `next_stack`.

For example:

```c
Jpush_next(&&times_3_1_1,th);
```

This means:

```text
When times(X,Y,Z1) succeeds,
continue at times_3_1_1.
```

### Failure Continuations

A failure continuation specifies where execution should return if the current goal fails or if another solution is requested.

```c
Jpush_back(
    &&label,
    arglist,
    vp,
    np,
    th);
```

It is stored in `back_stack` together with the SCBM state.

For example:

```c
Jpush_back(
    &&times_3_1_0back,
    arglist,
    vp[th],
    np[Jget_scp(CONJ,th)][th],
    th);
```

This means:

```text
If plus(Z1,Y,Z) fails,
return to the search for another solution of times(X,Y,Z1).
```

---

## 48. Relationship Between Success and Failure Continuations

Consider the following Prolog clause:

```prolog
times(s(X),Y,Z) :-
    times(X,Y,Z1),
    plus(Z1,Y,Z).
```

The forward execution flow is:

```text
times(X,Y,Z1)
    │
    │ success
    ▼
plus(Z1,Y,Z)
    │
    │ success
    ▼
success of the entire clause
```

Success continuations represent this forward flow.

```text
times → plus → success
```

Failure continuations represent search in the opposite direction.

```text
plus fails
    ↓
try another solution of times

all solutions of times fail
    ↓
return to another clause or to the caller
```

SCBM manages these two directions of control using separate stacks.

---

## 49. Difference Between `plus/3` and `times/3`

Both predicates are classified as `recur`, but their generated code has different levels of complexity.

### `plus/3`

```prolog
plus(s(X),Y,s(Z)) :-
    plus(X,Y,Z).
```

The body contains only one goal.

There is no later goal requiring clause variables after the recursive call succeeds.

Therefore, clause variables do not need to be saved.

```text
recursive call
    ↓
immediate success of the clause
```

### `times/3`

```prolog
times(s(X),Y,Z) :-
    times(X,Y,Z1),
    plus(Z1,Y,Z).
```

The body contains two goals.

After the first recursive call succeeds, the outer clause variables are required to execute `plus/3`.

The following additional processing is therefore necessary:

```text
save clause variables
perform recursive call
restore clause variables
execute the next goal
```

This is implemented using `Jpush_var` and `Jpop_var`.

---

## 50. Execution Example: `plus(s(s(0)),Y,Z)`

Consider the following query:

```prolog
?- plus(s(s(0)),Y,Z).
```

In the first call, the first argument is not `0`, so the first clause fails.

The second clause performs the following unifications:

```text
X = s(0)
Z = s(Z1)
```

The recursive body call becomes:

```prolog
plus(s(0),Y,Z1)
```

The second clause is selected again.

```text
X = 0
Z1 = s(Z2)
```

The next recursive call becomes:

```prolog
plus(0,Y,Z2)
```

The first clause now succeeds.

```text
Z2 = Y
```

As the success continuations are followed back outward, the surrounding structures become determined.

```text
Z1 = s(Y)
Z  = s(s(Y))
```

The result is:

```prolog
Z = s(s(Y))
```

The entire recursive process is implemented without recursive C calls, using transitions among labels such as:

```text
plus_3
plus_3_1
plus_3_1_0back
plus_3
...
success
plus_3_1_1
success
plus_3_1_1
success
```

---

## 51. Execution Example: `times(s(s(0)),Y,Z)`

Consider the following query:

```prolog
?- times(s(s(0)),Y,Z).
```

In the second clause of the outer `times/3` call:

```text
X = s(0)
```

The following recursive call is made:

```prolog
times(s(0),Y,Z1)
```

The second clause is selected again.

```text
X = 0
```

The next recursive call is:

```prolog
times(0,Y,Z2)
```

The first clause produces:

```text
Z2 = 0
```

The success continuation then advances to the second goal of the inner clause.

```prolog
plus(0,Y,Z1)
```

Therefore:

```text
Z1 = Y
```

Execution then returns to the outer success continuation and performs:

```prolog
plus(Z1,Y,Z)
```

Because `Z1 = Y`, this is conceptually:

```prolog
plus(Y,Y,Z)
```

In this way, `times/3` receives the recursive multiplication result in `Z1` and passes it to the following `plus/3` call.

Because `Z1`, `Y`, and `Z` must remain available after the recursive call, the variable stack is required.

---

## 52. Label Naming Rules

The generated label names indicate their positions in the compiled control flow.

### Predicate Labels

```text
plus
times
```

### Arity Labels

```text
plus_3
times_3
```

### Clause Labels

```text
plus_3_0
plus_3_1
times_3_0
times_3_1
```

The general form is:

```text
predicate-name_arity_clause-number
```

### Body Goal Labels

```text
plus_3_1_0
times_3_1_0
times_3_1_1
```

These indicate positions of goals within a clause body.

### Post-Success Labels

```text
plus_3_1_1
times_3_1_1
times_3_1_2
```

These indicate positions executed after individual goals succeed.

### Backtracking Restart Labels

```text
plus_3_1_0back
times_3_1_0back
times_3_1_1back
```

These indicate positions from which execution resumes when backtracking into a particular goal.

---

## 53. Main SCBM APIs

The main APIs used by generated `recur` code are as follows:

| API             | Role                                                                 |
| --------------- | -------------------------------------------------------------------- |
| `Jsave_arg`     | Saves the top-level argument list                                    |
| `Jget_arg`      | Retrieves a saved argument list                                      |
| `Jpush_next`    | Saves a success continuation                                         |
| `Jpop_next`     | Removes a success continuation                                       |
| `Jpush_back`    | Saves a failure continuation and restart state                       |
| `Jpop_back`     | Removes a saved failure-continuation state                           |
| `Jset_back`     | Sets the next clause of the same predicate as a failure continuation |
| `Jpush_var`     | Saves a variable required after a predicate call                     |
| `Jpop_var`      | Restores a saved variable                                            |
| `Jget_choice`   | Obtains the clause number from which execution resumes               |
| `Jinc_choice`   | Advances to the next clause number                                   |
| `Jrelease`      | Releases the state created by the previous clause attempt            |
| `Jpush_recur`   | Participates in pushing recursive state onto SCBM                    |
| `Jpop_recur`    | Removes recursive state from SCBM                                    |
| `Jget_vp`       | Retrieves the saved variable-stack position                          |
| `Jget_np`       | Retrieves the saved success-continuation-stack position              |
| `Jdiscard_conj` | Discards the current conjunction state                               |
| `Jprove_all`    | Executes the remaining goals after the top-level predicate           |

---

## 54. General Form of Generated `recur` Code

A predicate containing a single recursive body goal is generally generated in the following form:

```c
predicate_clause:
    /* Retrieve arguments */
    /* Create clause variables */
    /* Perform head unification */

    arglist = /* arguments for the recursive call */;

    Jpush_back(
        &&clause_fail,
        arglist,
        vp[th],
        np[conj][th],
        th);

recursive_call_back:
    Jpush_next(&&after_recursive_call,th);

    clause = Jget_choice(th);
    goto predicate_arity;

after_recursive_call:
    goto success;

clause_fail:
    Jpop_back(th);
    goto allfail;
```

For a predicate containing multiple body goals, variable preservation between goals is added.

```c
first_goal:
    arglist = /* arguments for the first goal */;

    Jpush_var(/* variables required by later goals */);

    Jpush_back(
        &&clause_fail,
        arglist,
        vp[th],
        np[conj][th],
        th);

first_goal_back:
    Jpush_next(&&after_first_goal,th);
    goto first_predicate;

after_first_goal:
    /* Restore variables */

    arglist = /* arguments for the second goal */;

    Jpush_back(
        &&first_goal_back,
        arglist,
        vp[th],
        np[conj][th],
        th);

second_goal_back:
    Jpush_next(&&after_second_goal,th);
    goto second_predicate;

after_second_goal:
    goto success;
```

---

## 55. Difference from the `nondet` Type

A `nondet` predicate is generated as an independent C function for each predicate.

```c
static int c_color(int arglist, int rest, int th);
```

For a `recur` predicate, the small entry function is separate from the actual implementation, which is incorporated into the large function.

```c
static int recur_scbm(...);
```

The main differences are:

| Item                         | `nondet` type                          | `recur` type                            |
| ---------------------------- | -------------------------------------- | --------------------------------------- |
| Execution body               | Separate C function for each predicate | Shared large function                   |
| Recursion                    | Normally not applicable                | Implemented using labels and SCBM       |
| Clause selection             | Local clause selection                 | Clause labels inside the large function |
| Success continuation         | Mainly ordinary function return        | `next_stack`                            |
| Failure continuation         | `choice` and local clause control      | `back_stack` and SCBM                   |
| Clause-variable preservation | Normally unnecessary                   | Required when later goals use variables |
| Movement between predicates  | C function calls                       | `goto` within the large function        |

---

## 56. Summary

Because `plus/3` and `times/3` contain recursion, they are compiled as `recur` predicates.

The entry functions called from Prolog are small.

```c
c_plus(...)
c_times(...)
```

Each entry function passes the predicate number, arity, initial clause number, and argument list to the large function.

```c
recur_scbm(...)
```

Inside the large function, the execution position is selected through the following hierarchy:

```text
predicate
  ↓
arity
  ↓
clause
  ↓
goal within the clause body
```

Recursive calls are implemented not as recursive C function calls, but as `goto` statements to labels within the same large function.

```c
goto plus_3;
goto times_3;
```

The position to execute after success is saved as a success continuation.

```c
Jpush_next(...)
```

The position to execute after failure or when searching for another solution is saved as a failure continuation in SCBM.

```c
Jpush_back(...)
```

Clause variables required after a recursive call are saved on the variable stack.

```c
Jpush_var(...)
Jpop_var(...)
```

The body of `plus/3` contains only one goal, so the entire clause succeeds immediately after the recursive call succeeds.

The body of `times/3` contains two goals. It therefore saves clause variables before the first recursive call, restores them after that call succeeds, and then executes `plus/3`.

Through this mechanism, the generated code represents Prolog recursion, conjunction, success continuations, failure continuations, and backtracking using a large C function, labeled `goto` statements, and SCBM stacks.
