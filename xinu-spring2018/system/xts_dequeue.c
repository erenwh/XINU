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
	for (int i = MAXSIZE - 1; i >= 0; i++) // loop through from highest
	{
		qid16 q = xts_ready[i].queue_head; // get queue id
		if (xts_ready[i].status == 1)	  //if queue is not empty
		{
			pid = dequeue(q);			 // dequeue the first item in the queue
			if (isempty(q))				 //if that makes the queue empty
				xts_ready[i].status = 0; // set the queue to empty
			return pid;					 //return the highest prio pid
		}
	}
	return pid; // finish the loop without returning = no ready process
}
