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

## SCBM API

- Jpush_conj(th);
scp[CONJ][th]を１つ加算しそこにその時点でのSP,WP,ACを記憶する。
choiceポイントなどを初期化する。

- Jpush_recur(th);
scp[RECUR][th]を１つ加算しそこにその時点でのSP,WP,ACを記憶する。
choiceポイントなどを初期化する。
その位置がすでに再帰で訪れた場所である場合には単にscp[RECUR][th]を１つ加算する。

- Jpop_recur(th);
再帰する述語において成功して戻ってきたときにその位置のREUSE_SCBMを１とする。
SCP[RECUR][th]を１つ減ずる

- Jsuccess(arglist,th);
成功した時点でのarglistを保存するとともに、SUCC_SCBMを１とする。

- Jprepare(arglist,th);
以前に成功していて直前のarglistが保存されている場合にはそれを返す。
そうでなければ引数として与えられたarglistを返す。
これは再帰のバックトラック時において直前成功時点の値を復元するものである。

- Jdiscard(th);
SCPが保持する位置の全要素を０クリアする。
SCPが保持する位置からの再帰位置を全部０クリアする。

- Jinc_choice(th);
choiceポイントに１を加算する。次に進む節を指定する。

- Jmax_choice(th);
choiceポイントを999,999,999とする。これによりallfailにgotoで
飛ぶこととなる。これは述語の完全失敗を意味する。

- Jrelease(th);
保存してあったsp(local stack pointer)により変数をunbindする。
保存してあったac(argument counter)に復元する。

- Jget_choice(th);
以前再帰した位置ならばchoice+9999を返す
以前再帰して成功した位置ならばchoiceを返す。
再帰でない場合にはchoiceを返す。

- Jsuccess(arglist,th);
成功した場所においてそのときのarglistを記憶するとともに
SUCC_SCBMを１とする。

- Jget_disj_choice(th);
選言のためのchoiceポイントを取り出す。

- Jinc_disj_choice(th);
選言のためのchoiceポイントに１を加算する。

- Jreset_disj(th);
選言のためのchoiceポイントから１を減算する。

