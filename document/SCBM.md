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
