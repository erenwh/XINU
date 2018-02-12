/*  main.c  - main */

#include <xinu.h>

extern void printprocess(void);
extern void randomprocess(void);

extern long host2net(long);
extern long host2netca(long);
extern long host2neta(long);

extern void prnsegadd(void);

extern void stackinfo(void);
extern int appl1(void);
extern int fun1(int,int);

extern void stackoverflowA(void);
extern void stackoverflowB(void);


void test() {
    kprintf("****host2net test START****\n");
    long original = 0x12345678;
    long test1 = host2net(original);
    long test2 = host2netca(original);
    long test3 = host2neta(original);
    kprintf("host2net.S(%x) = %x\n", original, test1);
    kprintf("host2netca.c(%x) = %x\n", original, test2);
    kprintf("host2neta.c(%x) = %x\n", original, test3);
    kprintf("result should be 78563412\n");
    kprintf("****host2net test END****\n");
    kprintf("\n\n");

}


process	main(void)
{
        // print my info
	kprintf("\n(Wang, Han)\n");
	kprintf("\nwang2786\n");
        kprintf("\n\n");

        // 3
        test();//host2net tests
        sleepms(300);

        // 4.1
        kprintf("**** 4.1 Segament Address****\n");
        prnsegadd();
        kprintf("\n\n");
        sleepms(300);
        kprintf("**** 4.1 Segament Address END****\n\n");


        // 4.2
        kprintf("****app vs fun****\n");

        kprintf("1.main process before appl1():\n");
        stackinfo();

        int app1_pid;
        app1_pid = create(appl1, INITSTK, INITPRIO, "appl1", 0, NULL);
        
        resume(app1_pid);
        kprintf("\n\n");
        sleepms(300);
        kprintf("****app vs fun END****\n\n");
        
        // 4.4 Bouns
        kprintf("******bonus GoCreat**********\n");
        kprintf("before gocreate\n");
        printprocess();
        sleepms(500);

        kprintf("\nrandom process is a program that just a infinte loop that sleeps for 2 seconds.\n\n");
        gocreate(randomprocess, INITSTK, 5, "randomprocess", 0, NULL);
        sleepms(500);

        kprintf("after gocreate\n");
        printprocess();


        sleep(2); // for 4.4 to finish
        kprintf("******bonus GoCreat END**********\n\n");

        // 4.3
        kprintf("*****Memory Smashing*****\n");

        // Spawn Hacker first with low priority
        //attack 2048 byte prio:10
        resume(create(stackoverflowA, 2048, 10, "hacker", 0));

        //victim 2048 byte prio:15
        int victim_pid = create(stackoverflowB, 2048, 15, "victim",0);
        resume(victim_pid);
        sleep(3);

        sleep(5);
        kprintf("main: hello?\n");

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
