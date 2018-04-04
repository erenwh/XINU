#include <xinu.h>

void messageRec(int n)
{
    umsg32 msg;
    while (1)
    {
        sleepms(100);
        msg = receive();
        kprintf("\n(PID:%d):Message recieved: %c\n", currpid, msg);
    }
}