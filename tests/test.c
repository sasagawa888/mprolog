#include "jump.h"
void boo(void){
dynamic_clause = Jcons(26,Jcons(Jcons(Jmakepred("boo"),Jcons(Jmakevar("varX"),NIL)),Jcons(Jcons(1204,Jcons(Jmakevar("varX"),NIL)),NIL)));
Jadd_dynamic(dynamic_clause);
}void init_tpredicate(void){
}
void init_declare(void){
int body,th; th=0;
boo();
body = Jcons(1568,Jcons(Jcons(52,Jcons(Jmakepred("boo"),Jcons(Jmakeint(1),NIL))),NIL));
Jprove_all(body,Jget_sp(th),th);
}