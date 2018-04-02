#include <xinu.h>

void asyTest1()
{
    pid32 asyRec1 = create(asyMessageRec, 1024, 20, "asyRec1", 0, NULL);
    pid32 asySend1 = create(asyMessageSend, 1024, 20, "asySend1", 2, asyRec1, 'Z');

    resume(asySend1);
    sleepms(1000);

    resume(asyRec1);

    if (mbuf == 'Z')
    {
        kprintf("asyTest PASSED!\n");
    }
    else
    {
        kprintf("asyTest FAILED!\n");
    }
}