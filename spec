M-Prolog　コンパイラ仕様

:- use_module(compiler).


compile_file(filename)
compile_file(filename,option)  option c only generate C code
                                      o only generate Object code from C code


type(Predicate,Arity,type)  type [nondet,det,tail,dyn,mut]
mode(Predicate,Arity,[+,+,-,-])

p/2 p/3 が混在する場合には全体をtypeに従って生成する。arityは無視する。述語情報としてgen_definitionで利用する。
モードはアリティーの異なるごとに分析する。
同一述語名で arity の異なる定義がある場合、type は述語名単位で1つだけ判定する。
arity ごとに異なる type を持つことは想定しない。mode は arity ごとに推論する。

pass1   typeの判定
pass2   typeの判定　2パスでtypeの判定をする。後続の述語に依存してtypeが決まる場合があるので
　　　　2パス方式とする。
mode1   モードの判定
mode2 　2パス方式とする。後続の述語に依存する場合がある。

analize pass1 pass2 により呼び出されてtype/3をassertする。
modeinf mode1 mode2 により呼び出されて決定性述語についてそのmodeを推論,assert mode/3

pass3　Cコード生成とオブジェクトコードの生成

gen_predicate  reconsult したすべての述語の本体のCコードを生成する。
gen_definition reconslutしたすべての述語の定義のCコードを生成する。
gen_a_pred(P) 述語Pを生成する  
            gen_nondet_pred(P) 非決定性述語
            gen_det_pred(P) 決定性述語
            gen_tail_pred(P) 動的述語
            gen_dyn_pred(P) 末尾再帰述語
            gen_mut_pred(P) 関数類似述語

            gen_nondet_clause(C) 
            gen_det_clause(C)
            gen_dyn_clause(C)
            gen_tail_clause(C)
            gen_mut_clause(C)

typeの異なるごとに頭部生成、本体部生成のコードをもつ。
類似しているものもあるが、メンテナンスするうえで各々独立させておいた方が良い

頭部生成　gen_nondet_head  nondetなどは頭部の構成は同じなので共通して
          gen_det_head    gen_headを呼び出す
          gen_dyn_head　　これらは同じ機能なので
          gen_dyn_head 
          gen_mut_head
          gen_tail_head  TCO用の頭部は特殊なので独自に作る
          

本体部生成 gen_nondet_body -> gen_a_nodnet_body  再帰的に本体部を生成する
           gen_det_body    -> gen_a_det_body
           gen_dyn_body    -> gen_a_dyn_body 
           gen_tail_body   -> gen_a_tail_body
           gen_mut_body    -> gen_a_mut_body

命名規則　Cコードを生成するもの　gen_***
          主たる述語名は正確にする。例 gen_definition 
          その内部の述語名は省略可。長くなりすぎるとバグや誤読の原因となる。
          コンパイラ用の組み込み述語 n_***
　　　　　共通する述語は適宜、機能を表す命名

動的リンク関数　J****()  Jはプロジェクト名のJUMPに由来

動的リンク関数の縮減　動作するようになったら動的リンク関数を見直す。
これは実行時間において足かせになる。複合命令に統合するなど工夫する。

Prologの制御に特有な機能を次の動的リンク関数に集約する
prepare(rest,th) 
release(rest,th)
respond(rest,th)
discard(rest,th)
pushback(th)
decchoice(th)

restはインタプリタが使用する後続述語のための構文木リストである。
これがNILのときにはコンパイルコードとして動作している。これを
スイッチとしてインタプリタとしての動作なのかコンパイラとしての動作
なのかを判別する。thはスレッドである。

arity_count(arglist) 引数の数を返す。その値はキャッシュされている。これによりバックトラックで
呼び出されたときの再計算を省略できる。

prepare: selfstackに現時点でのwp,sp,acを記憶する。これはインタプリタで利用する。
         コンパイラとして動作しているときにはwp.sp.acの値は呼び出し元で
         backstackに記憶されている。したがってこのprepareはインタプリタようである。
         if(rest!=NIL){}のときに呼び出される。
        
release: sp,acを解除する。restに応じて解除する。

respond: インタプリタである場合にはproveallにより継続を呼び出す。
         コンパイラの場合にはyesを返す。それらの値をreturnすることにより述語を抜ける
         if(rest != NIL){respond(rest,th)}のように本体部の最後で呼び出される。

