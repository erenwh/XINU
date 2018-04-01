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

    prptr = &proctab[pid];
    prptr_send = &proctab[currpid];

    /* interrupt */
    mask = disable();
    if (isbadpid(pid))
    {
        restore(mask);
        return SYSERR;
    }
    if ((prptr->prstate == PR_FREE))
    {
        restore(mask);
        return SYSERR;
    }

    if (prptr->prhasmsg) {
        prptr_send->sendblkmsg = msg;
        prptr_send->sendblkflag = TRUE;
        
    }
}