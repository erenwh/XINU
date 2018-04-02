#include <xinu.h>

void asyMessageRec()
{
    if (cbreg(&mrecv_cb) != OK)
    {
        kprintf("cb registration failed!\n");
    }

    while (1)
    {
        mrecv_cb();
    }
}