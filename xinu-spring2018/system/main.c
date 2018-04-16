/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

#define PART3
//#define PART4

umsg32 mbuf;

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

// Test for XSIGRCV
int recv_cb(void)
{
	mbuf = receive();
	kprintf("mbuf = %c\n", mbuf);
	return (OK);
}
void sigRec()
{
	if (sigcbreg(XSIGRCV, &recv_cb, 0) != OK)
	{
		kprintf("sigcb registration failed!\n");
	}

	while (TRUE)
	{
		sleepms(10);
		//kprintf("mbuf=%s\n", mbuf);
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
	resume(sigSend1);
	sleepms(500);
	resume(sigSend2);
	sleepms(500);
	resume(sigSend3);
	sleepms(500);

	resume(sigRec1);
	sleepms(2000);

	kill(sigRec1);
	kill(sigSend1);
	kill(sigSend2);
	kill(sigSend3);
}

// Test for XSGICHL
void child_test1(void)
{
	// creating parent process
	pid32 parent = create(parentapp, 1024, 20, "parentProcess", 0, NULL);
	resume(parent);

	if (sigcbreg(XSIGCHL, &chl_cb, 0) != OK)
	{
		kprintf("sigcb registration failed!\n");
	}

	pid32 child = childwait();// get the pid of child that is about to terminate
}

void parentapp(void)
{
	kprintf("parent(%d) is running\n", currpid);
	//create child process
	pid32 child1 = create(childapp, 1024, 20, "childrenProcess1", 0, NULL);
	resume(child1);
}

void childapp(void)
{
	int delay = 5;
	while (delay > 0)
	{
		kprintf("child(%d) is running(%d)\n", currpid, delay);
		delay--;
		if (delay <= 0)
		{
			kprintf("child(%d) is finished\n", currpid);
			return;
		}
	}
}

void chl_cb() {

}
