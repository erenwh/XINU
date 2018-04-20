/* getmem.c - getmem */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  getmem  -  Allocate heap storage, returning lowest word address
 *------------------------------------------------------------------------
 */
char *getmem(
	uint32 nbytes /* Size of memory requested	*/
)
{
	intmask mask; /* Saved interrupt mask		*/
	struct memblk *prev, *curr, *leftover, *tempblk;
	mask = disable();
	if (nbytes == 0)
	{
		restore(mask);
		return (char *)SYSERR;
	}
	struct procent *prptr = &proctab[currpid];

	uint32 extraspace = (uint32)roundmb(sizeof(struct memblk));
	nbytes = (uint32)roundmb(nbytes) + extraspace; /* Use memblk multiples	*/

	prev = &memlist;
	curr = memlist.mnext;
	while (curr != NULL)
	{ /* Search free list	*/

		if (curr->mlength == nbytes)
		{ /* Block is exact match	*/
			prev->mnext = curr->mnext;
			memlist.mlength -= nbytes;

			if (currpid != 0) // if its not my nullproc
			{

				if (prptr->mylist.mnext != NULL) // if mylist have next
				{
					kprintf("creating non-first element(split)\n");
					tempblk = prptr->mylist.mnext; // set temp to head

					while (tempblk->mnext != NULL)
					{
						tempblk = tempblk->mnext; // find the last one
					}
					tempblk->mnext = (struct memblk *)curr;
					tempblk->mnext->mlength = nbytes;
					tempblk->mnext->mnext = NULL;
					//printMylist();
				}
				else // if mylist doesnot have next
				{
					kprintf("creating first element(split)\n");
					// set the next pointer to curr
					prptr->mylist.mnext = (struct memblk *)curr; // head is empty
					prptr->mylist.mnext->mlength = nbytes;
					prptr->mylist.mnext->mnext = NULL;
				}
				//printMylist();
				restore(mask);
				return (char *)((uint32)curr + extraspace);
			}
			restore(mask);
			return (char *)(curr);
		}
		else if (curr->mlength > nbytes)
		{ /* Split big block	*/
			leftover = (struct memblk *)((uint32)curr +
										 nbytes);
			prev->mnext = leftover;
			leftover->mnext = curr->mnext;
			leftover->mlength = curr->mlength - nbytes;
			memlist.mlength -= nbytes;

			if (currpid != 0)
			{
				if (prptr->mylist.mnext != NULL) // if mylist have next
				{
					kprintf("creating non-first element(split)\n");
					tempblk = prptr->mylist.mnext; // set temp to head

					while (tempblk->mnext != NULL)
					{
						tempblk = tempblk->mnext; // find the last one
					}
					tempblk->mnext = (struct memblk *)curr;
					tempblk->mnext->mlength = nbytes;
					tempblk->mnext->mnext = NULL;
					//printMylist();
				}
				else // if mylist doesnot have next
				{
					kprintf("creating first element(split)\n");
					// set the next pointer to curr
					prptr->mylist.mnext = (struct memblk *)curr; // head is empty
					prptr->mylist.mnext->mlength = nbytes;
					prptr->mylist.mnext->mnext = NULL;
				}
				//printMylist();
				restore(mask);
				return (char *)((uint32)curr + extraspace);
			}

			restore(mask);
			return (char *)(curr);
		}
		else
		{ /* Move to next block	*/
			prev = curr;
			curr = curr->mnext;
		}
	}
	restore(mask);
	return (char *)SYSERR;
}
