/* freemem.c - freemem */

#include <xinu.h>
#define PART4
/*------------------------------------------------------------------------
 *  freemem  -  Free a memory block, returning the block to the free list
 *------------------------------------------------------------------------
 */
syscall freemem(
	char *blkaddr, /* Pointer to memory block	*/
	uint32 nbytes  /* Size of block in bytes	*/
)
{
	intmask mask; /* Saved interrupt mask		*/
	struct memblk *next, *prev, *block;
	uint32 top;

	mask = disable();
	if ((nbytes == 0) || ((uint32)blkaddr < (uint32)minheap) || ((uint32)blkaddr > (uint32)maxheap))
	{
		restore(mask);
		return SYSERR;
	}

	uint32 extraspace = (uint32)roundmb(sizeof(struct memblk));
#ifdef PART4

	kprintf("user is freeing %d, at 0x%08X, extraspace:%d\n", nbytes, blkaddr, extraspace);

#endif
	nbytes = (uint32)roundmb(nbytes) + extraspace;			 /* Use memblk multiples	*/
	block = (struct memblk *)((uint32)blkaddr - extraspace); // substract the header

	struct procent *prptr = &proctab[currpid];

	struct memblk *tempprev, *tempcurr;
	tempprev = &prptr->mylist;
	tempcurr = prptr->mylist.mnext;

	while (tempcurr != NULL)
	{
		if (tempprev->mnext == block)
		{
			break; // found it
		}
		tempprev = tempcurr;
		tempcurr = tempcurr->mnext;
	}
	if (tempcurr != NULL)
	{ // found it
		//changing the point to the next's next
		tempprev->mnext = tempcurr->mnext; //remove the block and link it
	}

	prev = &memlist; /* Walk along free list	*/
	next = memlist.mnext;
	while ((next != NULL) && (next < block))
	{
		prev = next;
		next = next->mnext;
	}

	if (prev == &memlist)
	{ /* Compute top of previous block*/
		top = (uint32)NULL;
	}
	else
	{
		top = (uint32)prev + prev->mlength;
	}

	/* Ensure new block does not overlap previous or next blocks	*/

	if (((prev != &memlist) && (uint32)block < top) || ((next != NULL) && (uint32)block + nbytes > (uint32)next))
	{
		restore(mask);
		return SYSERR;
	}

	memlist.mlength += nbytes;

	/* Either coalesce with previous block or add to free list */

	if (top == (uint32)block)
	{ /* Coalesce with previous block	*/
		prev->mlength += nbytes;
		block = prev;
	}
	else
	{ /* Link into list as new node	*/
		block->mnext = next;
		block->mlength = nbytes;
		prev->mnext = block;
	}

	/* Coalesce with next block if adjacent */

	if (((uint32)block + block->mlength) == (uint32)next)
	{
		block->mlength += next->mlength;
		block->mnext = next->mnext;
	}
	restore(mask);
	return OK;
}
