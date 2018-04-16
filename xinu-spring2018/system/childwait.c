#include <xinu.h>

/* childwait() returns the pid of a child process that has terminated to its parent process */
pid32 childwait(void)
{
    intmask mask;
    mask = disable();
    struct procent *prptr = &proctab[currpid];

    pid32 child = prptr->returnChildPid;
    prptr->prstate = PR_CHLDWAIT;

    if (child == -1) // no child is about to end
    {
        kprintf("No child is ending\n");
        restore(mask);
        return SYSERR;
    }
    else // a child is terminated
    {
        //prptr->prstate = PR_READY;
        kprintf("I got a child is about to end!\n");
    }
    resched();
    restore(mask);

    //TODO implement childwait
    return child;
}