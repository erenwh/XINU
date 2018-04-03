#include <xinu.h>

void asyMessageRec()
{
    if (cbreg(&mrecv_cb) != OK)
    {
        kprintf("cb registration failed!\n");
    }

    while (1)
    {
        sleepms(300);
        //mrecv_cb();
        kprintf("mbuf is '%c'\n", mbuf);
    }
}