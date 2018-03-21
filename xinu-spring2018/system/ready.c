/* ready.c - ready */

#include <xinu.h>

qid16 readylist; /* Index of ready list		*/

/*------------------------------------------------------------------------
 *  ready  -  Make a process eligible for CPU service
 *------------------------------------------------------------------------
 */
status ready(
	pid32 pid /* ID of process to make ready	*/
)
{
	register struct procent *prptr;

	if (isbadpid(pid))
	{
		return SYSERR;
	}

	/* Set process state to indicate ready and add to ready list */

	prptr = &proctab[pid];
	prptr->prstate = PR_READY;
	//prptr->prbool = TRUE;
	//insert(pid, readylist, prptr->prprio);
	//kprintf("ready:pid:%d, prprio:%d\n",pid,prptr->prprio);
	xts_enqueue(pid, prptr->prprio);
	resched();

	return OK;
}
