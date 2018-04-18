#include <xinu.h>

// Test for XSGICHL
void child_test1(void)
{
    // creating parent process
    pid32 parent = create(parentapp, 1024, 20, "parentProcess", 0, NULL);
    resume(parent);
}

void child_test2(void)
{
    // creating parent process
    pid32 parent = create(parentapp, 1024, 20, "parentProcess", 0, NULL);
    resume(parent);
}

void parentapp(void)
{
    kprintf("parent(%d) is running\n", currpid);
    //create child process
    pid32 child1 = create(childapp, 1024, 20, "childrenProcess1", 0, NULL);
    resume(child1);
    //struct procent *prptr = &proctab[currpid];
    //kprintf("#ofchildren:%d\n", prptr->numChildren);
    /*
    pid32 child2 = create(childapp, 1024, 20, "childrenProcess2", 0, NULL);
    resume(child2);
    kprintf("#ofchildren:%d\n", prptr->numChildren);*/

    if (sigcbreg(XSIGCHL, &chl_cb, 0) != OK)
    {
        kprintf("sigcb registration failed!\n");
    }
    pid32 waitingchildPID = childwait(); // get the pid of child that is about to terminate
    kprintf("pid(%d): childwait return pid: %d", currpid, waitingchildPID);
    while (1)
    {
    }

    return;
}
void parentapp2(void)
{
    kprintf("parent(%d) is running\n", currpid);
    pid32 waitingchildPID1 = childwait();
    kprintf("pid(%d): childwait return pid: %d", currpid, waitingchildPID1);
    //create child process
    pid32 child1 = create(childapp, 1024, 20, "childrenProcess1", 0, NULL);
    resume(child1);
    pid32 waitingchildPID2 = childwait();
    kprintf("pid(%d): childwait return pid: %d", currpid, waitingchildPID2);
    pid32 waitingchildPID3 = childwait();
    kprintf("pid(%d): childwait return pid: %d", currpid, waitingchildPID3);
    //struct procent *prptr = &proctab[currpid];
    //kprintf("#ofchildren:%d\n", prptr->numChildren);
    /*
    pid32 child2 = create(childapp, 1024, 20, "childrenProcess2", 0, NULL);
    resume(child2);
    kprintf("#ofchildren:%d\n", prptr->numChildren);*/

    if (sigcbreg(XSIGCHL, &chl_cb, 0) != OK)
    {
        kprintf("sigcb registration failed!\n");
    }
    kprintf("pid(%d): childwait return pid: %d", currpid, waitingchildPID1);
    // get the pid of child that is about to terminate
    while (1)
    {
    }

    return;
}

void childapp(void)
{
    int delay = 5;
    while (delay > 0)
    {
        kprintf("child(%d) is running(%d)\n", currpid, delay);
        delay--;
        if (delay <= 0)
        {
            kprintf("child(%d) is finished\n", currpid);
            return;
        }
    }
}

int chl_cb()
{
    struct procent *pr = &proctab[currpid];

    struct procent *prptr = &proctab[pr->prparent];
    //kprintf("I am %s\n", prptr->prname);
    //kprintf("numChildren:%d\n", prptr->numChildren);
    prptr->numChildren--;
    prptr->prstate = PR_READY;
    //kprintf("numChildren:%d\n", prptr->numChildren);
    kprintf("This is Callback function chl_cb, a child process is about to end\n");
    return (OK);
}