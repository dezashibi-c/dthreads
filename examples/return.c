// ***************************************************************************************
//    Project: dthreads -> https://github.com/dezashibi-c/dthreads
//    File: return.c
//    Date: 2024-08-14
//    Author: Navid Dezashibi
//    Contact: navid@dezashibi.com
//    Website: https://www.dezashibi.com | https://github.com/dezashibi
//    License:
//     -> THIS EXAMPLE IS BASED ON A SIMILAR EXAMPLE FROM https://code-vault.net
//     Please refer to the LICENSE file, repository or website for more information about
//     the licensing of this work. If you have any questions or concerns,
//     please feel free to contact me at the email address provided above.
// ***************************************************************************************
// *  Description: Refer to readme for documentation or dthread.h
// ***************************************************************************************

#define DTHREAD_DEBUG
#define DTHREAD_IMPL
#include "../dthreads/dthread.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

dthread_define_routine(roll_dice)
{
    (void)data;

    dthread_rng_seed_maker();

    int value = (dthread_rng_random() % 6) + 1;
    int* result = malloc(sizeof(int));
    if (result == NULL)
    {
        fprintf(stderr, "Memory allocation failed in roll_dice\n");
        dthread_exit(NULL);
    }

    *result = value;

    printf("Thread result: %p\n", (void*)result);
    return (void*)result;
}

int main(void)
{
    dthread_rng_init();

    DThread thread = dthread_init_thread(roll_dice, NULL);

    if (dthread_create(&thread, NULL) != 0)
    {
        fprintf(stderr, "Thread create failed\n");
        return 1;
    }

    if (dthread_join(&thread) != 0)
    {
        fprintf(stderr, "Thread join failed\n");
        return 2;
    }

    printf("Main res: %p\n", dthread_get_result(&thread));
    printf("Result: %d\n", *dthread_get_result_as(&thread, int*));

    free(dthread_get_result(&thread));

    dthread_rng_cleanup();

    return 0;
}
