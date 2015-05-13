/*
 *  Warning
 *
 *  This implementation does not contain memory barriers (DMB - command for ARM).
 *  Therefore, there can't be used to implement the synchronization primitives.
*/
#define ATOMIC_FETCH_OPP(OPP, CMD)	                         \
.align  2                                                    ;\
    .global atomic_fetch_##OPP                               ;\
    .type   atomic_fetch_##OPP, %function                    ;\
atomic_fetch_##OPP:                                          ;\
.try_##OPP:                                                  ;\
    ldrex   r2,  [r0]                                        ;\
    ##CMD   r12, r2,  r1                                     ;\
    strex   r3,  r12, [r0]                                   ;\
    teq     r3,  #0                                          ;\
    bne     .try_##OPP                                       ;\
    mov     r0,  r2                                          ;\
    bx      lr                                               ;\
    .size   atomic_fetch_##OPP, .-atomic_fetch_##OPP         ;\



.text


ATOMIC_FETCH_OPP(add, add)
ATOMIC_FETCH_OPP(sub, sub)
ATOMIC_FETCH_OPP(and, and)
ATOMIC_FETCH_OPP(xor, eor)
ATOMIC_FETCH_OPP(or, orr)





.align  2;
    .global atomic_exchange
    .type   atomic_exchange, %function
atomic_exchange:
    mov     r3, r0
    dmb     sy
.try_exchange:
    ldrex   r0, [r3]
    strex   r2, r1, [r3]
    teq     r2, #0
    bne     .try_exchange
    dmb     sy
    bx      lr
    .size   atomic_exchange, .-atomic_exchange

