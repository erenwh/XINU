/* resched.c - resched, resched_cntl */

#include <xinu.h>

struct defer Defer;

/*------------------------------------------------------------------------
 *  resched  -  Reschedule processor to highest priority eligible process
 *------------------------------------------------------------------------
 */
void resched(void) /* Assumes interrupts are disabled	*/
{
    struct procent *ptold; /* Ptr to table entry for old process	*/
    struct procent *ptnew; /* Ptr to table entry for new process	*/

    /* If rescheduling is deferred, record attempt and return */

    if (Defer.ndefers > 0)
    {
        Defer.attempt = TRUE;
        return;
    }

    /* Point to process table entry for the current (old) process */

    ptold = &proctab[currpid];

    /* Han Wang: handle null process */
    if (currpid == 0)
    {
        //kprintf("debug\n");
        ptold->prprio = 0;
        ptold->prcputot += clkmilli - prctxswbeg;

        // when null process is the only process
        pri16 readyHigh = xts_priochk();
        //kprintf("readyhigh:%d\n", readyHigh);
        if (readyHigh == -1) // is Ready empty
        {
            // add time slice to null process keeps it running
            preempt = xts_conf[0].xts_quantum;
            prctxswbeg = clkmilli; /*Han Wang: update timestamp for next time use */
            return;
        }
        // if null process is not the only process
        else
        {
            //dont run the null process
            //kprintf("debug_1\n");
            ptold->prstate = PR_READY;
            xts_enqueue(currpid, ptold->prprio); //enqueue to 0
            //printReady();
        }
    }
    else
    { // if its not null proc
        if (ptold->prstate == PR_CURR)
        { //CPU
            ptold->prcputot += clkmilli - prctxswbeg;
            // prioiry update section
            //if (wakeupbool == 0) // if its not from wakeup()
            //{
            if (preempt > 0) // give up unused time slice
            {
                ptold->prprio = xts_conf[ptold->prprio].xts_slpret;
            }
            else
            {
                //used up time slice
                ptold->prprio = xts_conf[ptold->prprio].xts_tqexp;
            }
            //}

            //Ready list checking section
            // if old prio is higher than list
            pri16 readyHigh = xts_priochk();
            if (ptold->prprio > readyHigh)
            {
                //if (wakeupbool == 0)
                //{
                preempt = xts_conf[ptold->prprio].xts_quantum;
                //}
                prctxswbeg = clkmilli;
                wakeupbool = 0;

                return;
            }

            /* Old process will no longer remain current */
            wakeupbool = 0;
            ptold->prstate = PR_READY;
            xts_enqueue(currpid, ptold->prprio);
            //insert(currpid, readylist, ptold->prprio);
        }
    }

    /* Force context switch to highest priority ready process */

    currpid = xts_dequeue(); // dequeue from xts
    ptnew = &proctab[currpid];
    ptnew->prstate = PR_CURR;
    //preempt = QUANTUM; /* Reset time slice for process	*/
    preempt = xts_conf[ptnew->prprio].xts_quantum; //update quantum base on TS table
    wakeupbool = 0;
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
status resched_cntl(            /* Assumes interrupts are disabled	*/
                    int32 defer /* Either DEFER_START or DEFER_STOP	*/
)
{
    switch (defer)
    {

    case DEFER_START: /* Handle a deferral request */

        if (Defer.ndefers++ == 0)
        {
            Defer.attempt = FALSE;
        }
        return OK;

    case DEFER_STOP: /* Handle end of deferral */
        if (Defer.ndefers <= 0)
        {
            return SYSERR;
        }
        if ((--Defer.ndefers == 0) && Defer.attempt)
        {
            resched();
        }
        return OK;

    default:
        return SYSERR;
    }
}
