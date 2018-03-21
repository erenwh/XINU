/* yield.c - yield */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  yield  -  Voluntarily relinquish the CPU (end a timeslice)
 *------------------------------------------------------------------------
 */
syscall yield(void)
{
	intmask mask; /* Saved interrupt mask		*/

	mask = disable();
	proctab[currpid].prblock = 1;
	resched();
	restore(mask);
	return OK;
}
