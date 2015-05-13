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



ptest_func tests[] =
{

    //add
    test_atomic_add_1,
    test_atomic_add_2,
    test_atomic_add_3,
    test_atomic_add_4,
    test_atomic_add_5,
    test_atomic_add_6,

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
