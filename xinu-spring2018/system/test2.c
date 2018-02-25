#include <xinu.h>
#include <test.h>
#define DEBUG
void test2() {
    uint32 i = 0;
    while(i < UPBOUND) {
        i++;
    }
#ifdef DEBUG
    struct procent *curr = &proctab[currpid];
    kprintf("\n\n%s(%d):\nprcputot:%d;clkmilli:%d,prctxswbeg:%d\n",curr->prname, currpid,getcputot(currpid),clkmilli,curr->prctxswbeg);
//    kprintf("\n%s:%dms\n",curr->prname,getcputot(currpid));
#endif 
}
