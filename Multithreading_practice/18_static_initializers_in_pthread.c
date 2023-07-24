#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>

#define THREAD_NUM 2

//the static initializers are simply just some static values that you can assign right on definition of that mutex field

pthread_mutex_t mutexFuel = PTHREAD_MUTEX_INITIALIZER; //macro mfor some default value
//lets not to use init function anymore
pthread_cond_t condFuel = PTHREAD_COND_INITIALIZER;
//there are no initializers for barriers

void* routine(void* args){
    
    return (NULL);
}

int main(int argc, char *argv[])
{
    pthread_t th[THREAD_NUM];
    //pthread_mutex_init(&mutexFuel, NULL);
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
    //pthread_mutex_destroy(&mutexFuel);
    return (0);
}