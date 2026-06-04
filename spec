M-Prolog　コンパイラ仕様

u:- use_module(compiler).


compile_file(filename)
compile_file(filename,option)  option c only generate C code
                                      o only generate Object code from C code


type(Predicate,Arity,type)  type [nondet,det,tail,dyn,mut]
mode(Predicate,Arity,[+,+,-,-])

p/2 p/3 が混在する場合には全体をtypeに従って生成する。arityは無視する。述語情報としてgen_defで利用する。
モードはアリティーの異なるごとに分析する。

pass1   typeの判定
pass2   typeの判定　2パスでtypeの判定をする。後続の述語に依存してtypeが決まる場合があるので
　　　　2パス方式とする。
mode1   モードの判定
mode2 　2パス方式とする。後続の述語に依存する場合がある。

analize pass1 pass2 により呼び出されてtype/2をassertする。
modeinf mode1 mode2 により呼び出されて決定性述語についてそのmodeを推論するｌ

pass3　Cコード生成とオブジェクトコードの生成

gen_pred  reconsult したすべての述語の本体のCコードを生成する。
gen_def　 reconslutしたすべての述語の定義のCコードを生成する。

gen_a_pred  1つの述語の本体を生成する。これはtypeにより次のように分岐する。
            gen_a_nondet_pred 非決定性述語
            gen_a_det_pred　決定性述語
            gen_a_dyn_pred　動的述語
            gen_a_tail_pred　末尾再帰述語
            gen_a_mut_pred　関数類似述語

typeの異なるごとに頭部生成、本体部生成のコードをもつ。
類似しているものもあるが、メンテナンスするうえで各々独立させておいた方が良い

頭部生成　gen_nondet_head
          gen_det_head 
          gen_dyn_head
          gen_dyn_head 
          gen_tail_head
          gen_mut_head

本体部生成 gen_nondet_body
           gen_det_body 
           gen_dyn_body
           gen_tail_body 
           gen_mut_body


動的リンク関数の縮減　動作するようになったら動的リンク関数を見直す。
これは実行時間において足かせになる。複合命令に統合するなど工夫する。


