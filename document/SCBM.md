# SCBM API Specification

## Overview

SCBM (Success Continuation and Backtracking Mechanism) is the execution mechanism used by the M-Prolog compiler to implement Prolog control flow directly in C.

SCBM3 does not use the WAM instruction model. Instead, compiled Prolog predicates are translated into C code using direct control transfers, including computed `goto`, together with two lightweight runtime stacks:

* the **next stack**, which manages success continuations;
* the **back stack**, which manages backtracking points and their execution environments.

The design deliberately keeps these two mechanisms independent.

## Basic Data Structures

```c
static void *next_goto[RECURSIZE][THREADSIZE];
static void *back_goto[RECURSIZE][THREADSIZE];
static void *back_goto1[RECURSIZE][THREADSIZE];

static int next_stack[RECURSIZE][THREADSIZE];
static int back_stack[RECURSIZE][SCBM_ELT_SIZE][THREADSIZE];

static int np[THREADSIZE]; /* next pointer */
static int rp[THREADSIZE]; /* back/recur pointer */
```

`np` points to the current success continuation.

`rp` points to the current backtracking frame.

Conceptually:

```text
             Success                     Failure
            Continuation                Continuation
                 |                           |
                 v                           v
          +--------------+            +--------------+
 np ----> |  next_goto   |     rp --->|  back_goto   |
          |  next_stack  |            |  back_stack  |
          +--------------+            +--------------+
```

The next stack describes what should happen after a goal succeeds.

The back stack describes what should happen when execution must backtrack.

---

## Backtracking Frame

Each backtracking frame contains the execution state required by a choice point.

The following values are currently stored:

```text
SP_SCBM       stack pointer
WP_SCBM       working pointer
AC_SCBM       argument/variable allocation state
ARGLIST_SCBM  argument list
NP_SCBM       next-stack pointer
CHOICE_SCBM   current alternative number
```

`back_goto` contains the currently active failure continuation.

`back_goto1` contains the original failure continuation installed when the frame was created. This makes it possible to temporarily replace a failure continuation and later restore it.

---

# API

## Spush_next

```c
void Spush_next(void *cont, int pointer, int th);
```

Pushes a success continuation onto the next stack.

`cont` is the address to which execution continues after successful completion of the current goal.

`pointer` is auxiliary information associated with the continuation.

The operation increments `np` and stores both values:

```c
np[th]++;
next_goto[np[th]][th] = cont;
next_stack[np[th]][th] = pointer;
```

A stack overflow raises a resource error.

---

## Spop_next

```c
void Spop_next(int th);
```

Removes the current success continuation from the next stack.

Conceptually:

```c
np[th]--;
```

A stack underflow raises a resource error.

---

## Spush_back

```c
void Spush_back(void *cont, int arglist, int th);
```

Creates a new backtracking frame.

The operation increments `rp` and saves the execution state associated with the new choice point.

The current implementation stores:

```c
SP
WP
AC
arglist
np
choice = 0
```

The failure continuation is stored in both:

```c
back_goto[rp[th]][th]
back_goto1[rp[th]][th]
```

`back_goto` may subsequently be changed.

`back_goto1` preserves the original continuation so that it can be restored later.

---

## Spop_back

```c
void Spop_back(int th);
```

Removes the current backtracking frame.

Conceptually:

```c
rp[th]--;
```

No execution environment is restored by this operation. Environment restoration is handled separately by `Srelease()`.

A stack underflow raises a resource error.

This separation is intentional: `Spop_back()` manages the lifetime of a backtracking frame, while `Srelease()` restores execution state.

---

## Sset_back

```c
void Sset_back(void *cont, int th);
```

Changes the active failure continuation of the current backtracking frame.

Conceptually:

```c
back_goto[rp[th]][th] = cont;
```

The original continuation stored in `back_goto1` is not modified.

This operation is useful when compiled code temporarily requires a different failure destination.

---

## Sreset_back

```c
void Sreset_back(int th);
```

Restores the original failure continuation of the current backtracking frame.

Conceptually:

```c
back_goto[rp[th]][th] =
    back_goto1[rp[th]][th];
```

Thus the following sequence is possible:

```text
Spush_back(A)
      |
      v
 active = A
 original = A

Sset_back(B)
      |
      v
 active = B
 original = A

Sreset_back()
      |
      v
 active = A
 original = A
```

