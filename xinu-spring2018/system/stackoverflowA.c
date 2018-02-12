/**
  *attacker
  */
#include <xinu.h>
void stackoverflowA(void) {
    kprintf("Hacker(pid: %d) is starting\n", currpid);
    unsigned long *vic_sp, *vic_bp;
    vic_sp = (unsigned long *) proctab[victim_pid].prstkptr;
    vic_bp = vic_sp + 2; // move up 2
    vic_bp = *bp;
    vic_bp = *bp;

}
