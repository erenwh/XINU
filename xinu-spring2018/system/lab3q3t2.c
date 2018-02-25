#include <xinu.h>

void lab3q3t2() {
        // Spawning processes with different priority
        kprintf("\nTest3.2: Different Priority\n"); 
        resume(create(test2, 1024, 25, "test1.2-prio 25",0));
        resume(create(test2, 1024, 26, "test2.2-prio 26",0));
        resume(create(test2, 1024, 27, "test3.2-prio 27",0));
        resume(create(test2, 1024, 28, "test4.2-prio 28",0));
        sleep(10);
 //       printprocess();
        kprintf("\nEnd of Test3.2\n");
}
