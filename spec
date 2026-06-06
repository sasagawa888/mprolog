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

prepare: selfstackに現時点でのwp,sp,acを記憶する。これはインタプリタで利用する。
         コンパイラとして動作しているときにはwp.sp.acの値は呼び出し元で
         backstackに記憶されている。Choiseする節番号を返す。これはコンパイラで利用する。
        
release: sp,acを解除するとともにchoice番号を+1する。

respond: インタプリタである場合にはproveallにより継続を呼び出す。
         コンパイラの場合にはyesを返す。それらの値をreturnすることにより述語を抜ける

discard: wpを復元することによりワーキングメモリを開放する。さらにコンパイラ動作している場合
にはBPをpopする。

pushback：非決定性述語を呼び出すときに呼び出し元で生成、backstackにpushしておく。
ここにwp,sp,acが保存されChoice節は0に初期化される。

decchoice：releaseにより通常はChoiceが+1となるが末尾再帰節である場合には
ここが再度選択点になることはない。そこでその場合には-1する。
コンパイル時に検出することも可能なのだけどそのためには次の節を解析すること
なり煩雑なので動的に処理すすることにする。


選言のコード生成
gen_nondet_body にオプションの項をついてして生成コードを調整する。
nonの場合には連言の最後はreturn(respond(rest,th))となる。
exceptの場合には連言の場合には res=respond(rest,th)となる。

A;B の場合
if(Aの連言)
if(res=YES) goto exit_A_M_N
if(Bの連言)
exit_A_M_N:
ラベルはユニークにするためにarity、M番目の節、N番目での選言
これによりネストした選言にも対応できる。

カットの生成
gen_nondet_body にカット出現の有無を表す項を追加する。
nonはカット出現なし。
cutは以前にカットが出現していることを表す。
カットが出現している場合全部失敗のときには次節に飛ばず
allfailに飛ぶ

A,!,B

if(A=yes){
    if(B=yes){
       return(respond());
    }
    goto allfail;
}

allfail:
discard();

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