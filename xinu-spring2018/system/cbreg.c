#include <xinu.h>

syscall cbreg(int (*fnp)(void))
{
    intmask mask;
    mask = disable(); // disable interrupts

    struct procent *prptr = &proctab[currpid];
    if (prptr->prhascb == FALSE)
    {
        prptr->prhascb = TRUE;
        prptr->fptr = fnp;
    }
    else
    {
        return SYSERR;
    }
    //kprintf("cbreg\n");

    restore(mask); // restore interrupts
    return OK;
}