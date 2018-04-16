#include <xinu.h>

void jumpcb()
{
    if (proctab[currpid].prhasmsg == TRUE)
    {
        if (proctab[currpid].prhascb == TRUE &&
            proctab[currpid].fptr != NULL)
        {
            proctab[currpid].fptr();
        }
    }
}
