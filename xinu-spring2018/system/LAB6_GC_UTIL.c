#include <xinu.h>
//util for garbage collection
void mgcTest(void)
{
    printmem();

    char *test1 = getmem(256);
    //printmem();
    freemem(test1, 256);

    char *test2 = getmem(512);

    char *test3 = getmem(512);

    freemem(test3, 512);

    void *test4 = getmem(512);

    //void *test5 = getmem(256);
    //printmem();
    //char *test3 = getmem(256);
    //printmem();
    //printmem();

    //printMylist();

    //printmem();
    //char *test2 = getmem(256);
    //char *test2 = getmem(256);
    //char *test3 = getmem(256);
    //void *test4 = getmem(256);
    //void *test5 = getmem(256);
    //printMylist();
    /*if (freemem(test1, 256) == SYSERR)
	{
		kprintf("FREEMEM FAILED\n");
	}
	*/
}
void printmem(void)
{
    intmask mask = disable();
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
    restore(mask);
}

void printMylist(void)
{

    struct memblk *tempprev, *tempcurr;
    struct procent *prptr = &proctab[currpid];
    tempprev = &prptr->mylist;
    tempcurr = prptr->mylist.mnext;
    kprintf("Print my list:\n");
    while (tempcurr != NULL)
    {
        printf("\nprev:0x%08X, length:%d,  next:0x%08X, length:%d\n\n", tempprev, tempprev->mlength, tempcurr, tempcurr->mlength);
        tempcurr = tempcurr->mnext;
    }
}
