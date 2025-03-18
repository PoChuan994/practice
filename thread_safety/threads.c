#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define LOOPS 10000000

static int counter = 0;

static void *thread(void *unused)
{
    for (int i=0; i< LOOPS; ++i) {
        ++counter;
    }
    return NULL;
}

int main()
{
    pthread_t t1, t2;

    pthread_create(&t1, NULL, thread, NULL);
    pthread_create(&t2, NULL, thread, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Counter is %d by thread\n", counter);
    return 0;
}
