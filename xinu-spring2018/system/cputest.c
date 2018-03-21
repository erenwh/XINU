#include <xinu.h>

void cputest()
{
    kprintf("Test for CPU begins\n");
    resume(create(cpubound, 1024, 50, "cpubound_1", 0, NULL));
    resume(create(cpubound, 1024, 50, "cpubound_2", 0, NULL));
    resume(create(cpubound, 1024, 50, "cpubound_3", 0, NULL));
    resume(create(cpubound, 1024, 50, "cpubound_4", 0, NULL));
    resume(create(cpubound, 1024, 50, "cpubound_5", 0, NULL));
    receive();
    receive();
    receive();
    receive();
    receive();
}