/*  main.c  - main */
/*
#include <xinu.h>
#include <stdio.h>

process	main(void)
{
	kprintf("\nHello World!\n");
	kprintf("\nThis is Han Wang, PID: 0028451697, username:wang2786\n");
	kprintf("\nThis is my custom version of the XINU machine.\n");
	kprintf("\n...creating a shell\n");
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
*/
