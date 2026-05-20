# Mode Inference Prototype
The mode library is planned to eventually be integrated into and absorbed by the compiler.

# Example Execution
N-Prolog Ver 5.19 [30M cells]
?- use_module(mode).
yes
?- infer('./tests/bug').
inference1
inference2
yes
?- listing(mode).
mode(dummy,0,[]).
mode(partition,4,['+','+','-','-']).
mode(partition,4,['-','+','+','+']).
mode(foo,2,['-','+']).
mode(fact,2,['+','-']).
mode(bar,1,['+']).
mode(qsort,3,['+','-','+']).
yes
?-

The system analyzed the code in bug.pl and inferred the input/output modes of the predicates.

The analyzed code is shown below.

% mode test data

qsort([X|L], R, R0) :-
    partition(L, X, L1, L2),
    qsort(L2, R1, R0),
    qsort(L1, R, [X|R1]).
qsort([], R, R) :- !.

partition([X|L], Y, [X|L1], L2) :-
    X < Y, !, partition(L, Y, L1, L2).
partition([X|L], Y, L1, [X|L2]) :-
    !, partition(L, Y, L1, L2).
partition([], _, [], []) :- !.


% test case
foo(X,Y) :- true, X is Y.

fact(0,1).
fact(N,M) :-
    N1 is N-1,
    fact(N1,M1),
    M is N*M1.

bar(X) :- write(X).

boo(1,2).

+ denotes an input argument.
- denotes an output argument.

Predicates whose modes cannot be inferred are ignored.
In the above example, boo/2 is not analyzed.

# Two-Pass Analysis

qsort/3 depends on partition/4.

Without first analyzing partition/4, accurate mode inference for qsort/3 is impossible.
Therefore, the system uses a two-pass analysis.

During the first pass, the mode of qsort/3 remains unresolved.
The inference is completed during the second pass after the mode information for partition/4 becomes available.

# Inference Rules

Reasoning that is trivial for humans turned out to be surprisingly difficult to express in Prolog.

In partition/4, [X|L] and [X|L1] have the same structure and share the variable X.
Therefore, the system assumes that one side is input and the other side is output.
From the condition X < Y, both X and Y must already be instantiated.
Therefore, they must belong to input arguments.

The usual mode of partition/4 is:

partition(+,+,-,-)

However, the reverse direction is also possible and executable in Prolog, so the system generates two modes.

In qsort/3, L1 and L2 are free variables, so they are inferred to be outputs.
Using the already inferred mode information for partition/4, the system infers that L and X are inputs.
R1 is a free variable, so it is inferred to be an output.
In [X|R1], R1 is an output variable.
Therefore, the list structure itself is already determined, and the third argument is inferred to be an input.

The system derives modes through this kind of reasoning.

For fact/2, the inference relies on the semantics of is/2.

The left-hand side of is/2 is treated as an output, while variables appearing on the right-hand side are treated as inputs.

For bar/1, the argument of write/1 must already be instantiated.
Therefore, X is inferred to be an input.

Predicates such as boo(1,2) are treated as simple database facts and are excluded from analysis.

# Spec 

Env = [e(1,2),c(varY,+),c(varX,+),c(2,varY),c(1,varX)]
c/2　connect c(1,[X|L])
e/2 exclusive e(2,3)
s/3 state s(R,+)
a/1 argument  a(1,+)   
