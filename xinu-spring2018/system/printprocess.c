#include <xinu.h>

void printprocess() {
    struct procent *prptr;
    char *pstate[]  = {             /* names for process states     */
        "free ", "curr ", "ready", "recv ", "sleep", "susp ","wait ", "rtime"};

    for (int i = 0; i < NPROC; i++) {
        prptr = &proctab[i];
        if(prptr->prstate == PR_FREE) {
            continue;
        }
        printf("%3d %-16s %s %4d %4d 0x%08X 0x%08X %8d\n",
                i, prptr->prname, pstate[(int)prptr->prstate],
                prptr->prprio, prptr->prparent, prptr->prstkbase,
                prptr->prstkptr, prptr->prstklen);
    }
}
