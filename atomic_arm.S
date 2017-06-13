/*
 * atomic_arm.S
 *
 *
 * version 1.0
 *
 *
 * BSD 3-Clause License
 *
 * Copyright (c) 2015, Koynov Stas - skojnov@yandex.ru
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * more details see https://github.com/KoynovStas/atomic_arm
 *
 *
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

