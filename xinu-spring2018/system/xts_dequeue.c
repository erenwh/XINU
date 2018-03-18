/* xts-dequeue.c  -  xts_dequeue */

#include <xinu.h>

/**
 * 
 * returns the process ID of a highest priority ready process from xts_ready[]. 
 * If there are no ready processes outside of the kernel's NULL process, 
 * its PID 0 is returned
 * 
 */

pid32 xts_dequeue(void) {
	pid32 pid = 0;
	for (int i = 59; i >= 0; i++) {
		qid16 q = xts_ready[i].queue_head;
		if (xts_ready[i].status == 1) {
			pid = getfirst(q);
			queuetab[pid].qprev = EMPTY;
			queuetab[pid].qnext = EMPTY;
			return pid;
		}
	}
	return pid;
}