---

## Sinc_choice

```c
void Sinc_choice(int th);
```

Increments the alternative number of the current choice point.

Conceptually:

```c
back_stack[rp[th]][CHOICE_SCBM][th]++;
```

This value is used by compiled nondeterministic predicates to select the next alternative during backtracking.

---

## Sget_choice

```c
int Sget_choice(int th);
```

Returns the current alternative number stored in the current backtracking frame.

This function has no side effects.

Proof-counting or other execution statistics are intentionally kept outside this function.

A typical generated-code pattern is therefore:

```c
Jinc_proof(th);

switch (Sget_choice(th)) {
case 0:
    ...
case 1:
    ...
}
```

---

## Srelease

```c
void Srelease(int th);
```

Restores the execution environment saved in the current backtracking frame.

The current implementation restores the binding state and AC:

```c
Junbind(back_stack[rp[th]][SP_SCBM][th], th);
Jset_ac(back_stack[rp[th]][AC_SCBM][th], th);
```

WP is also stored in the backtracking frame and is intended to be restored in the final implementation.

`Srelease()` does **not** decrement `rp`.

This distinction is important:

```text
Srelease()
    restores the state of the current frame

Spop_back()
    removes the current frame
```

---

## Sget_arg

```c
int Sget_arg(int th);
```

Returns the argument list saved in the current backtracking frame.

Conceptually:

```c
return back_stack[rp[th]][ARGLIST_SCBM][th];
```

The saved argument list can be used when execution re-enters compiled code through a backtracking continuation.

---

## Ssave_arg

```c
void Ssave_arg(int x, int th);
```

Replaces the argument list stored in the current backtracking frame.

Conceptually:

```c
back_stack[rp[th]][ARGLIST_SCBM][th] = x;
```

---

## Sget_np

```c
int Sget_np(int th);
```

Returns the value of `np` that was saved when the current backtracking frame was created.

Conceptually:

```c
return back_stack[rp[th]][NP_SCBM][th];
```

This is not necessarily the same as the current value of `np[th]`.

It represents the success-continuation state associated with the current choice point.

---

# Design Principle

The central idea of SCBM3 is the separation of success and failure control flow.

The **next stack** answers:

> Where should execution continue if this goal succeeds?

The **back stack** answers:

> Where should execution continue, and what state is required, if this computation must backtrack?

Thus:

```text
Success direction

    Spush_next
        |
        v
     execute
        |
     success
        |
        v
    next_goto


Failure direction

    Spush_back
        |
        v
     execute
        |
     failure
        |
        v
    back_goto
```

The two stacks interact when necessary—for example, a backtracking frame records the value of `np` existing when the choice point was created—but their responsibilities remain separate.

---

# Design Goals

SCBM3 follows several design principles.

### Simplicity

The runtime API is intentionally small. Operations that do not directly belong to success continuation or backtracking management are kept outside SCBM.

### Explicit Control Flow

Compiled Prolog control flow is represented directly by C labels and continuation addresses rather than by an intermediate virtual-machine instruction set.

### Minimal Hidden State

Getter functions should retrieve values without unrelated side effects. Operations such as proof counting are performed explicitly by generated code.

### Separation of Responsibilities

Success continuation management, backtracking-frame management, environment restoration, and alternative selection are separate operations.

For example:

```text
Spush_next / Spop_next
    success continuation management

Spush_back / Spop_back
    backtracking-frame management

Sset_back / Sreset_back
    failure-continuation management

Srelease
    execution-state restoration

Sinc_choice / Sget_choice
    alternative management

Ssave_arg / Sget_arg
    argument-list management

Sget_np
    saved success-continuation state
```

This separation keeps the runtime mechanism small and makes the generated C code easier to inspect and debug.

---

## Summary

SCBM3 implements Prolog execution using two simple concepts:

```text
np = success continuation state
rp = backtracking state
```

A success continuation records where execution proceeds after success.

A backtracking frame records where execution proceeds after failure together with the state required to resume the search.

The resulting runtime interface is deliberately small. Most of the Prolog control structure is expressed directly in the C code generated by the M-Prolog compiler rather than being hidden inside a large virtual-machine runtime.
