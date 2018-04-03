#include <xinu.h>

void asyTest2()
{
    pid32 asyRec1 = create(asyMessageRec, 1024, 20, "asyRec1", 0, NULL);
    pid32 asySend1 = create(asyMessageSendMult, 1024, 30, "asySend1", 2, asyRec1, '1');

    resume(asySend1);
    sleepms(1000);

    resume(asyRec1);
    sleepms(1000);

    kill(asyRec1);
}