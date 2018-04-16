#include <xinu.h>

syscall sigcbreg(uint16 ssig, int (*fnp)(void), uint32 tmarg)
{
    // TODO implement new cbreg
    intmask mask;
    mask = disable(); // disable interrupts

    //if function pointer is null
    if (fnp == NULL)
    {
        restore(mask);
        return SYSERR;
    }

    if (ssig == XSIGRCV) // asynchronous IPC with callback
    {
        struct procent *prptr = &proctab[currpid];
        prptr->prhascb = TRUE;
        prptr->fptr = fnp;
        restore(mask); //restore interrupts and get ready to return
        return OK;
    }
    else if (ssig == XSIGCHL) // parent-child signal
    {
        struct procent *prptr = &proctab[currpid];
        prptr->prhascb1 = TRUE;
        prptr->fptr1 = fnp;
        restore(mask);
        return OK;
    }
    else // XSIGXTM
    {
        struct procent *prptr = &proctab[currpid];
        prptr->prhascb2 = TRUE;
        prptr->fptr2 = fnp;
        restore(mask);
        return OK;
    }

    //kprintf("cbreg\n");

    restore(mask); // restore interrupts
    return OK;
}