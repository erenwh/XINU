#include <xinu.h>

void messageRec(int n)
{
    umsg32 msg;
    while (1)
    {
        msg = receive();
        kprintf("(PID:%d):Message recieved: %c\n", currpid, msg);
    }
}