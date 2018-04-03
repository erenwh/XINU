#include <xinu.h>

void asyTest1()
{
    pid32 asyRec1 = create(asyMessageRec, 1024, 20, "asyRec1", 0, NULL);
    pid32 asySend1 = create(asyMessageSend, 1024, 20, "asySend1", 2, asyRec1, 'Z');
    pid32 asySend2 = create(asyMessageSend, 1024, 20, "asySend2", 2, asyRec1, 'Y');

    pid32 regSend1 = create(messageSend, 1024, 20, "regSend1", 2, asyRec1, 'P');

    resume(asySend1);
    sleepms(1000);
    resume(asySend2);
    sleepms(1000);

    resume(regSend1);
    sleepms(1000);

    resume(asyRec1);
    sleepms(1000);

    kill(asyRec1);
}