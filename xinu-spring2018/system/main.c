/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

//#define PART3_1
//#define PART3_2
//#define PART3_3
//#define PART3_4
#define PART4

//#define DEBUG
process
main(void)
{
	// print my info
	kprintf("\n(Wang, Han)\n");
	kprintf("\nwang2786\n");
#ifdef PART3_1
	kprintf("\n***PART3: Test for XSIGRCV***\n");
	recv_test1();
	kprintf("\n***Waiting PART3: Test for XSIGRCV to Finish***\n");
	sleepms(2000);
#endif
#ifdef PART3_2
	kprintf("\n***PART3: Test1 for XSIGCHL***\n");
	sleepms(500);
	child_test1();
	sleepms(5000);
	//kprintf("\n***PART3: Test2 for XSIGCHL***\n");
	//child_test2();
	//sleepms(5000);
	kprintf("\n***Waiting PART3: Test for XSIGCHL to Finish***\n");
#endif
#ifdef PART3_3
	kprintf("\n***PART3: Test for XSIGXTM***\n");
	sleepms(500);
	xtm_test1();
	sleepms(5000);
	kprintf("\n***Waiting PART3: Test for XSIGXTM to Finish***\n");

#endif

#ifdef PART3_4
	kprintf("\n***PART3: Test for Multiple Signal***\n");
	sleepms(500);
	multi_test1();
	sleepms(5000);
	kprintf("\n***Waiting PART3: Test for XSIGXTM to Finish***\n");

#endif

#ifdef PART4
	kprintf("\n***PART2: Test 1 Memory Garbage Collection \n");
	struct memblk *memptr; /* Ptr to memory block		*/
	uint32 free_mem = 0;
	for (memptr = memlist.mnext; memptr != NULL;
		 memptr = memptr->mnext)
	{
		free_mem += memptr->mlength;
	}
	kprintf("%10d bytes of free memory.  Free list:\n", free_mem);
	for (memptr = memlist.mnext; memptr != NULL; memptr = memptr->mnext)
	{
		kprintf("           [0x%08X to 0x%08X]\r\n",
				(uint32)memptr, ((uint32)memptr) + memptr->mlength - 1);
	}

	kprintf("******************************************************\n");

	resume(create(mgcTest, 1024, 20, "mgcTest", 0));

	free_mem = 0;
	for (memptr = memlist.mnext; memptr != NULL;
		 memptr = memptr->mnext)
	{
		free_mem += memptr->mlength;
	}
	kprintf("%10d bytes of free memory.  Free list:\n", free_mem);
	for (memptr = memlist.mnext; memptr != NULL; memptr = memptr->mnext)
	{
		kprintf("           [0x%08X to 0x%08X]\r\n",
				(uint32)memptr, ((uint32)memptr) + memptr->mlength - 1);
	}

	sleep(1000);
	kprintf("\n***Waiting PART2: Test 1 to Finish***\n");
	sleepms(4000);

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
void mgcTest(void)
{
	void *test1 = getmem(256);
	void *test2 = getmem(256);
	//void *test3 = getmem(256);
	//void *test4 = getmem(256);
	//void *test5 = getmem(256);
	//printMylist();
	/*if (freemem(test1, 256) == SYSERR)
	{
		kprintf("FREEMEM FAILED\n");
	}
	*/
}
