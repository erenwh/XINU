#include <xinu.h>

void mixedtest()
{
    kprintf("Test for MIXED begins\n");
    resume(create(iobound, 1024, 20, "iobound_1", 0, NULL));
    resume(create(iobound, 1024, 20, "iobound_2", 0, NULL));
    resume(create(iobound, 1024, 20, "iobound_3", 0, NULL));
    resume(create(cpubound, 1024, 20, "cpubound_1", 0, NULL));
    resume(create(cpubound, 1024, 20, "cpubound_2", 0, NULL));
    resume(create(cpubound, 1024, 20, "cpubound_3", 0, NULL));
    receive();
    receive();
    receive();
    receive();
    receive();
    receive();
}