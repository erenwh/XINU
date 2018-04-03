#include <xinu.h>

void blockTest1()
{
    pid32 rec = create(messageRec, 1024, 20, "reciever", 1, 2);
    pid32 send = create(messageSend, 1024, 20, "sender", 2, rec, 'A');
    resume(send);
    sleepms(1000);

    resume(rec);
    sleepms(1000);
    kill(rec);
}