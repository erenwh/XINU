	.file	"host2netca.c"
	.text
	.globl	host2netca
	.type	host2netca, @function
host2netca:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	leal	11(%ebp), %eax
	movl	%eax, -4(%ebp)
	leal	-16(%ebp), %eax
	movl	%eax, -8(%ebp)
	movl	$0, -12(%ebp)
	jmp	.L2
.L3:
	movl	-8(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, -8(%ebp)
	movl	-4(%ebp), %edx
	leal	-1(%edx), %ecx
	movl	%ecx, -4(%ebp)
	movb	(%edx), %dl
	movb	%dl, (%eax)
	incl	-12(%ebp)
.L2:
	movl	-12(%ebp), %eax
	cmpl	$3, %eax
	jbe	.L3
	movl	-16(%ebp), %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	host2netca, .-host2netca
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.6) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
