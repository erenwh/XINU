/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

#define PART3
//#define PART4

int recv_cb(void)
{
	mbuf = receive();
	kprintf("cb(pid: %d): mbuf = %s\n", currpid, mbuf);
	return (OK);
}
void sigRec()
{
	if (sigcbreg(XSIGRCV, &recv_cb, 0) != OK)
	{
		kprintf("sigcb registration failed!\n");
		return 1;
	}

	while (TRUE)
	{
		sleepms(10);
	}
	return;
}

void sigSend(pid32 pid, umsg32 msg)
{
	kprintf("Sender(PID:%d) is sending message('%c') to Reciever(pid:%d)\n", currpid, msg, pid);
	sendblk(pid, msg);
}

void recv_test1()
{
	pid32 sigRec1 = create(sigRec, 1024, 20, "sigRec1", 0, NULL);
	pid32 sigSend1 = create(sigSend, 1024, 20, "sigSend1", 2, sigRec1, 'A');
	pid32 sigSend2 = create(sigSend, 1024, 20, "sigSend2", 2, sigRec1, 'B');
	pid32 sigSend3 = create(sigSend, 1024, 20, "sigSend3", 2, sigRec1, 'C');
	resume(sigsend1);
	sleepms(500);
	resume(sigsend2);
	sleepms(500);
	resume(sigsend3);
	sleepms(500);

	resume(sigRec1);
	sleepms(500);

	kill(sigRec1);
}

process
main(void)
{
	// print my info
	kprintf("\n(Wang, Han)\n");
	kprintf("\nwang2786\n");
#ifdef PART3
	kprintf("\n***PART3: Test 1***\n");
	recv_test1;
	kprintf("\n***Waiting PART3: Test 1 to Finish***\n");
	sleepms(2000);
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
