/* xts-dequeue.c  -  xts_dequeue */

#include <xinu.h>

/**
 * 
 * returns the process ID of a highest priority ready process from xts_ready[]. 
 * If there are no ready processes outside of the kernel's NULL process, 
 * its PID 0 is returned
 * 
 */

pid32 xts_dequeue(void)
{
	pid32 pid = 0;
	for (int i = 59; i >= 0; i++)
	{
		qid16 q = queueArr[i];
		if (!isempty(q))
		{
			pid = getfirst(q);
			queuetab[pid].qprev = EMPTY;
			queuetab[pid].qnext = EMPTY;
			if (!nonempty(q))
			{
				xts_ready[i].status = 0;
			}
			return pid;
		}
	}
	return pid;
}
