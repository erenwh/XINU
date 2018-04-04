#include <xinu.h>

void jumpcb()
{
    if (proctab[currpid].prhascb == TRUE &&
        proctab[currpid].fptr != NULL)
    {
        proctab[currpid].fptr();
//        proctab[currpid].prhascb = FALSE;
//        proctab[currpid].fptr = NULL;
    }
}
