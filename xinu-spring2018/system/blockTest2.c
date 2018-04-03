#include <xinu.h>

void blockTest2()
{
    pid32 rec1 = create(messageRec, 1024, 20, "reciever", 1, 2);
    pid32 send1 = create(messageSend, 1024, 20, "sender", 2, rec1, 'B');
    pid32 send2 = create(messageSend, 1024, 20, "sender", 2, rec1, 'C');
    pid32 send3 = create(messageSend, 1024, 20, "sender", 2, rec1, 'D');
    pid32 send4 = create(messageSend, 1024, 20, "sender", 2, rec1, 'E');
    resume(send1);
    sleepms(1000);
    resume(send2);
    sleepms(1000);
    resume(send3);
    sleepms(1000);
    resume(send4);
    sleepms(1000);

    resume(rec1);
    sleepms(5000);
    kill(rec1);
    /*resume(rec1);
    sleepms(1000);
    resume(rec1);
    sleepms(1000);
    resume(rec1);
    sleepms(1000);*/
}