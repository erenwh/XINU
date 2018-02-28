/* resched.c - resched, resched_cntl */

#include <xinu.h>

struct	defer	Defer;

/*------------------------------------------------------------------------
 *  resched  -  Reschedule processor to highest priority eligible process
 *------------------------------------------------------------------------
 */
void	resched(void)		/* Assumes interrupts are disabled	*/
{
    struct procent *ptold;	/* Ptr to table entry for old process	*/
    struct procent *ptnew;	/* Ptr to table entry for new process	*/
    
    
    
    /* If rescheduling is deferred, record attempt and return */
    
    if (Defer.ndefers > 0) {
        Defer.attempt = TRUE;
        return;
    }
    
    
    /* Point to process table entry for the current (old) process */
    
    ptold = &proctab[currpid];
    
    /* Han Wang: handle null process */
    if (currpid == 0) {
        ptold->prprio = 0;
    }
    if (ptold->prstate == PR_CURR) {  /* Process remains eligible */
        if (ptold->prprio > firstkey(readylist)) {
            if(currpid != 0) { /*Han Wang:if current process has a higher prority then first in waiting queue, */
                ptold->prcputot += clkmilli - prctxswbeg;/*Han Wang:update its cpu total time using time stamp*/
                pri16 priocheck = ptold->prprio - ptold->prcputot;/*Han Wang:and do priority check for both ends*/
                //Han Wang:check for prio not 0
                if (priocheck < 1) {
                    priocheck = 1; // Han Wang:set it to smallest possible
                } else if( priocheck >= MAXPRIO) { // Han Wang:if its bigger than limit
                    priocheck = MAXPRIO - 1; //Han Wang:set it to max
                }
                //Han Wang:store it back to old
                ptold->prprio = priocheck;
                //Han Wang:increase other waiting process so that avoid all process being priority 1 
                IncreasePrio();
            } else { //Han Wang: null process stays 0, sanity check
                ptold->prprio = 0;
                //Han Wang:increase other waiting process so that avoid all process being priority 1 
                IncreasePrio();
            }
            prctxswbeg = clkmilli;/*Han Wang: update timestamp for next time use */
            return;
        }
        
        /* Han Wang:if current process isnt higher, update the total time used and set it into the readylist */
        if (currpid != 0) {
            ptold->prcputot += clkmilli - prctxswbeg;
        }
        /* Old process will no longer remain current */
        
        ptold->prstate = PR_READY;
        insert(currpid, readylist, ptold->prprio - ptold->prcputot);
    } else {//Han Wang: if pt->old isnt in CURR state, reset the cpu total
        if (currpid != 0) {
            ptold->prcputot += clkmilli - prctxswbeg;
        }
    }
    
    /* Force context switch to highest priority ready process */
    
    currpid = dequeue(readylist);
    ptnew = &proctab[currpid];
    ptnew->prstate = PR_CURR;
    preempt = QUANTUM;		/* Reset time slice for process	*/
    
    
    
    ctxsw(&ptold->prstkptr, &ptnew->prstkptr);
    //Han Wang: new process store the time stamp
    prctxswbeg = clkmilli;
    /* Old process returns here when resumed */
    
    return;
}

/*------------------------------------------------------------------------
 *  resched_cntl  -  Control whether rescheduling is deferred or allowed
 *------------------------------------------------------------------------
 */
status	resched_cntl(		/* Assumes interrupts are disabled	*/
                     int32	defer		/* Either DEFER_START or DEFER_STOP	*/
)
{
    switch (defer) {
            
        case DEFER_START:	/* Handle a deferral request */
            
            if (Defer.ndefers++ == 0) {
                Defer.attempt = FALSE;
            }
            return OK;
            
        case DEFER_STOP:	/* Handle end of deferral */
            if (Defer.ndefers <= 0) {
                return SYSERR;
            }
            if ( (--Defer.ndefers == 0) && Defer.attempt ) {
                resched();
            }
            return OK;
            
        default:
            return SYSERR;
    }
}
