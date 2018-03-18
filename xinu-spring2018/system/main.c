/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

process	main(void)
{
        // print my info
	kprintf("\n(Wang, Han)\n");
	kprintf("\nwang2786\n");
	recvclr();
	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));

	while (TRUE) {
		receive();
		sleepms(200);
		kprintf("\n\nMain process recreating shell\n\n");
		resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
	}
	return OK;
}
