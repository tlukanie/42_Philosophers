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
#include <time.h>

#define THREAD_NUM 8

// Problem:
// Every thread rolls a dice, saved its value in an array
// The main thread calculates the winner then
// Each thread prints a message with whether or not they lost or won

int diceValues[8];
//will denote in the main thread whether or not the thread won or lost
int status[8] = { 0 };

pthread_barrier_t barrierRolledDice;
pthread_barrier_t barrierCalculated;

void* rollDice(void* args){
    int index = *(int*)args;
    while(1)
    {
        diceValues[index] = rand() % 6 + 1;
        pthread_barrier_wait(&barrierRolledDice);
        pthread_barrier_wait(&barrierCalculated);
        if (status[index] == 1){
            printf("(%d rolled %d) I won\n", index, diceValues[index]);
        } else {
            printf("(%d rolled %d) I lost\n", index, diceValues[index]);
        }
    }
    free(args);
    return (NULL);
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    pthread_t th[THREAD_NUM];
    pthread_barrier_init(&barrierRolledDice, NULL, THREAD_NUM + 1);
    pthread_barrier_init(&barrierCalculated, NULL, THREAD_NUM + 1);
    int i;
    for (i = 0; i < THREAD_NUM; i++){
        int* a = malloc(sizeof(int));
        *a = i;
        if (pthread_create(&th[i], NULL, &rollDice, a) != 0) {
            perror("Failed to create thread");
        }
    }
    while(1){
        pthread_barrier_wait(&barrierRolledDice);
        //Calculate the winner
        int max = 0;
        for(i = 0; i < THREAD_NUM; i++){
            if (diceValues[i] > max) {
                max = diceValues[i];
            }
        }

        for (i = 0; i < THREAD_NUM; i++)
        {
            if (diceValues[i] == max) {
                status[i] = 1;
            } else {
                status[i] = 0;
            }
        }
    printf("==== NEW ROUND STARTED ====\n");
    sleep(1);
    pthread_barrier_wait(&barrierCalculated);
    }
    for (i = 0; i < THREAD_NUM; i++){
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }
    pthread_barrier_destroy(&barrierRolledDice);
    pthread_barrier_destroy(&barrierCalculated);
    return 0;
}