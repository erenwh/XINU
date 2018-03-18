/* xts-enqueue.c  -  xts_enqueue */

#include <xinu.h>

/**
 * 
 * enqueues the process given by pid and priority prio into the multilevel 
 * feedback queue at the appropriate place. 
 * xts_enqueue() return 0 if successful, -1 otherwise.
 * 
 */

int xts_enqueue(pid32 pid, /* pid of process */
                pri16 prio /* process's priority */
)
{

    qid16 q = xts_arr[prio]; // find the correct queue q
    int tail, prev;          /* Tail & previous node indexes	*/

    if (isbadqid(q) || isbadpid(pid))
    {
        return -1;
    }

    tail = queuetail(q);
    prev = queuetab[tail].qprev;

    queuetab[pid].qnext = tail; /* Insert just before tail node	*/
    queuetab[pid].qprev = prev;
    queuetab[prev].qnext = pid;
    queuetab[tail].qprev = pid;

    xts_ready[prio].status = 1;
    return 0;
}
