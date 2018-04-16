/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

#define PART3
//#define PART4

process
main(void)
{
	// print my info
	kprintf("\n(Wang, Han)\n");
	kprintf("\nwang2786\n");
#ifdef PART3
	kprintf("\n***PART3: Test for XSIGRCV***\n");
	recv_test1();
	kprintf("\n***Waiting PART3: Test for XSIGRCV to Finish***\n");
	sleepms(2000);
	kprintf("\n***PART3: Test for XSIGCHL***\n");
	sleepms(500);
	child_test1();
	sleepms(5000);
	kprintf("\n***Waiting PART3: Test for XSIGCHL to Finish***\n");
#endif

#ifdef PART4
	kprintf("\n***PART2: Test 1 sending from multiple process\n");
	asyTest1();
	kprintf("\n***Waiting PART2: Test 1 to Finish***\n");
	sleepms(4000);
	kprintf("\n***PART2: Test 2 sending from same process with multiple message using sendblk()***\n");
	asyTest2();
	kprintf("\n***Waiting PART2: Test 2 to Finish***\n");
	sleepms(2000);
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
