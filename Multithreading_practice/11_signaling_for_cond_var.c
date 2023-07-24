#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

//pthread_cond_signal vs pthread_cond_broadcast

//pthread_cond_signal(&condFuel) signals only to one thr

pthread_mutex_t mutexFuel;
pthread_cond_t condFuel;
int fuel = 0;

void* fuel_filling(void *arg)
{
    for (int i = 0; i < 5; i++)
    {
        pthread_mutex_lock(&mutexFuel);
        fuel += 30;
        printf("Filled fuel... %d\n", fuel);
        pthread_mutex_unlock(&mutexFuel);
        //shoud use broadcast instead of signal if you want all the threads that are waiting on that condition to awaken
        //to restart executing and check the condition
        pthread_cond_broadcast(&condFuel);
        sleep(1);
    }
    return (NULL);
}

void* car(void *arg)
{
    pthread_mutex_lock(&mutexFuel);
    //can't execute the condition inseide of the while loop for multithreaded programm
    while(fuel < 40)
    {
        printf("No fuel. Wait...\n");
        pthread_cond_wait(&condFuel, &mutexFuel);
    }
    fuel -= 40;
    printf("Got fuel. Now left: %d\n", fuel);
    pthread_mutex_unlock(&mutexFuel);
    return (NULL);
}

int main(int argc, char *argv[])
{
    pthread_t th[6];
    pthread_mutex_init(&mutexFuel, NULL);
    pthread_cond_init(&condFuel, NULL);
    for (int i = 0; i < 6; i++)
    {
        if (i == 4 || i == 5){
            if(pthread_create(&th[i], NULL, &fuel_filling, NULL) != 0){
                perror("Failed to create  thread");
            }
        } else {
            if(pthread_create(&th[i], NULL, &car, NULL) != 0){
                perror("Failed to create  thread");
            }
        }
    }

    for (int i = 0; i < 6; i++){
        if (pthread_join(th[i], NULL) != 0){
            perror("Failed to join thread");
        }
    }
    pthread_mutex_destroy(&mutexFuel);
    pthread_cond_destroy(&condFuel);
    return 0;
}

// Basically this order of execution ocurred:
// car1: lock -> cond_wait -> unlock
// car2: lock -> cond_wait -> unlock
// fueler1: lock
// car3: lock(waiting on lock)
// car4: lock(waiting on lock)