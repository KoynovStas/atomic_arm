#include <stdio.h>
#include <stdlib.h>


#include "atomic_arm.h"
#include "stest.h"





// --------------   ADD  ------------------------


TEST(test_atomic_add_1)
{
    int i = 0;
    int ret;


    ret = atomic_fetch_add(&i, 1);

    TEST_ASSERT( (i == 1) && (ret == 0) );


    TEST_PASS(NULL);
}



TEST(test_atomic_add_2)
{
    int i = 0;
    int ret;

    ret = atomic_fetch_add(&i, 2);

    TEST_ASSERT( (i == 2) && (ret == 0) );


    TEST_PASS(NULL);
}



TEST(test_atomic_add_3)
{
    int i = 0;
    int ret;

    ret = atomic_fetch_add(&i, -2);

    TEST_ASSERT( (i == -2) && (ret == 0) );


    TEST_PASS(NULL);
}



TEST(test_atomic_add_4)
{
    int i = -2;
    int ret;

    ret = atomic_fetch_add(&i, 2);

    TEST_ASSERT( (i == 0) && (ret == -2) );


    TEST_PASS(NULL);
}



TEST(test_atomic_add_5)
{
    int i = 0;
    int ret;

    ret = atomic_fetch_add(&i, 0xFFFFFF);

    TEST_ASSERT( (i == 0xFFFFFF) && (ret == 0) );


    TEST_PASS(NULL);
}



TEST(test_atomic_add_6)
{
    int i = 0;
    int ret;

    ret = atomic_fetch_add(&i, 0);

    TEST_ASSERT( (i == 0) && (ret == 0) );


    TEST_PASS(NULL);
}



// -------------------  SUB  --------------------



TEST(test_atomic_sub_1)
{
    int i = 0;
    int ret;

    ret = atomic_fetch_sub(&i, 1);

    TEST_ASSERT( (i == -1) && (ret == 0) );


    TEST_PASS(NULL);
}



TEST(test_atomic_sub_2)
{
    int i = 0;
    int ret;

    ret = atomic_fetch_sub(&i, 2);

    TEST_ASSERT( (i == -2) && (ret == 0) );


    TEST_PASS(NULL);
}



TEST(test_atomic_sub_3)
{
    int i = 0;
    int ret;

    ret = atomic_fetch_sub(&i, -2);

    TEST_ASSERT( (i == 2) && (ret == 0) );


    TEST_PASS(NULL);
}



TEST(test_atomic_sub_4)
{
    int i = -2;
    int ret;

    ret = atomic_fetch_sub(&i, 2);

    TEST_ASSERT( (i == -4) && (ret == -2) );


    TEST_PASS(NULL);
}



TEST(test_atomic_sub_5)
{
    int i = 0;
    int ret;


    ret = atomic_fetch_sub(&i, 255);

    TEST_ASSERT( (i == -255) && (ret == 0) );


    TEST_PASS(NULL);
}



TEST(test_atomic_sub_6)
{
    int i = -100;
    int ret;


    ret = atomic_fetch_sub(&i, -100);

    TEST_ASSERT( (i == 0) && (ret == -100) );


    TEST_PASS(NULL);
}


// -------------------  AND  --------------------


TEST(test_atomic_and_1)
{
    unsigned int i = 0;
    unsigned int ret;

    ret = atomic_fetch_and(&i, 1);

    TEST_ASSERT( (i == 0) && (ret == 0) );


    TEST_PASS(NULL);
}



TEST(test_atomic_and_2)
{
    unsigned int i = 2;
    unsigned int ret;

    ret = atomic_fetch_and(&i, 2);

    TEST_ASSERT( (i == 2) && (ret == 2) );


    TEST_PASS(NULL);
}



TEST(test_atomic_and_3)
{
    unsigned int i = 0xFFFF;
    unsigned int ret;

    ret = atomic_fetch_and(&i, 0xFF);

    TEST_ASSERT( (i == 0xFF) && (ret == 0xFFFF) );


    TEST_PASS(NULL);
}



TEST(test_atomic_and_4)
{
    unsigned int i = -1;
    unsigned int ret;

    ret = atomic_fetch_and(&i, 0);

    TEST_ASSERT( (i == 0) && (ret == -1) );


    TEST_PASS(NULL);
}



TEST(test_atomic_and_5)
{
    unsigned int i = 0xFFFF;
    unsigned int ret;

    ret = atomic_fetch_and(&i, 0xFF00);

    TEST_ASSERT( (i == 0xFF00) && (ret == 0xFFFF) );


    TEST_PASS(NULL);
}



TEST(test_atomic_and_6)
{
    unsigned int i = 0xFFFFAA55;
    unsigned int ret;

    ret = atomic_fetch_and(&i, 0xFFFF5A5A);

    TEST_ASSERT( (i == 0xFFFF0A50) && (ret == 0xFFFFAA55) );


    TEST_PASS(NULL);
}


