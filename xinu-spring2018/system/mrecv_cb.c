#include <xinu.h>

//umsg32 mbuf;

int32 mrecv_cb(void)
{
    mbuf = receive();
    //kprintf("mbuf = %c\n", mbuf);
    return (OK);
}
