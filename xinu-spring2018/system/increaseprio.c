#include <xinu.h>

void IncreasePrio() {
    int16 curr;
    curr = firstid(readylist);
    while (curr != queuetail(readylist)) {
        if (curr != 0) { //null process stays 0
            queuetab[curr].qkey += 5;
        }
        curr = queuetab[curr].qnext;
    }

            
}
