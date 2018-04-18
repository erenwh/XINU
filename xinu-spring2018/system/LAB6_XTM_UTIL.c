#include <xinu.h>

// Test for XSIGXTM
//pid32 xtmpid;
void xtm_test1()
{

    pid32 sigRec1 = create(XTM_rec, 1024, 20, "sigRec1", 0, NULL);

    resume(sigRec1);

    // kill(sigRec1);
}

int wtmcallback(void)
{
    kprintf("Wall time exceeded! XTMcallback(pid%d) called at %d seconds\n", currpid, clktime);
    sigcbunreg(XSIGXTM);
    return OK;
}

int XTM_rec(void)
{
    kprintf("clktime:%d seconds\n", clktime);
    if (sigcbreg(XSIGXTM, &wtmcallback, 3) != OK)
    {
        kprintf("wall time callback function registration failed\n");
        return 1;
    }

    //xtmpid = currpid;

    while (1)
    {
    }
    return OK;
}