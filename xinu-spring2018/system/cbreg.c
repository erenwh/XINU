#include <xinu.h>

syscall cbreg(int (*fnp)(void))
{

    intmask mask;
    mask = disable(); // disable interrupts
    if (fnp == NULL)
    {
        restore(mask);
        return SYSERR;
    }

    struct procent *prptr = &proctab[currpid];
    prptr->prhascb = TRUE;
    prptr->fptr = fnp;
    //kprintf("cbreg\n");

    restore(mask); // restore interrupts
    return OK;
}