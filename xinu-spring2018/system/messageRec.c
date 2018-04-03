#include <xinu.h>

void messageRec(int n)
{
    umsg32 msg;
    while (1)
    {
        sleepms(100);
        msg = receive();
    }
}