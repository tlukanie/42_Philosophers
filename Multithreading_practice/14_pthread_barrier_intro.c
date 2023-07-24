// pthread barriers are not implemented in OS X, which is supposedly POSIX compliant.
// So to get my application to compile, I found an implementation of barriers using other pthread features.
//Paste the following into a file and include it in your Mac OS X code that uses pthread barriers:

#ifdef __APPLE__

#ifndef PTHREAD_BARRIER_H_
#define PTHREAD_BARRIER_H_

#include <pthread.h>
#include <errno.h>

typedef int pthread_barrierattr_t;
typedef struct
{
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int count;
    int tripCount;
} pthread_barrier_t;


int pthread_barrier_init(pthread_barrier_t *barrier, const pthread_barrierattr_t *attr, unsigned int count)
{
    if(count == 0)
    {
        errno = EINVAL;
        return -1;
    }
    if(pthread_mutex_init(&barrier->mutex, 0) < 0)
    {
        return -1;
    }
    if(pthread_cond_init(&barrier->cond, 0) < 0)
    {
        pthread_mutex_destroy(&barrier->mutex);
        return -1;
    }
    barrier->tripCount = count;
    barrier->count = 0;

    return 0;
}

int pthread_barrier_destroy(pthread_barrier_t *barrier)
{
    pthread_cond_destroy(&barrier->cond);
    pthread_mutex_destroy(&barrier->mutex);
    return 0;
}

int pthread_barrier_wait(pthread_barrier_t *barrier)
{
    pthread_mutex_lock(&barrier->mutex);
    ++(barrier->count);
    if(barrier->count >= barrier->tripCount)
    {
        barrier->count = 0;
        pthread_cond_broadcast(&barrier->cond);
        pthread_mutex_unlock(&barrier->mutex);
        return 1;
    }
    else
    {
        pthread_cond_wait(&barrier->cond, &(barrier->mutex));
        pthread_mutex_unlock(&barrier->mutex);
        return 0;
    }
}

#endif // PTHREAD_BARRIER_H_
#endif // __APPLE__

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
//#include <pthread_barrier.h>

/****************************************/
//barriers are a nice way to control the execution flow of the multiple threads

//barrier usually waits for multiple threads to wait for that barrier object until it lets
//multiple threads pass
//the idea of a barrier is as follows:
//barrier will stop the execution of the threads until the certain amount of threads

//creating a barrier object
pthread_barrier_t barrier;

void* routine(void* args){
    while(1) {
    printf("Waiting at the barrier...\n");
    sleep(1);
    pthread_barrier_wait(&barrier);
    printf("We passed the barrier\n");
    sleep(1);
    }
    return (NULL);
}

int main(int argc, char *argv[])
{
    pthread_t th[9];
    int i;
    pthread_barrier_init(&barrier, NULL, 7);
    for (i = 0; i < 9; i++){
        if (pthread_create(&th[i], NULL, &routine, NULL) != 0) {
            perror("Failed tp create thread");
        }
    }
    for (i = 0; i < 9; i++) {
        if (pthread_join(th[i], NULL) != 0){
            perror("Failed to join thread");
        }
    }
    pthread_barrier_destroy(&barrier);
    return 0;
}
