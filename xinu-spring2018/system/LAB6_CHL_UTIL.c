#include <xinu.h>

// Test for XSGICHL
void child_test1(void)
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

    if (sigcbreg(XSIGCHL, &chl_cb, 0) != OK)
    {
        kprintf("sigcb registration failed!\n");
    }

    pid32 child = childwait(); // get the pid of child that is about to terminate

    while (1)
    {
        sleepms(10);
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
    kprintf("chl_cb\n");
    return 1;
}