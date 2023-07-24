#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>

#define THREAD_NUM 8

//this mutex can only be locked and then unlocked by the same thread
//you cannot have it locked once by a thread and unlocked by another thread which we could have with semaphores
pthread_mutex_t mutexFuel;
int fuel = 50;

//with recursive locks you're gonna have to always unlock the mutex the same 
//number of times you have locked it
//otherwise the code is not gonna be valid or gonna create a deadlock
//it only applies to the same thread
//there should be the same number of unlocks as locks in the same thread


void* routine(void* args){
    //we can lock the same mutex in the same thread multiple times without getting a deadlock
    //but we have to set some attributes to the mutex itself
    pthread_mutex_lock(&mutexFuel);
    pthread_mutex_lock(&mutexFuel);
    fuel += 50;
    printf("Incremented fuel to: %d\n", fuel);
    pthread_mutex_unlock(&mutexFuel);
    pthread_mutex_unlock(&mutexFuel);
    return (NULL);
}

int main(int argc, char *argv[])
{
    pthread_t th[THREAD_NUM];
    //a mutex that can be locked multiple times inside of thread is called a recursive mutex
    pthread_mutexattr_t recursiveMutexAttributes;
    //to set it recursive
    pthread_mutexattr_init(&recursiveMutexAttributes);
    pthread_mutexattr_settype(&recursiveMutexAttributes, PTHREAD_MUTEX_RECURSIVE);
    //pass &recursiveMutexAttributes as the second parameter as well
    pthread_mutex_init(&mutexFuel, &recursiveMutexAttributes);
    int i;
    for (i = 0; i < THREAD_NUM; i++) {
        if (pthread_create(&th[i], NULL, &routine, NULL) != 0) {
            perror("Failed to create thread");
        }
    }

    for (i = 0; i < THREAD_NUM; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }
    printf("Fuel: %d\n", fuel);
    pthread_mutexattr_destroy(&recursiveMutexAttributes);
    pthread_mutex_destroy(&mutexFuel);
    return (0);
}