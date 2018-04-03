/* jumpcb.s - clkdisp (x86) */

/*------------------------------------------------------------------------
 * jumpcb  -  Interrupt dispatcher for asy call back interrupts (Lab5 Han Wang)
 *------------------------------------------------------------------------
 */

 .global jumpcb
.section .text
.type jumpcb, %function

jumpcb:
		pushal			# Save registers
		cli			# Disable further interrupts
		call	mrecv_cb	# Call callback
		sti			# Restore interrupt status
		popal			# Restore registers
		ret			# Return to func
