/*
 * atomic_arm.h
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
 */

#ifndef ATOMIC_ARM_HEADER
#define ATOMIC_ARM_HEADER



#ifdef  __cplusplus
        #define  EXTERN_PREFIX extern "C"
#else
        #define  EXTERN_PREFIX extern
#endif



#undef  ATOMIC_OPP  //Atomic operations and command not supported



#if (__STDC_VERSION__ >= 201112L) && (__STDC_NO_ATOMICS__ != 1)
// The implementation supports atomic types and <stdatomic.h> (C11)
// C is ISO/IEC 9899:2011 (C11) and __STDC_NO_ATOMICS__ is not defined
// __STDC_NO_ATOMICS__ see in 6.10.8.3 Conditional feature macros (standart C11)
// __STDC_VERSION__ in gcc defined if set -std=c11


    #define  ATOMIC_OPP     //Atomic operations supported
    #include <stdatomic.h>


#endif //#if (__STDC_VERSION__ >= 201112L) && (__STDC_NO_ATOMICS__ != 1)




#if    !defined(  ATOMIC_OPP  )   \
    && (defined(__ARM_ARCH_6__)   \
    ||  defined(__ARM_ARCH_6J__)  \
    ||  defined(__ARM_ARCH_6K__)  \
    ||  defined(__ARM_ARCH_6Z__)  \
    ||  defined(__ARM_ARCH_6ZK__) \
    ||  defined(__ARM_ARCH_7__)   \
    ||  defined(__ARM_ARCH_7A__)  \
    ||  defined(__ARM_ARCH_7R__) )


    #define  ATOMIC_OPP        //Atomic operations supported


    //use our atomic functions
    //functions only for int(32 bits): sizeof(int) == 4

    EXTERN_PREFIX int atomic_exchange(int *obj, int arg);
    EXTERN_PREFIX int atomic_fetch_add(int *obj, int arg);
    EXTERN_PREFIX int atomic_fetch_sub(int *obj, int arg);

    EXTERN_PREFIX unsigned int atomic_fetch_and(unsigned int *obj, unsigned int arg);
    EXTERN_PREFIX unsigned int atomic_fetch_xor(unsigned int *obj, unsigned int arg);
    EXTERN_PREFIX unsigned int atomic_fetch_or(unsigned int *obj, unsigned int arg);


#endif //ifdef __ARM_ARCH_XXX__




#ifdef ATOMIC_OPP

    //preg is volatile pointer to reg
    //IF use our atomic functions, reg must be sizeof(reg) == 4

    #define  ATOMIC_SET_BIT(preg, num_bit)  atomic_fetch_or (preg,  (1 << num_bit))
    #define  ATOMIC_CLR_BIT(preg, num_bit)  atomic_fetch_and(preg, ~(1 << num_bit))
    #define  ATOMIC_INV_BIT(preg, num_bit)  atomic_fetch_xor(preg,  (1 << num_bit))


    #define  ATOMIC_SET_FLAG(preg, flag)  atomic_fetch_or (preg,  (flag))
    #define  ATOMIC_CLR_FLAG(preg, flag)  atomic_fetch_and(preg, ~(flag))
    #define  ATOMIC_INV_FLAG(preg, flag)  atomic_fetch_xor(preg,  (flag))


#endif //#ifdef ATOMIC_OPP





#endif //ATOMIC_ARM_HEADER
