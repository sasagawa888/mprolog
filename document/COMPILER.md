# Compiler

# Usage
To use the compiler in N-Prolog, you need to load the module. Compilation is performed using compile_file/1.

```
N-Prolog Ver 3.91
?- use_module(compiler).
yes
?- compile_file('./tests/fact.pl').
phase pass1
phase pass2
compiling fact
invoke GCC
yes
?- 

```
# Note
If you are using libraries, and you define a predicate with the same name as one contained in those libraries, a compilation error will occur. In such cases, please rename the predicate.

# Option

- compile_file(F,c)
If you provide c as the second argument, the converted C code will be retained. You can check what kind of code is being generated.

- compile_file(F,o)
If you provide o as the second argument, it simply compiles the C source code and generates the object code. This is useful when you need to manually modify the compiled code.

- compile_file(F,a)
If you provide co a the second argument, it snalize prolog code. not generate c source or object code.


# C inline
N-Prolog allows embedding C code in the body section. When a string is passed to cinline/1, it is directly embedded into the compiled code as is.

e.g.

```
ack(M,N,X) :-
cinline($ int a(int m, int n){
              if(m==0) return(n+1);
              else if(n==0) return(a(m-1,1));
              else return(a(m-1,a(m,n-1)));
          }
          int m = Jget_int(Jderef(varM,th));
          int n = Jget_int(Jderef(varN,th));
          int res = a(m,n);
          Junify(varX,Jmakeint(res),th);
          return(Jexec_all(rest,Jget_sp(th),th)); $).

```
cinline/1 only functions when there is a single instance in the body. Multiple instances of cinline/1 will not work correctly.


## C inline declare
To embed C code such as #include and #define, use cdeclate/1.
e.g. 

```
cdeclare($#define a 1$).
cdeclare($#define b 2$).
cdeclare($#include <stdio.h>$).
```

## C inline library option
To add compilation options, use clibrary/1.
e.g. 

```
clibrary($-ltcl -ltk$).
```

## C inline variable
In compiled Prolog, variable names have 'var' prefixed to them at compile time. When retrieving a value, deref is called first, and then the value is converted to a C value using an API corresponding to its type.
