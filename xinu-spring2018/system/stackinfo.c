#include <xinu.h>
#include <stdio.h>

void stackinfo() {
    unsigned long *base_ptr;
    unsigned long *stack_ptr;
    //stack pointer
    asm (
            "mov %%esp, %0"
            : "=r"(stack_ptr) //out
            );
    //base pointer
    struct procent *pproc = &proctab[(getpid())];
    base_ptr = (unsigned long *) pproc->prstkbase;

    kprintf("Base of the stack : Address - 0x%08X, Value - 0x%08X\n", base_ptr, *base_ptr);
    kprintf("Top of the stack : Address - 0x%08X, Value - 0x%08X\n", stack_ptr, *stack_ptr);
    kprintf("\n");
    return;
}
