#include <xinu.h>

/**
 * 
 * If receiver's buffer is full, sendblk() blocks indefinitely,
 * Upon blocking, XINU's upper half context switches out the 
 * sending process and puts it into a waiting state SNDBLK.
 */


syscall sendblk(
    pid32 pid,
    umsg32 msg
) {
    intmask mask;          /* Saved interrupt mask		*/
    struct procent *prptr; /* Ptr to process' table entry	*/
    struct procent *prptr_send;
 
    /* interrupt */
    mask = disable();
    if (isbadpid(pid))
    {
        restore(mask);
        return SYSERR;
    }

    prptr = &proctab[pid];
    prptr_send = &proctab[currpid];

    if ((prptr->prstate == PR_FREE))
    {
        restore(mask);
        return SYSERR;
    }

    if (prptr->prhasmsg) { // handle blocking message
        prptr_send->sendblkmsg = msg;
        prptr_send->sendblkflag = TRUE;
        if (prptr_send->rcpblkflag == FALSE) { // if there is no process waiting
            insert(currpid, sleepq);//insertd?
        }
        prptr_send->prstate == PR_SNDBLK;
        enqueue(currpid, prptr->sendqueue);
        resched();
    } else {
        prptr->prmsg = msg;     /* Deliver message		*/
        prptr->prhasmsg = TRUE; /* Indicate message is waiting	*/
    }

    if (prptr->prstate == PR_RECV)
    {
        ready(pid);
    }
    else if (prptr->prstate == PR_RECTIM)
    {
        unsleep(pid);
        ready(pid);
    }
    restore(mask); /* Restore interrupts */
    return OK;
}