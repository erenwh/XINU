#include <xinu.h>

void iotest()
{
    kprintf("Test for IO begins\n");
    resume(create(iobound, 1024, 50, "iobound_1", 0, NULL));
    resume(create(iobound, 1024, 50, "iobound_2", 0, NULL));
    resume(create(iobound, 1024, 50, "iobound_3", 0, NULL));
    resume(create(iobound, 1024, 50, "iobound_4", 0, NULL));
    resume(create(iobound, 1024, 50, "iobound_5", 0, NULL));
    receive();
    receive();
    receive();
    receive();
    receive();
}