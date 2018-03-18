/* resched.c - resched, resched_cntl */

#include <xinu.h>

struct defer Defer;

/*------------------------------------------------------------------------
 *  resched  -  Reschedule processor to highest priority eligible process
 *------------------------------------------------------------------------
 */
void resched(void) /* Assumes interrupts are disabled	*/
{

	struct procent *ptold; /* Ptr to table entry for old process	*/
	struct procent *ptnew; /* Ptr to table entry for new process	*/

	/* If rescheduling is deferred, record attempt and return */

	if (Defer.ndefers > 0)
	{
		Defer.attempt = TRUE;
		return;
	}

	/* Point to process table entry for the current (old) process */
	uint32 currTime = clktimemsec;
	uint32 addTotal = 0;
	ptold = &proctab[currpid];
	addTotal = currTime - (ptold->prctxswintime);
	ptold->prcpumsec = ptold->prcpumsec + addTotal;

	if (ptold->prstate == PR_CURR)
	{ //CPU

		pri16 oldprio = ptold->prprio;				 //save old
		pri16 newprio = xts_conf[oldprio].xts_tqexp; //update new base on TS table
		ptold->prprio = newprio;					 // update old

		// if old prio is higher than list
		pri16 readyHigh = xts_priochk();
		if (ptold->prprio > readyHigh)
		{
			return;
		}

		/* Old process will no longer remain current */

		ptold->prstate = PR_READY;
		xts_enqueue(currpid, ptold->prprio);
		//insert(currpid, readylist, ptold->prprio);
	}
	else if (ptold->prstate == PR_SLEEP)
	{												  // cpu intensive
		pri16 oldprio = ptold->prprio;				  //save old
		pri16 newprio = xts_conf[oldprio].xts_slpret; //update new base on TS table
		ptold->prprio = newprio;					  // update old
	}

	/* Force context switch to highest priority ready process */

	//currpid = dequeue(readylist);
	currpid = xts_dequeue(); // dequeue from xts
	ptnew = &proctab[currpid];
	ptnew->prstate = PR_CURR;
	ptnew->prctxswintime = currTime;
	//preempt = QUANTUM;		/* Reset time slice for process	*/
	preempt = xts_conf[ptnew->prprio].xts_quantum; //update quantum base on TS table
	ctxsw(&ptold->prstkptr, &ptnew->prstkptr);

	/* Old process returns here when resumed */

	return;
}

/*------------------------------------------------------------------------
 *  resched_cntl  -  Control whether rescheduling is deferred or allowed
 *------------------------------------------------------------------------
 */
status resched_cntl(			/* Assumes interrupts are disabled	*/
					int32 defer /* Either DEFER_START or DEFER_STOP	*/
)
{
	switch (defer)
	{

	case DEFER_START: /* Handle a deferral request */

		if (Defer.ndefers++ == 0)
		{
			Defer.attempt = FALSE;
		}
		return OK;

	case DEFER_STOP: /* Handle end of deferral */
		if (Defer.ndefers <= 0)
		{
			return SYSERR;
		}
		if ((--Defer.ndefers == 0) && Defer.attempt)
		{
			resched();
		}
		return OK;

	default:
		return SYSERR;
	}
}