#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define LOOPS 10000000

static int counter = 0;
pthread_mutex_t lock;    /* Declare a mutex lock */

static void *thread(void *unused)
{
    for (int i = 0; i < LOOPS; ++i) {
        pthread_mutex_lock(&lock);    /* Obtain the lock */
        ++counter;
        pthread_mutex_unlock(&lock);    /* release the lock */
    }
    return NULL;
}

int main()
{
    pthread_t t1, t2;
    pthread_mutex_init(&lock, NULL);    /* Initialize the mutex lock */

    pthread_create(&t1, NULL, thread, NULL);
    pthread_create(&t2, NULL, thread, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Counter is %d by thread\n", counter);
    pthread_mutex_destroy(&lock);   /* Destroy the lock */
    return 0;
}
