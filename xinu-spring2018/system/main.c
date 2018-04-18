/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

//#define PART3_1
#define PART3_2
//#define PART3_3
//#define PART4

//#define DEBUG
process
main(void)
{
	// print my info
	kprintf("\n(Wang, Han)\n");
	kprintf("\nwang2786\n");
#ifdef PART3_1
	kprintf("\n***PART3: Test for XSIGRCV***\n");
	recv_test1();
	kprintf("\n***Waiting PART3: Test for XSIGRCV to Finish***\n");
	sleepms(2000);
#endif
#ifdef PART3_2
	kprintf("\n***PART3: Test for XSIGCHL***\n");
	sleepms(500);
	child_test1();
	sleepms(5000);
	kprintf("\n***Waiting PART3: Test for XSIGCHL to Finish***\n");
#endif
#ifdef PART3_3
	kprintf("\n***PART3: Test for XSIGXTM***\n");
	sleepms(500);
	xtm_test1();
	sleepms(5000);
	kprintf("\n***Waiting PART3: Test for XSIGXTM to Finish***\n");

#endif

#ifdef PART4
	kprintf("\n***PART2: Test 1 Memory Garbage Collection \n");
	resume(create(mgcTest, 1024, 20, "mgcTest", 0));
	kprintf("MEMLIST(BEFORE): %d\n", memlist.mlength);
	mgcTest(void);
	kprintf("MEMLIST(AFTER): %d\n", memlist.mlength);
	sleep(1000);
	kprintf("MEMLIST(AFTER): %d\n", memlist.mlength);
	sleep(1000);
	kprintf("\n***Waiting PART2: Test 1 to Finish***\n");
	sleepms(4000);

#endif

	/*recvclr();
	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));

	while (TRUE) {
		receive();
		sleepms(200);
		kprintf("\n\nMain process recreating shell\n\n");
		resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
	}*/
	kprintf("\n\nYou reached the end of the Main().\n\n");
	return OK;
}
