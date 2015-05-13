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






ptest_func tests[] =
{


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
