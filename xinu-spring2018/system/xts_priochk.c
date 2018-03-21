/* xts_priochk.c  -  xts_priochk */

#include <xinu.h>

/**
 * 
 * returns the highest priority of (ready) processes in xts_ready[]. 
 * xts_priochk() is used by the scheduler resched() when determining 
 * if the current process should continue to run or not.
 * 
 */

pri16 xts_priochk(void)
{
    for (int i = 59; i >= 0; i--)
    {
        if (xts_ready[i].status == 1)
        {
            return i;
        }
    }
    return -1;
}
