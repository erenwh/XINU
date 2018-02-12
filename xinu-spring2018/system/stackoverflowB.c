/**
  *victim
  */
#include <xinu.h>
void stackoverflowB(void) {
    char b = 'B';
    putc(CONSOLE,b);
    kprintf("\nVictim(pid:%d) is going to sleep\n", currpid);
    sleepms(1500);
    kprintf("\nVictim(pid:%d) finished sleeping\n",currpid);
    putc(CONSOLE,b);
}
