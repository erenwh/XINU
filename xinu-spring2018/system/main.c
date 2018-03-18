/*  main.c  - main */

#include <xinu.h>


//#define Q3_T1
//#define Q3_T2
//#define Q4_5CPU
//#define Q4_5IO
#define Q4_3CPU3IO

process	main(void)
{
    // print my info
    kprintf("\n(Wang, Han)\n");
    kprintf("\nwang2786\n");
    kprintf("\n\n");
#ifdef Q3_T1
    lab3q3t1();
#endif

#ifdef Q3_T2
    lab3q3t2();
#endif
    
#ifdef Q4_5CPU
    kprintf("Test for Q4_5CPU begins\n");
    resume(create(cpubound,1024, 50,"cpubound_1",0,NULL));
    resume(create(cpubound,1024, 50,"cpubound_2",0,NULL));
    resume(create(cpubound,1024, 50,"cpubound_3",0,NULL));
    resume(create(cpubound,1024, 50,"cpubound_4",0,NULL));
    resume(create(cpubound,1024, 50,"cpubound_5",0,NULL));
    receive();receive();receive();receive();receive();
#endif

#ifdef Q4_5IO
    kprintf("Test for Q4_5IO begins\n");
    resume(create(iobound,1024, 50,"iobound_1",0,NULL));
    resume(create(iobound,1024, 50,"iobound_2",0,NULL));
    resume(create(iobound,1024, 50,"iobound_3",0,NULL));
    resume(create(iobound,1024, 50,"iobound_4",0,NULL));
    resume(create(iobound,1024, 50,"iobound_5",0,NULL));
    receive();receive();receive();receive();receive();
#endif

#ifdef Q4_3CPU3IO
    kprintf("Test for Q4_3CPU3IO begins\n");
    resume(create(cpubound,1024, 50,"cpubound_1",0,NULL));
    resume(create(cpubound,1024, 50,"cpubound_2",0,NULL));
    resume(create(cpubound,1024, 50,"cpubound_3",0,NULL));
    resume(create(iobound,1024, 50,"iobound_1",0,NULL));
    resume(create(iobound,1024, 50,"iobound_2",0,NULL));
    resume(create(iobound,1024, 50,"iobound_3",0,NULL));
    receive();receive();receive();receive();receive();receive();
#endif

    /*
     recvclr();
     resume(create(shell, 8192, 50, "shell", 1, CONSOLE));
     
     
     while (TRUE) {
     receive();
     sleepms(200);
     kprintf("\n\nMain process recreating shell\n\n");
     resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
     }*/
    return OK;
}
