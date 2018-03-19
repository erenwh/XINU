/**
  *attacker
  */
#include <xinu.h>
int plusone(int x) {
    x++;
//    kprintf("x: %d\n", x); //uncomment this line will spell out exception 13 indicating currpid5(victim is vaolated)
    //recursive
    if (x > 10000) return x;
    else return plusone(x);
}
void stackoverflowA(void) {
    kprintf("Hacker(pid: %d) is starting\n", currpid);
    int x = 0;
    plusone(x);
    //kprintf("hacker: x = %d\n", x);
}




