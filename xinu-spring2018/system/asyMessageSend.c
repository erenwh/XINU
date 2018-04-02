#include <xinu.h>

void asyMessageSend(pid32 pid, umsg32 msg)
{
    kprintf("Sender(PID:%d) is sending message('%c') to Reciever(pid:%d)\n", currpid, msg, pid);
    send(pid, msg);
}