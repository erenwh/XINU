/* receive.c - receive */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  receive  -  Wait for a message and return the message to the caller
 *------------------------------------------------------------------------
 */
umsg32 receive(void)
{
    intmask mask;          /* Saved interrupt mask		*/
    struct procent *prptr; /* Ptr to process' table entry	*/
    struct procent *prptr_send;
    umsg32 msg;            /* Message to return		*/
    pid32 sender;

    mask = disable();
    prptr = &proctab[currpid];
    if (prptr->prhasmsg == FALSE)
    {
        if (!isempty(prptr->sendqueue)) {// if the queue is empty
            sender = dequeue(prptr->sendqueue);
            prptr_send = &proctab[sender];
            send->sendblkflag == FLASE;
            prptr->prhasmsg = TRUE;

            //see if more process waiting
            if (isempty(prptr->sendqueue)) {
                prptr->rcpblkflag = FALSE;
            }
            prptr->prstate = PR_READY;
            insert(sender, readylist, prptr->prprio);
        }
        else {
            prptr->prstate = PR_RECV;
            resched(); /* Block until message arrives	*/
        }
    }
    msg = prptr->prmsg;      /* Retrieve message		*/
    prptr->prhasmsg = FALSE; /* Reset message flag		*/
    restore(mask);
    return msg;
}
