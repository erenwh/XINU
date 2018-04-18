#include <xinu.h>

void multi_test1() {
    pid32 xtm = create(XTM_rec, 1024, 30, "MIX_XTM", 0, NULL);
    resume(xtm);

    pid32 chd = create(parentapp, 1024, 30, "MIX_CHD", 0, NULL);
    resume(chd);
/*
    pid32 RCV1 = create(sigRec, 1024, 20, "MIX_RCV", 0, NULL);
    pid32 RCV2 = create(sigSend, 1024, 20, "MIX_SEND", 2, RCV1, 'A');
    
    resume(RCV2);
    sleepms(500);

    resume(RCV1);
    sleepms(2000);

    kill(RCV1);
    kill(RCV2);
*/

}