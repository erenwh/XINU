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

    //kprintf("cbreg\n");

    restore(mask); // restore interrupts
    return OK;
}