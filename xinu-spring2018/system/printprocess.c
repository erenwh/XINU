#include <xinu.h>

void printprocess() {
    struct procent *prptr;
    char *pstate[]  = {             /* names for process states     */
        "free ", "curr ", "ready", "recv ", "sleep", "susp ","wait ", "rtime","time"};

        kprintf("\n**************Printing Process Info**************************\n");
	kprintf("%3s %-16s %5s %4s %4s %10s %-10s %10s %4s\n",
		   "Pid", "Name", "State", "Prio", "Ppid", "Stack Base",
		   "Stack Ptr", "Stack Size", "Time");

	kprintf("%3s %-16s %5s %4s %4s %10s %-10s %10s %4s\n",
		   "---", "----------------", "-----", "----", "----",
		   "----------", "----------", "----------","----");
    for (int i = 0; i < NPROC; i++) {
        prptr = &proctab[i];
        if(prptr->prstate == PR_FREE) {
            continue;
        }
        kprintf("%3d %-16s %s %4d %4d 0x%08X 0x%08X %8d %4d\n",
                i, prptr->prname, pstate[(int)prptr->prstate],
                prptr->prprio, prptr->prparent, prptr->prstkbase,
                prptr->prstkptr, prptr->prstklen, prptr->prcputot);
    }
        kprintf("\n**************END********************************************\n");
}