// -------------------  OR  --------------------


TEST(test_atomic_or_1)
{
    unsigned int i = 0;
    unsigned int ret;

    ret = atomic_fetch_or(&i, 1);

    TEST_ASSERT( (i == 1) && (ret == 0) );


    TEST_PASS(NULL);
}



TEST(test_atomic_or_2)
{
    unsigned int i = 2;
    unsigned int ret;

    ret = atomic_fetch_or(&i, 2);

    TEST_ASSERT( (i == 2) && (ret == 2) );


    TEST_PASS(NULL);
}



TEST(test_atomic_or_3)
{
    unsigned int i = 0xFFFF;
    unsigned int ret;

    ret = atomic_fetch_or(&i, 0xFE);

    TEST_ASSERT( (i == 0xFFFF) && (ret == 0xFFFF) );


    TEST_PASS(NULL);
}



TEST(test_atomic_or_4)
{
    unsigned int i = -1;
    unsigned int ret;

    ret = atomic_fetch_or(&i, 0);

    TEST_ASSERT( (i == -1) && (ret == -1) );


    TEST_PASS(NULL);
}



TEST(test_atomic_or_5)
{
    unsigned int i = 0;
    unsigned int ret;

    ret = atomic_fetch_or(&i, 0xFF00);

    TEST_ASSERT( (i == 0xFF00) && (ret == 0) );


    ret = atomic_fetch_or(&i, 0x00F0);

    TEST_ASSERT( (i == 0xFFF0) && (ret == 0xFF00) );


    ret = atomic_fetch_or(&i, 0x000F);

    TEST_ASSERT( (i == 0xFFFF) && (ret == 0xFFF0) );



    TEST_PASS(NULL);
}



TEST(test_atomic_or_6)
{
    unsigned int i = 0xFFFFAA55;
    unsigned int ret;

    ret = atomic_fetch_or(&i, 0xFFFF5A5A);

    TEST_ASSERT( (i == 0xFFFFFA5F) && (ret == 0xFFFFAA55) );


    TEST_PASS(NULL);
}


// -------------------  XOR  --------------------


TEST(test_atomic_xor_1)
{
    unsigned int i = 0;
    unsigned int ret;

    ret = atomic_fetch_xor(&i, 1);

    TEST_ASSERT( (i == 1) && (ret == 0) );


    TEST_PASS(NULL);
}



TEST(test_atomic_xor_2)
{
    unsigned int i = 1;
    unsigned int ret;

    ret = atomic_fetch_xor(&i, 0);

    TEST_ASSERT( (i == 1) && (ret == 1) );


    TEST_PASS(NULL);
}



TEST(test_atomic_xor_3)
{
    unsigned int i = 0xAAAAAAAA;
    unsigned int ret;

    ret = atomic_fetch_xor(&i, 0);

    TEST_ASSERT( (i == 0xAAAAAAAA) && (ret == 0xAAAAAAAA) );


    TEST_PASS(NULL);
}



TEST(test_atomic_xor_4)
{
    unsigned int i = 0xAAAAAAAA;
    unsigned int ret;


    ret = atomic_fetch_xor(&i, 0x55555555);

    TEST_ASSERT( (i == 0xFFFFFFFF) && (ret == 0xAAAAAAAA) );


    TEST_PASS(NULL);
}



TEST(test_atomic_xor_5)
{
    unsigned int i = 0xFFFFFFFF;
    unsigned int ret;


    ret = atomic_fetch_xor(&i, 0xFFFFFFFF);

    TEST_ASSERT( (i == 0) && (ret == 0xFFFFFFFF) );


    TEST_PASS(NULL);
}



TEST(test_atomic_xor_6)
{
    unsigned int i = 0xFFFFFFFF;
    unsigned int ret;


    ret = atomic_fetch_xor(&i, 0x55555555);

    TEST_ASSERT( (i == 0xAAAAAAAA) && (ret == 0xFFFFFFFF) );


    TEST_PASS(NULL);
}


// -------------------  exchange  --------------------


TEST(test_atomic_exchange_1)
{
    int i = 0;
    int ret;


    ret = atomic_exchange(&i, 1);

    TEST_ASSERT( (i == 1) && (ret == 0) );


    TEST_PASS(NULL);
}



TEST(test_atomic_exchange_2)
{
    int i = 0;
    int ret;


    ret = atomic_exchange(&i, -1);

    TEST_ASSERT( (i == -1) && (ret == 0) );


    TEST_PASS(NULL);
}



TEST(test_atomic_exchange_3)
{
    int i = 0xAAAAAAAA;
    int ret;


    ret = atomic_exchange(&i, 0x55555555);

    TEST_ASSERT( (i == 0x55555555) && (ret == 0xAAAAAAAA) );


    TEST_PASS(NULL);
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


    //exchange
    test_atomic_exchange_1,
    test_atomic_exchange_2,
    test_atomic_exchange_3,
};



MAIN_TESTS(tests)
