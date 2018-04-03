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
        return SYSERR; //When a process tries to register a second callback function, cbreg() should return with an error.
    }
    //kprintf("cbreg\n");

    restore(mask); // restore interrupts
    return OK;
}