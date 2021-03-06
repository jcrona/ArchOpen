/* 
*   kernel/lib/memset.S
*
*   MediOS project
*   Copyright (c) 2005 by Christophe THOMAS (oxygen77 at free.fr)
*
*   Code from uClinux
*   Copyright (C) 1995, 1996 Russell King
*
*  ASM optimised string functions
*/


/*.text*/
.section ".core"

/*
 * Prototype: void memcpy(void *to,const void *from,unsigned long n);
 * ARM3: cant use memcopy here!!!
 */

	.align	5
	.word	0

1:	subs	r2, r2, #4		@ 1 do we have enough
	blt	5f			@ 1 bytes to align with?
	cmp	r3, #2			@ 1
	strltb	r1, [r0], #1		@ 1
	strleb	r1, [r0], #1		@ 1
	strb	r1, [r0], #1		@ 1
	add	r2, r2, r3		@ 1 (r2 = r2 - (4 - r3))
/*
 * The pointer is now aligned and the length is adjusted.  Try doing the
 * memzero again.
 */

.global memset
memset:
	ands	r3, r0, #3		@ 1 unaligned?
	bne	1b			@ 1
/*
 * we know that the pointer in r0 is aligned to a word boundary.
 */
	orr	r1, r1, r1, lsl #8
	orr	r1, r1, r1, lsl #16
	mov	r3, r1
	cmp	r2, #16
	blt	4f
/*
 * We need an extra register for this loop - save the return address and
 * use the LR
 */
	str	lr, [sp, #-4]!
	mov	ip, r1
	mov	lr, r1

2:	subs	r2, r2, #64
	stmgeia	r0!, {r1, r3, ip, lr}	@ 64 bytes at a time.
	stmgeia	r0!, {r1, r3, ip, lr}
	stmgeia	r0!, {r1, r3, ip, lr}
	stmgeia	r0!, {r1, r3, ip, lr}
	bgt	2b
	beq	6f			@ VP
;; 	ldmeqfd sp!, {pc}		@ Now <64 bytes to go.
/*
 * No need to correct the count; we're only testing bits from now on
 */
	tst	r2, #32
	stmneia	r0!, {r1, r3, ip, lr}
	stmneia	r0!, {r1, r3, ip, lr}
	tst	r2, #16
	stmneia	r0!, {r1, r3, ip, lr}
	ldr	lr, [sp], #4

4:	tst	r2, #8
	stmneia	r0!, {r1, r3}
	tst	r2, #4
	strne	r1, [r0], #4
/*
 * When we get here, we've got less than 4 bytes to zero.  We
 * may have an unaligned pointer as well.
 */
5:	tst	r2, #2
	strneb	r1, [r0], #1
	strneb	r1, [r0], #1
	tst	r2, #1
	strneb	r1, [r0], #1
	bx	lr
;; 	mov pc, lr

	@ VP fix for thumb interworking, maybe not optimal
6:	ldr	lr, [sp], #4
	bx	lr
