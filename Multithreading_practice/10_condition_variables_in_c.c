#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

//A condition variable is an identifier for a certain signal that you could either signal or wait on
//You are signaling that the condition's result might have changed

// The condition variable comes with mainly 3 operations that you can do on it:
// 1)pthread_cond_wait
// 2)pthread_cond_broadcast
// 3)pthread_broad_signal

pthread_mutex_t mutexFuel;
pthread_cond_t condFuel;
int fuel = 0;

void* fuel_filling(void *arg)
{
    //printf("Filling fuel\n");
    for (int i = 0; i < 5; i++)
    {
        pthread_mutex_lock(&mutexFuel);
        fuel += 15;
        printf("Filled fuel... %d\n", fuel);
        pthread_mutex_unlock(&mutexFuel);
        //once we've done filling the fuel we can send a signal
        //it says to all the threads that are waiting on this condition, to continue execution
        pthread_cond_signal(&condFuel);
        sleep(1);
    }
    return (NULL);
}

void* car(void *arg)
{
    //printf("Here to get fuel\n");
    pthread_mutex_lock(&mutexFuel);
    //important to have it in a while loop
    //the condition itself is not contained in the condition variable, its contained in the while loop itself
    while(fuel < 40)
    {
        printf("No fuel. Wait...\n");
        //waits for a signal from another thread that may or may not change the condition
        pthread_cond_wait(&condFuel, &mutexFuel);
        // Equivalent to:
        // pthread_mutex_unlock(&mutexFuel);
        // wait for signal on condFuel
        // pthread_mutex_lock(&mutexFuel);
    }
    fuel -= 40;
    printf("Got fuel. Now left: %d\n", fuel);
    pthread_mutex_unlock(&mutexFuel);
    return (NULL);
}

int main(int argc, char *argv[])
{
    pthread_t th[2];
    pthread_mutex_init(&mutexFuel, NULL);
    pthread_cond_init(&condFuel, NULL);
    for (int i = 0; i < 2; i++)
    {
        if (i == 1){
            if(pthread_create(&th[i], NULL, &fuel_filling, NULL) != 0){
                perror("Failed to create  thread");
            }
        } else {
            if(pthread_create(&th[i], NULL, &car, NULL) != 0){
                perror("Failed to create  thread");
            }
        }
    }

    for (int i = 0; i < 2; i++){
        if (pthread_join(th[i], NULL) != 0){
            perror("Failed to join thread");
        }
    }
    pthread_mutex_destroy(&mutexFuel);
    pthread_cond_destroy(&condFuel);
    return 0;
}