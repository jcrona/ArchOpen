/* 
*   medios/api/codec_init/codec_stop.S
*
*   MediOS project
*   Copyright (c) 2005 by Christophe THOMAS (oxygen77 at free.fr)
*/


.text



.global exit
exit:
    ldr     r0, =.SavSP
    ldr     sp, [r0]
    ldmia   sp, {r0 - r12}			@ read r0 - r12
    add     sp, sp, #72
    mov     r0, #0
    ldr     pc, [sp],#4
