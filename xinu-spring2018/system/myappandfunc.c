#include <xinu.h>
#include <stdio.h>

extern void stackinfo(void);

int fun1(int a, int b) {
    int result;
    result = a + b;
    kprintf("3. after appl1() calls fun1() and before fun1() returns:\n");
    stackinfo();
    kprintf("fun1: (a)%d + (b)%d = %d\n\n", a,b,result);
    return result;
}

int appl1() {
    kprintf("2. after appl1() is created before fun1() is called:\n");
    stackinfo();

    int result;
    result = fun1(13, 21);
    kprintf("4. after appl1() calls fun1() and after fun1() has returned:\n");
    stackinfo();
    kprintf("appl1: func result is %d\n\n",result);
    return result;
}
