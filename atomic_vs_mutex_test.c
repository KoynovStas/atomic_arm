#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <pthread.h>
#include <sys/time.h>



#include "atomic_arm.h"





#define  MAX_COUNT_LOOP_ITERATIONS  (100000000)




pthread_t test_threads[2];



static pthread_mutex_t test_mutex = PTHREAD_MUTEX_INITIALIZER;
int test_reg;




void perror_exit(char *error_message)
{
    printf("error: %s\n", error_message);
    exit(EXIT_FAILURE);
}



void* test_mutex_thread1(void *thread_arg)
{

    unsigned int i;

    for(i = 0; i < MAX_COUNT_LOOP_ITERATIONS; i++)
    {
        pthread_mutex_lock(&test_mutex);
        test_reg++;
        pthread_mutex_unlock(&test_mutex);
    }


    return NULL;
}



void* test_mutex_thread2(void *thread_arg)
{

    unsigned int i;

    for(i = 0; i < MAX_COUNT_LOOP_ITERATIONS; i++)
    {
        pthread_mutex_lock(&test_mutex);
        test_reg--;
        pthread_mutex_unlock(&test_mutex);
    }


    return NULL;
}



void* test_atomic_thread1(void *thread_arg)
{

    unsigned int i;

    for(i = 0; i < MAX_COUNT_LOOP_ITERATIONS; i++)
    {
        atomic_fetch_add(&test_reg, 1);
    }


    return NULL;
}



void* test_atomic_thread2(void *thread_arg)
{

    unsigned int i;

    for(i = 0; i < MAX_COUNT_LOOP_ITERATIONS; i++)
    {
        atomic_fetch_sub(&test_reg, 1);
    }


    return NULL;
}



void start_test_threads(void *(*test_thread1)(void *),    void *(*test_thread2)(void *))
{

    if(pthread_create(&test_threads[0], NULL, test_thread1, NULL) != 0)
      perror_exit("Cant create thread1");


    if(pthread_create(&test_threads[1], NULL, test_thread2, NULL) != 0)
      perror_exit("Cant create thread2");


    if(pthread_join(test_threads[0], NULL) != 0)
          perror_exit("Cant join thread1");


    if(pthread_join(test_threads[1], NULL) != 0)
          perror_exit("Cant join thread2");

}



void run_test(void *(*test_thread1)(void *),    void *(*test_thread2)(void *))
{
    unsigned int full_time;
    float delay, speed;
    static struct timespec time_start, time_end;


    //reset shared variable
    test_reg = 0;


    clock_gettime(CLOCK_REALTIME, &time_start);


    //testing routine
    start_test_threads(test_thread1, test_thread2);


    clock_gettime(CLOCK_REALTIME, &time_end);

    full_time = (unsigned int)(time_end.tv_sec-time_start.tv_sec);
    delay     = (float)full_time/(MAX_COUNT_LOOP_ITERATIONS*2);
    speed     = 1.0/delay;


    printf("time  = %u\n", full_time);
    printf("delay = %e\n", delay);
    printf("speed = %f\n", speed);


    // check test_reg
    // test_reg must be is 0
    if(test_reg == 0)
        printf("Test is passed (test_reg is 0)\n\n");
    else
        printf("Test is broken (test_reg must be is 0, but is %d\n\n", test_reg);
}



int main(void)
{


    printf("run mutex test threads, wait...\n\n");
    run_test(test_mutex_thread1, test_mutex_thread2);


    printf("run atomic test threads, wait...\n\n");
    run_test(test_atomic_thread1, test_atomic_thread2);


    return 0; //good job
}
