/**
  *     long host2net(long x) use a special assembly x86instruction to write very
  *     compact assembly code for the function.
  *     It follow the AT&T assembly language syntax.
  *     Han Wang @ Purdue
  */

.global host2net
.section .text
.type host2net, %function

host2net:
        pushl   %ebp                            //push base pointer
        movl    %esp,           %ebp            //move stack pointer into base pointer
        movl    8(%ebp),        %eax            //move base pointer + 8 into AX
        bswap   %eax                            //magical bswap
        popl    %ebp                            //pop base pointer
        ret                                     //get result
