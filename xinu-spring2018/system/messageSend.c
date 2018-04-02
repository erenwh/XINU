#include <xinu.h>

void messageSend(pid32 pid, char msg)
{
    kprintf("Sender(PID:%d) is sending message('%c') to Reciever(pid:%d)\n", currpid, msg, pid);
    sendblk(pid, msg);
}