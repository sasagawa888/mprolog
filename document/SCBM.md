## SCBM API

- Jpush_conj(th);
scp[CONJ][th]を１つ加算しそこにその時点でのSP,WP,ACを記憶する。
choiceポイントなどを初期化する。

- Jpush_back(cont,arglist,vp,np,th)

- Jpush_recur(arglist,vp,np,th);
scp[RECUR][th]を１つ加算しそこにその時点でのSP,WP,ACを記憶する。
choiceポイントなどを初期化する。Jpush_backから呼び出される。

- Jpop_recur(th);
SCP[RECUR][th]を１つ減ずる


- Jarity_count(arglist)
arglistの長さを返す。長さはキャッシュされる。
再度アクセスされるときにはキャッシュから返す。実行効率のためのものである。

- Jdiscard_conj(th)

- Jdiscard_recur(th)

- Jinc_choice(th)
choiceポイントに１を加算する。次に進む節を指定する。

- Jmax_choice(th)
choiceポイントを999,999,999とする。これによりallfailにgotoで
飛ぶこととなる。これは述語の完全失敗を意味する。

- Jrelease(th)
保存してあったsp(local stack pointer)により変数をunbindする。
保存してあったac(argument counter)に復元する。

- Jget_choice(th)
以前再帰した位置を返す。

- Jsuccess(arglist,th)
成功した場所においてそのときのarglistを記憶するとともに
SUCC_SCBMを１とする。

- Jget_disj_choice(th)
選言のためのchoiceポイントを取り出す。

- Jinc_disj_choice(th)
選言のためのchoiceポイントに１を加算する。

- Jreset_disj(th)
選言のためのchoiceポイントから１を減算する。

