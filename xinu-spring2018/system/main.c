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
	kprintf("\n***PART1: Test 2***\n");
	blockTest2();
#endif

#ifdef PART2

	kprintf("\n***PART1: Test 1***\n");
	asyTest1();
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
