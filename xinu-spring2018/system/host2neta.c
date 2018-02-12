/**
 * use in-line assembly, i.e., function asm(), to achieve the same goal. 
 * Save the function long host2neta(long x) in host2neta.c under system/
 * Han Wang @ Purdue
 */
#include <xinu.h>

long host2neta(long x) {
    long result;
    asm (
            "movl       %1,     %%eax; \
            bswap       %%eax; \
            movl        %%eax,  %0"
            :"=r"(result)            //out
            : "r"(x)          //in
        );
    return result;
}
