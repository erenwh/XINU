/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

process	main1(void)
{
	kprintf("\n(Wang, Han)\n");
	kprintf("\nwang2786\n");
	recvclr();
	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));
	sleep(1);
	pid32 pid = create(onandon, 2048, 30, "onandon", 0, CONSOLE));
	resume(pid);
	sleep(14);
	kill(pid);
	recvclr();

	/* Wait for shell to exit and recreate it */

	while (TRUE) {
		receive();
		sleepms(200);
		kprintf("\n\nMain process recreating shell\n\n");
		resume(create(shell, 4096, 20, "shell", 1, CONSOLE));

	}
	return OK;
}
