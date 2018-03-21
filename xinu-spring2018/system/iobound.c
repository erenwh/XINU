#include <xinu.h>
#define UP1  5
#define UP2  10
#define DEBUG
void iobound() {
    int32 i, j;
    //int count = 0;
    int pid = currpid;
    struct procent *curr = &proctab[pid];
    
    int32 sleeptime = 5;

    for(i = 0; i < UP1; i++) {
        for(j = 0; j < UP2; j++) {
            sleepms(sleeptime);
#ifdef  DEBUG
            int cputime = getcputot(pid);
            //intmask mask = disable();
            kprintf("IO(%d):, outer i: %d, Prio: %d, Preempt: %d,cputot:%d\n", pid, i, curr->prprio, preempt, cputime);
           // restore(mask);
#endif
        }
        
    }
#ifdef  DEBUG
    int cputime = getcputot(pid);
   // intmask mask = disable();
    kprintf("IOProcess Finished(%d): prcputot:%d, prprio:%d, preempt:%d\n", pid, cputime, curr->prprio, preempt);
    //restore(mask);
#endif
    return;
}
