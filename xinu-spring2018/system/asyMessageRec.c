#include <xinu.h>

umsg32 mbuf;
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
        intmask mask;
        mask = disable(); // disable interrupts
        kprintf("mbuf = %c\n", mbuf);
        restore(mask); // restore interrupts
    }
}
