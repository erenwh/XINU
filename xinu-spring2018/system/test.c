#include <xinu.h>
#include <test.h>
#define DEBUG
void test() {
    uint32 i;
//    while(i < UPBOUND) {
//        i++;
//    }
    for(i=0; i < UPBOUND; i++) {}

#ifdef DEBUG
    intmask mask = disable();
    struct procent *curr = &proctab[currpid];
    kprintf("\n\n%s(%d):\nprcputot:%d;clkmilli:%d,prctxswbeg:%d\n",curr->prname, currpid,getcputot(currpid),clkmilli,curr->prctxswbeg);
//    kprintf("\n%s:%dms\n",curr->prname,getcputot(currpid));
    restore(mask);
#endif 
}
