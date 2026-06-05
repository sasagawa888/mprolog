#include "jump.h"
void init_tpredicate(void){
(deftpred)("foo",c_foo,1,2);
(deftpred)("bar",c_bar,1,1);
}
void init_declare(void){
int body,th; th=0;
boo();
body = Jwlist3(Jmakesys("append"),Jwlistcons(Jwlistcons(Jmakeint(1),NIL,th),Jwlistcons(Jwlistcons(Jmakeint(2),NIL,th),Jwlistcons(NIL,NIL,th),th),th),th);
Jprove_all(body,Jget_sp(th),th);
body = Jwlist3(Jmakesys("dynamic"),Jwlistcons(Jwcons(52,Jwcons(Jmakepred("boo"),Jwcons(Jmakeint(1),NIL,th),th),th),NIL,th),th);
Jprove_all(body,Jget_sp(th),th);
}