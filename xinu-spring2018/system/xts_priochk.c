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
        if (!isempty(xts_arr[i]))
        {
            return i;
        }
    }
    return -1;
}

void printMFQ()
{
    for (int i = 59; i >= 0; i--)
    {
        if (!isempty(xts_arr[i]))
        {
            kprintf("Non-Empty Queue at Level %d \n ", i);
            printQueue(xts_arr[i]);
        }
    }
}
