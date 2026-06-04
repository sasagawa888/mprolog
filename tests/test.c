#include "jump.h"
void init_tpredicate(void){
(deftpred)("foo",c_foo,1,2);
}
void init_declare(void){
int body,th; th=0;
body = Jwlist3(Jmakesys("append"),Jwlistcons(Jwlistcons(Jmakeint(1),NIL,th),Jwlistcons(Jwlistcons(Jmakeint(2),NIL,th),Jwlistcons(Jwlistcons(Jmakeint(1),Jwlistcons(Jmakeint(2),NIL,th),th),NIL,th),th),th),th);
Jprove_all(body,Jget_sp(th),th);
}