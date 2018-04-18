#include <xinu.h>
syscall sigcbunreg(uint16 ssig)
{
    intmask mask;
    mask = disable(); // disable interrupts

    struct procent *prptr = &proctab[currpid];

    if (ssig == XSIGRCV) // asynchronous IPC with callback
    {

        prptr->prhascb = FALSE;
        prptr->fptr = NULL;
        restore(mask); //restore interrupts and get ready to return
        return OK;
    }
    else if (ssig == XSIGCHL) // parent-child signal
    {

        prptr->prhascb1 = FALSE;
        prptr->fptr1 = NULL;
        restore(mask);
        return OK;
    }
    else if (ssig == XSIGXTM) // XSIGXTM
    {

        prptr->prhascb2 = FALSE;
        prptr->fptr2 = NULL;
        prptr->walltime = 0;

        restore(mask);
        return OK;
    }
    else
    {
        return SYSERR;
    }
}