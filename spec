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
          gen_dyn_head
          gen_dyn_head 
          gen_mut_head
          gen_tail_head  TCO用の頭部は特殊なので独自に作る
          

本体部生成 gen_nondet_body -> gen_a_nodnet_body  再帰的に本体部を生成する
           gen_det_body    -> gen_a_det_body
           gen_dyn_body    -> gen_a_dyn_body 
           gen_tail_body   -> gen_a_tail_body
           gen_mut_body    -> gen_a_mut_body

命名規則　Cコードを生成するもの　gen_***
          コンパイラ用の組み込み述語 n_***
　　　　　共通する述語は適宜、機能を表す命名

動的リンク関数　J****()  Jはプロジェクト名のJUMPに由来

動的リンク関数の縮減　動作するようになったら動的リンク関数を見直す。
これは実行時間において足かせになる。複合命令に統合するなど工夫する。


