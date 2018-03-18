/* initialize.c - nulluser, sysinit, sizmem */

/* Handle system initialization and become the null process */

#include <xinu.h>
#include <string.h>

extern void prnsegadd(void);

extern void start(void); /* Start of Xinu code			*/
extern void *_end;		 /* End of Xinu code			*/

/* Function prototypes */

extern void main(void);	/* Main is the first process created	*/
extern void xdone(void);   /* System "shutdown" procedure		*/
static void sysinit();	 /* Internal system initialization	*/
extern void meminit(void); /* Initializes the free memory list	*/

/* Declarations of major kernel variables */

struct procent proctab[NPROC]; /* Process table			*/
struct sentry semtab[NSEM];	/* Semaphore table			*/
struct memblk memlist;		   /* List of free memory blocks		*/

/* lab 4(Han Wang): struct */
struct xts_tab xts_conf[MAXSIZE];	  /* table of priorities */
struct xts_multifb xts_ready[MAXSIZE]; /* ready array */
qid16 queueArr[MAXSIZE];

/* Active system status */

int prcount;   /* Total number of live processes	*/
pid32 currpid; /* ID of currently executing process	*/

/*------------------------------------------------------------------------
 * nulluser - initialize the system and become the null process
 *
 * Note: execution begins here after the C run-time environment has been
 * established.  Interrupts are initially DISABLED, and must eventually
 * be enabled explicitly.  The code turns itself into the null process
 * after initialization.  Because it must always remain ready to execute,
 * the null process cannot execute code that might cause it to be
 * suspended, wait for a semaphore, put to sleep, or exit.  In
 * particular, the code must not perform I/O except for polled versions
 * such as kprintf.
 *------------------------------------------------------------------------
 */

void nulluser()
{
	struct memblk *memptr; /* Ptr to memory block		*/
	uint32 free_mem;	   /* Total amount of free memory	*/

	/* Initialize the system */

	sysinit();

	kprintf("\n\r%s\n\n\r", VERSION);

	/* Output Xinu memory layout */
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

	kprintf("%10d bytes of Xinu code.\n",
			(uint32)&etext - (uint32)&text);
	kprintf("           [0x%08X to 0x%08X]\n",
			(uint32)&text, (uint32)&etext - 1);
	kprintf("%10d bytes of data.\n",
			(uint32)&ebss - (uint32)&data);
	kprintf("           [0x%08X to 0x%08X]\n\n",
			(uint32)&data, (uint32)&ebss - 1);

	//        prnsegadd();
	/* Enable interrupts */

	enable();

	/* Create a process to execute function main() */

	resume(
		create((void *)main, INITSTK, INITPRIO, "Main process", 0,
			   NULL));

	/* Become the Null process (i.e., guarantee that the CPU has	*/
	/*  something to run when no other process is ready to execute)	*/

	while (TRUE)
	{
		; /* Do nothing */
	}
}

/*------------------------------------------------------------------------
 *
 * sysinit  -  Initialize all Xinu data structures and devices
 *
 *------------------------------------------------------------------------
 */
static void sysinit()
{
	int32 i;
	struct procent *prptr; /* Ptr to process table entry	*/
	struct sentry *semptr; /* Ptr to semaphore table entry	*/

	/* Platform Specific Initialization */

	platinit();

	/* Initialize the interrupt vectors */

	initevec();

	/* Initialize free memory list */

	meminit();

	/* Initialize system variables */

	/* Count the Null process as the first process in the system */

	prcount = 1;

	/* Scheduling is not currently blocked */

	Defer.ndefers = 0;

	/* Initialize process table entries free */

	for (i = 0; i < NPROC; i++)
	{
		prptr = &proctab[i];
		prptr->prstate = PR_FREE;
		prptr->prname[0] = NULLCH;
		prptr->prstkbase = NULL;
		prptr->prprio = 0;
	}

	/* Initialize the Null process entry */

	prptr = &proctab[NULLPROC];
	prptr->prstate = PR_CURR;
	prptr->prprio = 0;
	strncpy(prptr->prname, "prnull", 7);
	prptr->prstkbase = getstk(NULLSTK);
	prptr->prstklen = NULLSTK;
	prptr->prstkptr = 0;
	currpid = NULLPROC;

	/* Initialize semaphores */

	for (i = 0; i < NSEM; i++)
	{
		semptr = &semtab[i];
		semptr->sstate = S_FREE;
		semptr->scount = 0;
		semptr->squeue = newqueue();
	}

	/* Initialize buffer pools */

	bufinit();

	/* lab4(Han Wang): init TS scheduler */
	for (i = 0; i < MAXSIZE; i++)
	{
		if (i < 10)
		{
			xts_conf[i].xts_quantum = 200;
			xts_conf[i].xts_tqexp = 0;
			xts_conf[i].xts_slpret = 50;
		}
		else
		{
			xts_conf[i].xts_tqexp = i - 10;
			if (i < 20)
			{
				xts_conf[i].xts_quantum = 160;
				xts_conf[i].xts_slpret = 51;
			}
			else if (i < 30)
			{
				xts_conf[i].xts_quantum = 120;
				xts_conf[i].xts_slpret = 52;
			}
			else if (i < 40)
			{
				xts_conf[i].xts_quantum = 80;
				if (i < 35)
				{
					xts_conf[i].xts_slpret = 53;
				}
				else
				{
					xts_conf[i].xts_slpret = 54;
				}
			}
			else if (i < 59)
			{
				xts_conf[i].xts_quantum = 40;
				if (i < 45)
				{
					xts_conf[i].xts_slpret = 55;
				}
				else if (i == 45)
				{
					xts_conf[i].xts_slpret = 56;
				}
				else if (i == 46)
				{
					xts_conf[i].xts_slpret = 57;
				}
				else
				{
					xts_conf[i].xts_slpret = 58;
				}
			}
			else
			{
				xts_conf[i].xts_quantum = 20;
				xts_conf[i].xts_slpret = 59;
			}
		}
	}

	/* Create a ready list for processes */

	//readylist = newqueue();

	/* lab4(Han Wang): init xts table and array */
	for (int i = 0; i < MAXSIZE; i++)
	{
		queueArr[i] = newqueue();
		xts_ready[i].status = 0;
		xts_ready[i].queue_head = queuehead(queueArr[i]);
		xts_ready[i].queue_tail = queuetail(queueArr[i]);
	}

	/* Initialize the real time clock */

	clkinit();

	for (i = 0; i < NDEVS; i++)
	{
		init(i);
	}
	return;
}

int32 stop(char *s)
{
	kprintf("%s\n", s);
	kprintf("looping... press reset\n");
	while (1)
		/* Empty */;
}

int32 delay(int n)
{
	DELAY(n);
	return OK;
}
