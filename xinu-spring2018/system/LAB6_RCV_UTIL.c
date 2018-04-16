#include <xinu.h>
umsg32 mbuf;

// Test for XSIGRCV
int recv_cb(void)
{
    mbuf = receive();
    kprintf("mbuf = %c\n", mbuf);
    return (OK);
}
void sigRec()
{
    if (sigcbreg(XSIGRCV, &recv_cb, 0) != OK)
    {
        kprintf("sigcb registration failed!\n");
    }

    while (TRUE)
    {
        sleepms(10);
        //kprintf("mbuf=%s\n", mbuf);
    }
    return;
}

void sigSend(pid32 pid, umsg32 msg)
{
    kprintf("Sender(PID:%d) is sending message('%c') to Reciever(pid:%d)\n", currpid, msg, pid);
    sendblk(pid, msg);
}

void recv_test1()
{
    pid32 sigRec1 = create(sigRec, 1024, 20, "sigRec1", 0, NULL);
    pid32 sigSend1 = create(sigSend, 1024, 20, "sigSend1", 2, sigRec1, 'A');
    pid32 sigSend2 = create(sigSend, 1024, 20, "sigSend2", 2, sigRec1, 'B');
    pid32 sigSend3 = create(sigSend, 1024, 20, "sigSend3", 2, sigRec1, 'C');
    resume(sigSend1);
    sleepms(500);
    resume(sigSend2);
    sleepms(500);
    resume(sigSend3);
    sleepms(500);

    resume(sigRec1);
    sleepms(2000);

    kill(sigRec1);
    kill(sigSend1);
    kill(sigSend2);
    kill(sigSend3);
}