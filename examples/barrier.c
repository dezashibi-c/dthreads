#define _POSIX_C_SOURCE 200112L

#define DTHREAD_IMPL
#include "../dthreads/dthread.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 4

DThreadBarrier barrier;

void* thread_func(void* arg)
{
    intptr_t thread_num = (intptr_t)arg;
    printf("Thread %ld reached the barrier.\n", thread_num);
    dthread_barrier_wait(&barrier);
    printf("Thread %ld passed the barrier.\n", thread_num);
    return NULL;
}

int main()
{
    DThread threads[NUM_THREADS];
    DThreadConfig thread_configs[NUM_THREADS];

    dthread_barrier_init(&barrier, NUM_THREADS);

    for (intptr_t i = 0; i < NUM_THREADS; ++i)
    {
        thread_configs[i] = dthread_config_init(thread_func, i);
        dthread_create(&threads[i], NULL, &thread_configs[i]);
    }

    for (int i = 0; i < NUM_THREADS; ++i)
    {
        dthread_join(threads[i], NULL);
    }

    dthread_barrier_destroy(&barrier);

    return 0;
}
