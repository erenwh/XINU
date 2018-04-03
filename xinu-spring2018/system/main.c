/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

#define PART1
#define PART2

process main(void)
{
	// print my info
	kprintf("\n(Wang, Han)\n");
	kprintf("\nwang2786\n");
#ifdef PART1
	kprintf("\n***PART1: Test 1***\n");
	blockTest1();
	kprintf("\n***Waiting PART1: Test 1 to Finish***\n");
	sleepms(2000);
	kprintf("\n***PART1: Test 2***\n");
	blockTest2();
	kprintf("\n***Waiting PART1: Test 2 to Finish***\n");
	sleepms(2000);
#endif

#ifdef PART2
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
