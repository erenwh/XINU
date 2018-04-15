/* receive.c - receive */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  receive  -  Wait for a message and return the message to the caller
 *------------------------------------------------------------------------
 */
umsg32 receive(void)
{
	intmask mask;		   /* Saved interrupt mask		*/
	struct procent *prptr; /* Ptr to process' table entry	*/
	umsg32 msg;			   /* Message to return		*/
	pid32 unblocked;

	mask = disable();
	prptr = &proctab[currpid];

	if (prptr->prhasmsg == FALSE)
	{
		prptr->prstate = PR_RECV;
		resched(); /* Block until message arrives	*/
	}

	msg = prptr->prmsg;		 /* Retrieve message		*/
	prptr->prhasmsg = FALSE; /* Reset message flag		*/
	kprintf("\n(PID:%d):Message recieved: %c\n", currpid, msg);
	if (prptr->rcpblkflag == TRUE)
	{
		unblocked = dequeue(prptr->sendqueue);
		struct procent *prptrUnblocked = &proctab[unblocked];

		prptrUnblocked->sendblkflag = FALSE; // msg is empty so turn to false
		prptr->prmsg = prptrUnblocked->sendblkmsg;

		prptr->prhasmsg = TRUE;
		//kprintf("\nRECEIVE2\n");

		//if the queue is empty, set rcpblkflag to false
		if (isempty(prptr->sendqueue))
			prptr->rcpblkflag = FALSE;

		//get ready
		ready(unblocked);
	}

	restore(mask);
	return msg;
}