discard: wpを復元することによりワーキングメモリを開放する。さらにコンパイラ動作している場合
にはBPをpopする。

pushback：非決定性述語を呼び出すときに呼び出し元で生成、backstackにpushしておく。
ここにwp,sp,acが保存されChoice節は0に初期化される。

inc_choice：releaseでは節選択点は変更しない。これにより選択点を+1する。

選言のコード生成
gen_nondet_body にオプションの項をついてして生成コードを調整する。
retの場合には連言の最後はreturn(respond(rest,th))となる。
resの場合には連言の場合には res=respond(rest,th)となる。

A;B の場合
if(Aの連言)
if(res=YES) goto exit_A_M_N
if(Bの連言)
exit_A_M_N:
ラベルはユニークにするためにarity、M番目の節、N番目での選言
これによりネストした選言にも対応できる。

選言においてfailにより再試行する場合
nondetを呼び出すまえにJpush_back()を実行する。ここではdisjunction-choiceを０として設定する。
選言の左が成功した場合にはそれを+1として１とする。再試行する場合にはこれを参照してgotoにより飛ぶ。
disjunction-choiceのためにL引数を追加する。これは０から順番にユニークになる。ネストした場合にこれで
ラベルをユニークにできる。

disj = Jget_back_disj(th);
switch(disj){
    case 0: goto disj_A_M_N_0;
    case 1: goto disj_A_M_N_1;
}
disj_A_M_N_0:
if(A=YES){
Jinc_disj(th);
res = YES;
}
if(res == YES) goto exit_A_M_N_L;
disj_A_M_N_1:
if(B=YES){
res = YES;
}
exit_A_M_N_L:


カットの生成
カットが出現した場合にはBacktrackを[]にする。
Bの生成中はBacktrackは[]なのでバックトラックを生成しない。
次節に進む

A,!,B

if(A=yes){
    if(B=yes){
       return(respond());
    }
}
next_clause:

本体部の末尾にカットがある場合。
A,B,!.
if(A=yes){
    if(B=yes){
       max_choice(th);
       return(respond());
    }
}

max_choiceを呼び出す。これは次節を999,999,999に設定する。
これにより失敗により再度呼び出される場合にはallfailに飛ぶ。
全部失敗となる。



特殊構文
ifthenelse・ifthen

A->B;C
A,B,Cを生成するときに選言と同様にres=respond()を生成する

if(A){
if(res=YES){
    if(B)
    goto exit_A_M_N
   }
} 
if(C)
exit_A_M_N

A->B 
if(A){
if(res=YES){
    if(B)
   }
} 

決定性述語における式評価
det判定のなった述語の生成である。この場合にはバックトラックはない。
X is Y+2*pi でXが再計算されることはない。したがってコンパイル時に計算可能なものは
計算しておいて算術演算を呼び出すコードを生成しておく。gen_det_evalにまとめる。
<= =:= などの算術比較述語においても同様である。

非決定性述語における式評価
nondet判定になった述語の生成である。バックトラックに備えなければならない。
X is Y+2*pi で再計算される可能性がある。算術演算を呼び出すのはis/2に任せる。
バックトラックした場合にはrelease(rest,th)によりYの値は解除される。
gen_argumentに引数生成をまとめる。比較演算においても同様である。


スタック
３つのスタックをもつ
localstack
backstack 
envstack

localstak:  局所変数の束縛を記憶している。SPにより管理される。
局所変数はvariantと呼ばれる配列に記憶される。それが束縛している場合に
localstakに記憶される。SPを管理することによりその束縛状態は解除される。

backstack: 非決定性述語の呼び出しのために使用される。呼び出し元がその時点での
sp,wp,acを保持する。選択節の番号の初期値0を保持する。呼び出された側は
これらの値をもとにして次節へ制御を移し、最終的に全部失敗して終わる。
backstackは[1]からコンパイラで使われる、[0]はインタプリタで使われる。
述語呼び出しは最初はインタプリタから起動されるこのときpush_backは行われていない。
このため[0]が使われる。inc_choiceがインタプリタでも起動するが実害はない。

envstack: インタプリタから呼び出された述語が開始時にsp,wp,acを保持するために使用する。
述語が始まるときにprepare命令によりpushされる。
述語が終わるときにdiscard命令によりpopされて解除される

