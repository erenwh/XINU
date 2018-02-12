/**
  *victim
  */
#include <xinu.h>
void stackoverflowB(void) {
    char b = 'B';
    putc(stdout,b);
    sleepms(1500);
    kprintf("\nVictim(pid:%d) finished sleeping\n",currpid);
    putc(stdout,b);
}
