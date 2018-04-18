#include <xinu.h>
#define DEBUG
/* childwait() returns the pid of a child process that has terminated to its parent process */
pid32 childwait(void)
{
    intmask mask;
    mask = disable();
    struct procent *prptr = &proctab[currpid];

    kprintf("numchildren:%d, returnchildpid:%d\n", prptr->numChildren, prptr->returnChildPid);
    // if there is no child and returnChildpid = -1
    if (prptr->numChildren == 0 && prptr->returnChildPid == -1)
    {
        //no process is running
        kprintf("DEBUG:childwait 1\n");
        return SYSERR;
    }
    else if (prptr->numChildren == 0 && prptr->returnChildPid != -1)
    {
        //if there is no child and return childpid is not -1
        kprintf("DEBUG:childwait 2\n");
        prptr->returnChildPid = -1;
        return prptr->returnChildPid;
    }
    else if (prptr->numChildren != 0 && prptr->returnChildPid != -1)
    {
        // if there is a child and return pid is not default
        kprintf("DEBUG:childwait 3\n");
        return prptr->returnChildPid;
    }
    else if (prptr->numChildren != 0 && prptr->returnChildPid == -1)
    {
        // normal case, have a child running, havent set before
        kprintf("DEBUG:childwait 4\n");
        prptr->prstate = PR_CHLDWAIT;
        resched();
    }
    else
    {
        kprintf("DEBUG:childwait 5\n");
    }

    restore(mask);

    //TODO implement childwait
    return prptr->returnChildPid;
}