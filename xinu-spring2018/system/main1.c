/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

process	main1(void)
{
	recvclr();
	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));
	resume(create(onandon, 2048, 30, "onandon", 0, CONSOLE));

	/* Wait for shell to exit and recreate it */

	while (TRUE) {
		onandon();
		sleep(14);

	}
	return OK;
}
