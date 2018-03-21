/* xts-enqueue.c  -  xts_enqueue */

#include <xinu.h>

/**
 * 
 * enqueues the process given by pid and priority prio into the multilevel 
 * feedback queue at the appropriate place. 
 * xts_enqueue() return 0 if successful, -1 otherwise.
 * 
 */

int xts_enqueue(pid32 pid, /* pid of process */
				pri16 prio /* process's priority */
)
{

	qid16 q = xts_ready[prio].queue_head;
	
	
	if (enqueue(pid, q) == SYSERR) {
		//kprintf("enqueue error\n");
		return -1;
	}
	xts_ready[prio].status = 1; // set status to not empty
	return 0;
}
