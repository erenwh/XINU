#include <xinu.h>

/**
 * 
 * If receiver's buffer is full, sendblk() blocks indefinitely,
 * Upon blocking, XINU's upper half context switches out the 
 * sending process and puts it into a waiting state SNDBLK.
 */

syscall sendblk(
    pid32 pid,
    umsg32 msg)
{
    intmask mask;                  /* Saved interrupt mask		*/
    struct procent *prptrReceiver; /* Ptr to receiver process' table entry	*/
    struct procent *prptrSender;   /* Ptr to sender process' table entry	*/
    //struct procent *prptr_send;

    /* interrupt */
    mask = disable();
    if (isbadpid(pid))
    {
        restore(mask);
        return SYSERR;
    }

    prptrReceiver = &proctab[pid];
    prptrSender = &proctab[currpid];

    if ((prptrReceiver->prstate == PR_FREE))
    {
        restore(mask);
        return SYSERR;
    }

    if (prptrReceiver->prhasmsg == TRUE)
    { // if there is a msg to handle
        if (prptrReceiver->sendqueue == NULL)
        {
            prptrReceiver->sendqueue = newqueue();
            kprintf("\nMaking a queue for msg: %c\n", msg);
        }
        prptrSender->sendblkflag = TRUE;  // change the sendblkflag
        prptrSender->sendblkmsg = msg;    // store the message
        prptrSender->sendblkrcp = pid;    // set recipient
        prptrSender->prstate = PR_SNDBLK; // change the state to sndblk

        kprintf("\nEnqueuing msg(%c)\n", msg);
        enqueue(currpid, prptrReceiver->sendqueue);

        prptrReceiver->rcpblkflag = TRUE;

       
        resched();
        /*if (prptrReceiver->prhasmsg == TRUE) 
        {// process woke up from sleep

        }*/
    }

    //kprintf("send\n");
    prptrReceiver->prmsg = msg;     //Deliver message
    prptrReceiver->prhasmsg = TRUE; // Indicate message is waiting

    if (prptrReceiver->prstate == PR_RECV)
    {
        ready(pid);
    }
    else if (prptrReceiver->prstate == PR_RECTIM)
    {
        unsleep(pid);
        ready(pid);
    }
    restore(mask); /* Restore interrupts */
    return OK;
}