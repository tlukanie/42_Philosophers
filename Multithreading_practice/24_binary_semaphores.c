/*
Semaphores are one of the easiest and best process synchronization mechanisms founded by Dijkstra in the mid-’90s. 
Binary Semaphore provides mutual synchronization between the processes in an operating system.
It has an integer range of values from 0 to 1. 
Basically, Binary Semaphores have two operations namely wait(P) and signal(V) operations. 
Both operations are atomic. Semaphore(s) can be initialized to zero or one. 
Here atomic means that the variable on which read, modify, and update happens at the same time/moment with no pre-emption.
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <semaphore.h>

#define THREAD_NUM 1


sem_t semFuel;
pthread_mutex_t mutexFuel;
int *fuel;

void* routine(void* args){
    //instead of locking with mutexes
    *fuel += 50;
    printf("Current value is %d\n", *fuel);
    //sem_post(&semFuel);
    return (NULL);
}

int main(int argc, char *argv[])
{
    pthread_t th[THREAD_NUM];
    fuel = malloc(sizeof(int));
    *fuel = 50;
    pthread_mutex_init(&mutexFuel, NULL);
    sem_init(&semFuel, 0, 0);
    int i;
    for (i = 0; i < THREAD_NUM; i++) {
        if (pthread_create(&th[i], NULL, &routine, NULL) != 0) {
            perror("Failed to create thread");
        }
    }
    //sem_wait(&semFuel);
    //current value after dealloctaion is 100, not 50 like in video!!!
    printf("Deallocating fuel\n");
    free(fuel);
    for (i = 0; i < THREAD_NUM; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }
    //printf("Fuel: %d\n", *fuel);
    pthread_mutex_destroy(&mutexFuel);
    sem_destroy(&semFuel);
    return (0);
}