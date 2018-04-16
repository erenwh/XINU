#include <xinu.h>

/* childwait() returns the pid of a child process that has terminated to its parent process */
pid32 childwait(void)
{
    intmask mask;
    mask = disable();
    struct procent *prptr = &proctab[currpid];

    //TODO implement childwait
    return 0;
}