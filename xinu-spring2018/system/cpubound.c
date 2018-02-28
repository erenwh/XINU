#include <xinu.h>
#define UP1  10
#define UP2  50
#define DEBUG
void cpubound() {
    int count = 0;
    int32 i, j;
    int pid = currpid;
    struct procent *curr = &proctab[pid];

    for(i = 0; i < UP1; i++) {
        for(j = 0; j < UP2; j++) {
            count++;
#ifdef  DEBUG
            int cputime = getcputot(pid);
            intmask mask = disable();
            kprintf("(%d):, outer i: %d, Prio: %d, Preempt: %d,cputot: %d\n", pid, i, curr->prprio, preempt, cputime);
            restore(mask);
#endif
        }


        
    }
#ifdef  DEBUG
    int cputime = getcputot(pid);
    intmask mask = disable();
    kprintf("Process Finished(%d): prcputot:%d, prprio:%d, preempt:%d\n", pid, cputime, curr->prprio, preempt);
    restore(mask);
#endif
    return;
}
