#include <xinu.h>

// Test for BONUS
void bonus_test1()
{

    pid32 sigmy1 = create(bonus_rec, 1024, 20, "sigmy1", 0, NULL);

    resume(sigmy1);

    // kill(sigRec1);
}

int bonuscallback(void)
{
    kprintf("\n(Wang, Han)\n");
    kprintf("\nwang2786\n");
    sigcbunreg(XSIGMY);
    return OK;
}

int bonus_rec(void)
{

    if (sigcbreg(XSIGMY, &bonuscallback, 0) != OK)
    {
        kprintf("MY callback function registration failed\n");
        return 1;
    }

    //xtmpid = currpid;

    while (1)
    {
    }
    return OK;
}