#ifndef ATOMIC_ARM_HEADER
#define ATOMIC_ARM_HEADER


#ifdef  __cplusplus
        #define  EXTERN_PREFIX extern "C"
#else
        #define  EXTERN_PREFIX extern
#endif



EXTERN_PREFIX int atomic_exchange(int *obj, int arg);
EXTERN_PREFIX int atomic_fetch_add(int *obj, int arg);
EXTERN_PREFIX int atomic_fetch_sub(int *obj, int arg);

EXTERN_PREFIX unsigned int atomic_fetch_and(unsigned int *obj, unsigned int arg);
EXTERN_PREFIX unsigned int atomic_fetch_xor(unsigned int *obj, unsigned int arg);
EXTERN_PREFIX unsigned int atomic_fetch_or(unsigned int *obj, unsigned int arg);


#endif //ATOMIC_ARM_HEADER
