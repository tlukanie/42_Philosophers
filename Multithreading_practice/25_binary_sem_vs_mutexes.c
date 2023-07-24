#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <semaphore.h>

#define THREAD_NUM 4

//mutexes have a concept of ownership:
//whenever a thread is locking that mutex - the mutex expects the unlock by the same thread
//if it's not - then the undefined behaviour occurrs
//with semaphores you can sem_wait in one thread and sem_post in another without any issues

sem_t semFuel;
pthread_mutex_t mutexFuel;
int fuel = 50;

void* routine1(void* args){
    while(1){
        pthread_mutex_lock(&mutexFuel);
        //instead
        //sem_wait(&semFuel);
        fuel += 50;
        printf("Current value is %d\n", fuel);
        //pthread_mutex_unlock(&mutexFuel);
        //instead
        //sem_post(&semFuel);
    }
    return (NULL);
}

void* routine2(void* args){
    while(1){
        //sem_post(&semFuel);
        //with mutexes we will face undefined behaviour
        //use semaphores instead
        pthread_mutex_unlock(&mutexFuel);
        usleep(5000);
    }
    return (NULL);
}

int main(int argc, char *argv[])
{
    pthread_t th[THREAD_NUM];
    pthread_mutex_init(&mutexFuel, NULL);
    sem_init(&semFuel, 0, 1);
    int i;
    for (i = 0; i < THREAD_NUM; i++) {
        if (i % 2 == 0){
            if (pthread_create(&th[i], NULL, &routine1, NULL) != 0) {
                perror("Failed to create thread");
            }
        } else {
            if (pthread_create(&th[i], NULL, &routine2, NULL) != 0) 
                perror("Failed to create thread");
        }
    }
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