#include <xinu.h>

void asyMessageSendMult(pid32 pid, umsg32 msg)
{
    umsg32 m = msg;
    kprintf("Sender(PID:%d) is sending message('%c') to Reciever(pid:%d)\n", currpid, m, pid);
    sendblk(pid, m);
    m++;
    kprintf("Sender(PID:%d) is sending message('%c') to Reciever(pid:%d)\n", currpid, m, pid);
    sendblk(pid, m);
    m++;
    kprintf("Sender(PID:%d) is sending message('%c') to Reciever(pid:%d)\n", currpid, m, pid);
    sendblk(pid, m);
}