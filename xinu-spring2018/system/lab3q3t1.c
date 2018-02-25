#include <xinu.h>

void lab3q3t1() {

        // Spawning several XINU processes and checking their monitored CPU usage.
        // 4 Process with same priority are going to share the cpu equally
        kprintf("\nTest3.1: Equal Priority\n");
/*#ifdef DEBUG
        int32 prcputot = getcputot(currpid);
        intmask mask = disable();
        struct procent *curr = &proctab[currpid];
        kprintf("\n\n%s(%d):\nprcputot:%d;clkmilli:%d,prctxswbeg:%d\n",curr->prname, currpid,prcputot,clkmilli,curr->prctxswbeg);
        restore(mask);
#endif*/
        resume(create(test, 1024, 35, "test1",0));
//        resume(create(test, 1024, 30, "test2",0));
//        resume(create(test, 1024, 30, "test3",0));
//        resume(create(test, 1024, 30, "test4",0));
        sleep(10);
//        printprocess();
        kprintf("\nEnd of Test3.1\n");
}
