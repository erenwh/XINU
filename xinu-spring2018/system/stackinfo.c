#include <xinu.h>
#include <stdio.h>

void stackinfo() {
    unsigned long *base_ptr;
    unsigned long *stack_ptr;

    asm (
            "mov %%ebp, %0"
            : "=r"(base_ptr) //out
            );
    asm (
            "mov %%esp, %0"
            : "=r"(stack_ptr) //out
            );
    kprintf("Base of the stack : Address - 0x%08X, Value - 0x%08X\n", stack_ptr, *stack_ptr);
    kprintf("Top of the stack : Address - 0x%08X, Value - 0x%08X\n", base_ptr, *base_ptr);
    kprintf("\n");
    return;
}
