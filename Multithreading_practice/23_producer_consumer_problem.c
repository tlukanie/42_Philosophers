#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <semaphore.h>

//BUS error!!! Doesn't function properly

//creating one producer and one consumer
#define THREAD_NUM 8

//we can have two semaphores:
//1) that stores the empty slots in the buffer
//2)stores the number of full slots in the buffer
sem_t semEmpty;
sem_t semFull;

//to stop the rac e conditions, when one thread is trying to increment count and another thread decremets it at the same time
pthread_mutex_t mutexBuffer;

int buffer[10];
int count = 0;

//The idea of the producer-consumer program is that we have a shared buffer
//so that a buffer that is in shared memory between multiple threads
//Problems that we need to solve:
//1) Manage shared memory access (make sure that we don't have any race conditions, probably by using mutex)
//2) Checking for if buffer is full (if you have two producers and one consumer, you'll have many more items in the buffer 
//than the consumer can take from it)
//3) Checking for if buffer is empty (if consumer tries to take an item from an empty buffer)


//the program will have producers that produce random numbers
//and consumers that consume the numbers and they just print it on the screeen

void* producer(void* args){
    //the producers and the consumers are usually processes that are long running
    //the producer keeps producing things, like the browser keeps producing requests to the server
    //and servers are always there to actually accept those requests
    while (1){
        //produce step
        int x = rand() % 100;
        sleep(1);

        sem_wait(&semEmpty);
        pthread_mutex_lock(&mutexBuffer);
        //add to the buffer
        buffer[count] = x;
        count++;
        pthread_mutex_unlock(&mutexBuffer);
        sem_post(&semFull);
    }
    return (NULL);
}

void* consumer(void* args){
    while(1)
    {
        int y;

        sem_wait(&semFull);
        pthread_mutex_lock(&mutexBuffer);
        //remove element from the buffer
        //the buffer will be used as a stack: first in last out
        y = buffer[count - 1];
        count--;
        pthread_mutex_unlock(&mutexBuffer);
        sem_post(&semEmpty);

        // consume (just printing to the screen)
        printf("Got %d\n", y);
        sleep(1);
    }
    return (NULL);
}

int main(int argc, char* argv[]){
    srand(time(NULL));
    pthread_t th[THREAD_NUM];
    pthread_mutex_init(&mutexBuffer, NULL);
    sem_init(&semEmpty, 0, 10);
    sem_init(&semFull, 0, 0);
    int i;
    for (i = 0; i < THREAD_NUM; i++)
    {
        //half of the threads will be producers, and another half - consumers
        if (i > 0){
            if (pthread_create(&th[i], NULL, &producer, NULL) != 0){
                perror("Failed to create thread");
            }
        } else { //only one consumer
            if (pthread_create(&th[i], NULL, &consumer, NULL) != 0){
                perror("Failed to create thread");
            }
        }
    }
    for (i = 0; i < THREAD_NUM; i++)
    {
        if (pthread_join(th[i], NULL) != 0){
            perror("Failed to join thread");
        }
    }
    sem_destroy(&semEmpty);
    sem_destroy(&semFull);
    pthread_mutex_destroy(&mutexBuffer);
    return 0;
}