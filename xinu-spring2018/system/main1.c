#include <xinu.h>
#include <stdio.h>

process	main(void)
{
        // print my info
	kprintf("\n(Wang, Han)\n");
	kprintf("\nwang2786\n");
	recvclr();//clear incoming msg and return msg if thers one waiting
	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));//create AND resume shell process
	sleep(1);//sleep 1 second for creating onandon process, avoid conflect
	pid32 pid = create(onandon, 2048, 30, "onandon", 0, CONSOLE);//create onandon process using 2048 and 30, store the pid for further use
	resume(pid);//resume the created process = run process
	sleep(14);// sleep for 14 secs
	kill(pid);// terminate onandon process
	recvclr();//clear incoming msg and return if there's one waiting


	while (TRUE) {
		receive();
		sleepms(200);
		kprintf("\n\nMain process recreating shell\n\n");
		resume(create(shell, 4096, 20, "shell", 1, CONSOLE));

	}
	return OK;
}
