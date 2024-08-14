// ***************************************************************************************
//    Project: dthreads -> https://github.com/dezashibi-c/dthreads
//    File: barrier.c
//    Date: 2024-08-14
//    Author: Navid Dezashibi
//    Contact: navid@dezashibi.com
//    Website: https://www.dezashibi.com | https://github.com/dezashibi
//    License:
//     Please refer to the LICENSE file, repository or website for more information about
//     the licensing of this work. If you have any questions or concerns,
//     please feel free to contact me at the email address provided above.
// ***************************************************************************************
// *  Description: Refer to readme for documentation or dthreads.h
// ***************************************************************************************

#define DTHREAD_IMPL
#include "../dthreads/dthread.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 4

DThreadBarrier barrier;

dthread_define_routine(thread_func)
{
    intptr_t thread_num = (intptr_t)arg;

    printf("Thread %zu reached the barrier.\n", thread_num);

    dthread_barrier_wait(&barrier);

    printf("Thread %zu passed the barrier.\n", thread_num);

    return NULL;
}

int main(void)
{
    DThread threads[NUM_THREADS];
    DThreadConfig thread_configs[NUM_THREADS];

    // Initialize barrier
    dthread_barrier_init(&barrier, NUM_THREADS);

    // Create threads
    for (intptr_t i = 0; i < NUM_THREADS; ++i)
    {
        thread_configs[i] = dthread_config_init(thread_func, i);
        dthread_create(&threads[i], NULL, &thread_configs[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; ++i)
    {
        dthread_join(threads[i], NULL);
    }

    // Cleanup barrier
    dthread_barrier_destroy(&barrier);

    return 0;
}
