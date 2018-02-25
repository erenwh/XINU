#include <xinu.h>
#include <test.h>
#define DEBUG
syscall getcputot(pid32 pid) {
    //look up the prcputot field in the process table entry

    int32 retval;
    intmask mask = disable();
    struct procent *curr = &proctab[pid];
    if (pid != currpid) {
        restore(mask);
        return SYSERR;
    }
    retval = curr->prcputot;

    restore(mask);
    return retval;
    
}
