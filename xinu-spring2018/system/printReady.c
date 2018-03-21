#include <xinu.h>

void printReady(void)
{
    for (int i = 59; i >= 0; i--)
    {
        qid16 QID = xts_ready[i].queue_head;
        pid32 f = firstid(QID);
        struct procent *p = &proctab[f];
        printf("qid:%d, pid:%d, name:%s\n", QID, f, p->prname);
        
    }
}