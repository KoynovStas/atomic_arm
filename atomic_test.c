#include <stdio.h>
#include <stdlib.h>


#include "atomic_arm.h"




#define  COUNT_ELEMENTS(array) (sizeof(array) / sizeof(array[0]))




struct test_info_t
{
    const char *func_name;
    const char *file_name;
};




#define  TEST_INIT  {test_info->func_name = __func__; \
                     test_info->file_name = __FILE__; }



typedef  int (*ptest_func)(struct test_info_t  *test_info);


#define TEST_BROKEN    (-1)
#define TEST_PASSED    (0)





// --------------   ADD  ------------------------

int test_atomic_add_1(struct test_info_t  *test_info)
{

    TEST_INIT;

    int i = 0;
    int ret;


    ret = atomic_fetch_add(&i, 1);

    if( (i != 1)  ||  (ret != 0) )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_atomic_add_2(struct test_info_t  *test_info)
{

    TEST_INIT;

    int i = 0;
    int ret;

    ret = atomic_fetch_add(&i, 2);

    if( (i != 2) ||  (ret != 0) )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_atomic_add_3(struct test_info_t  *test_info)
{

    TEST_INIT;

    int i = 0;
    int ret;

    ret = atomic_fetch_add(&i, -2);

    if( (i != -2) ||  (ret != 0) )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_atomic_add_4(struct test_info_t  *test_info)
{

    TEST_INIT;

    int i = -2;
    int ret;

    ret = atomic_fetch_add(&i, 2);

    if( (i != 0) ||  (ret != -2) )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_atomic_add_5(struct test_info_t  *test_info)
{

    TEST_INIT;

    int i = 0;
    int ret;

    ret = atomic_fetch_add(&i, 0xFFFFFF);

    if( (i != 0xFFFFFF) ||  (ret != 0) )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_atomic_add_6(struct test_info_t  *test_info)
{

    TEST_INIT;

    int i = 0;
    int ret;

    ret = atomic_fetch_add(&i, 0);

    if( (i != 0) ||  (ret != 0) )
        return TEST_BROKEN;


    return TEST_PASSED;
}





// -------------------  SUB  --------------------

int test_atomic_sub_1(struct test_info_t  *test_info)
{

    TEST_INIT;

    int i = 0;
    int ret;

    ret = atomic_fetch_sub(&i, 1);

    if( (i != -1) ||  (ret != 0) )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_atomic_sub_2(struct test_info_t  *test_info)
{

    TEST_INIT;

    int i = 0;
    int ret;

    ret = atomic_fetch_sub(&i, 2);

    if( (i != -2) ||  (ret != 0) )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_atomic_sub_3(struct test_info_t  *test_info)
{

    TEST_INIT;

    int i = 0;
    int ret;


    ret = atomic_fetch_sub(&i, -2);

    if( (i != 2) ||  (ret != 0) )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_atomic_sub_4(struct test_info_t  *test_info)
{

    TEST_INIT;

    int i = -2;
    int ret;

    ret = atomic_fetch_sub(&i, 2);

    if( (i != -4) ||  (ret != -2) )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_atomic_sub_5(struct test_info_t  *test_info)
{

    TEST_INIT;

    int i = 0;
    int ret;


    ret = atomic_fetch_sub(&i, 255);

    if( (i != -255) ||  (ret != 0) )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_atomic_sub_6(struct test_info_t  *test_info)
{

    TEST_INIT;

    int i = -100;
    int ret;


    ret = atomic_fetch_sub(&i, -100);

    if( (i != 0) ||  (ret != -100) )
        return TEST_BROKEN;


    return TEST_PASSED;
}





// -------------------  AND  --------------------

int test_atomic_and_1(struct test_info_t  *test_info)
{

    TEST_INIT;

    unsigned int i = 0;
    unsigned int ret;


    ret = atomic_fetch_and(&i, 1);

    if( (i != 0) ||  (ret != 0) )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_atomic_and_2(struct test_info_t  *test_info)
{

    TEST_INIT;

    unsigned int i = 2;
    unsigned int ret;


    ret = atomic_fetch_and(&i, 2);

    if( (i != 2) ||  (ret != 2) )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_atomic_and_3(struct test_info_t  *test_info)
{

    TEST_INIT;

    unsigned int i = 0xFFFF;
    unsigned int ret;


    ret = atomic_fetch_and(&i, 0xFF);

    if( (i != 0xFF) ||  (ret != 0xFFFF) )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_atomic_and_4(struct test_info_t  *test_info)
{

    TEST_INIT;

    unsigned int i = -1;
    unsigned int ret;


    ret = atomic_fetch_and(&i, 0);

    if( (i != 0) ||  (ret != -1) )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_atomic_and_5(struct test_info_t  *test_info)
{

    TEST_INIT;

    unsigned int i = 0xFFFF;
    unsigned int ret;


    ret = atomic_fetch_and(&i, 0xFF00);

    if( (i != 0xFF00) ||  (ret != 0xFFFF) )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_atomic_and_6(struct test_info_t  *test_info)
{

    TEST_INIT;

    unsigned int i = 0xFFFFAA55;
    unsigned int ret;


    ret = atomic_fetch_and(&i, 0xFFFF5A5A);

    if( (i != 0xFFFF0A50) ||  (ret != 0xFFFFAA55) )
        return TEST_BROKEN;


    return TEST_PASSED;
}





// -------------------  OR  --------------------

int test_atomic_or_1(struct test_info_t  *test_info)
{

    TEST_INIT;

    unsigned int i = 0;
    unsigned int ret;


    ret = atomic_fetch_or(&i, 1);

    if( (i != 1) ||  (ret != 0) )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_atomic_or_2(struct test_info_t  *test_info)
{

    TEST_INIT;

    unsigned int i = 2;
    unsigned int ret;


    ret = atomic_fetch_or(&i, 2);

    if( (i != 2) ||  (ret != 2) )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_atomic_or_3(struct test_info_t  *test_info)
{

    TEST_INIT;

    unsigned int i = 0xFFFF;
    unsigned int ret;


    ret = atomic_fetch_or(&i, 0xFE);

    if( (i != 0xFFFF) ||  (ret != 0xFFFF) )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_atomic_or_4(struct test_info_t  *test_info)
{

    TEST_INIT;

    unsigned int i = -1;
    unsigned int ret;


    ret = atomic_fetch_or(&i, 0);

    if( (i != -1) ||  (ret != -1) )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_atomic_or_5(struct test_info_t  *test_info)
{

    TEST_INIT;

    unsigned int i = 0;
    unsigned int ret;


    ret = atomic_fetch_or(&i, 0xFF00);

    if( (i != 0xFF00) ||  (ret != 0) )
        return TEST_BROKEN;


    ret = atomic_fetch_or(&i, 0x00F0);

    if( (i != 0xFFF0) ||  (ret != 0xFF00) )
        return TEST_BROKEN;



    ret = atomic_fetch_or(&i, 0x000F);

    if( (i != 0xFFFF) ||  (ret != 0xFFF0) )
        return TEST_BROKEN;



    return TEST_PASSED;
}



int test_atomic_or_6(struct test_info_t  *test_info)
{

    TEST_INIT;

    unsigned int i = 0xFFFFAA55;
    unsigned int ret;


    ret = atomic_fetch_or(&i, 0xFFFF5A5A);

    if( (i != 0xFFFFFA5F) ||  (ret != 0xFFFFAA55) )
        return TEST_BROKEN;


    return TEST_PASSED;
}





// -------------------  XOR  --------------------

int test_atomic_xor_1(struct test_info_t  *test_info)
{

    TEST_INIT;

    unsigned int i = 0;
    unsigned int ret;


    ret = atomic_fetch_xor(&i, 1);

    if( (i != 1) ||  (ret != 0) )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_atomic_xor_2(struct test_info_t  *test_info)
{

    TEST_INIT;

    unsigned int i = 1;
    unsigned int ret;


    ret = atomic_fetch_xor(&i, 0);

    if( (i != 1) ||  (ret != 1) )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_atomic_xor_3(struct test_info_t  *test_info)
{

    TEST_INIT;

    unsigned int i = 0xAAAAAAAA;
    unsigned int ret;


    ret = atomic_fetch_xor(&i, 0);

    if( (i != 0xAAAAAAAA) ||  (ret != 0xAAAAAAAA) )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_atomic_xor_4(struct test_info_t  *test_info)
{

    TEST_INIT;

    unsigned int i = 0xAAAAAAAA;
    unsigned int ret;


    ret = atomic_fetch_xor(&i, 0x55555555);

    if( (i != 0xFFFFFFFF) ||  (ret != 0xAAAAAAAA) )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_atomic_xor_5(struct test_info_t  *test_info)
{

    TEST_INIT;

    unsigned int i = 0xFFFFFFFF;
    unsigned int ret;


    ret = atomic_fetch_xor(&i, 0xFFFFFFFF);

    if( (i != 0) ||  (ret != 0xFFFFFFFF) )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_atomic_xor_6(struct test_info_t  *test_info)
{

    TEST_INIT;

    unsigned int i = 0xFFFFFFFF;
    unsigned int ret;


    ret = atomic_fetch_xor(&i, 0x55555555);

    if( (i != 0xAAAAAAAA) ||  (ret != 0xFFFFFFFF) )
        return TEST_BROKEN;


    return TEST_PASSED;
}



ptest_func tests[] =
{

    //add
    test_atomic_add_1,
    test_atomic_add_2,
    test_atomic_add_3,
    test_atomic_add_4,
    test_atomic_add_5,
    test_atomic_add_6,


    //sub
    test_atomic_sub_1,
    test_atomic_sub_2,
    test_atomic_sub_3,
    test_atomic_sub_4,
    test_atomic_sub_5,
    test_atomic_sub_6,


    //and
    test_atomic_and_1,
    test_atomic_and_2,
    test_atomic_and_3,
    test_atomic_and_4,
    test_atomic_and_5,
    test_atomic_and_6,


    //or
    test_atomic_or_1,
    test_atomic_or_2,
    test_atomic_or_3,
    test_atomic_or_4,
    test_atomic_or_5,
    test_atomic_or_6,


    //xor
    test_atomic_xor_1,
    test_atomic_xor_2,
    test_atomic_xor_3,
    test_atomic_xor_4,
    test_atomic_xor_5,
    test_atomic_xor_6,

};



void run_tests(void)
{
    struct test_info_t test_info;
    unsigned int i;

    for(i=0; i < COUNT_ELEMENTS(tests); ++i)
    {

        if( tests[i](&test_info) == TEST_BROKEN)
        {
            printf("test:  %s  in file: %s  is broken\n", test_info.func_name, test_info.file_name);
            exit(1);
        }
    }


    printf("all test passed  count tests = %d\n", COUNT_ELEMENTS(tests));
}



int main(void)
{

    run_tests();

    return 0;
}
