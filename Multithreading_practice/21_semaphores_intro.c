#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <semaphore.h>

#define THREAD_NUM 4

//with mutexes we can only lock a mutex in one single thread, you could lock it twice
// in the same thread, but you can't lock it twice on different threads - the very basic 
//difference betweeen semaphores and mutexes


//there are two operations that you can do on a semaphore inside the thread: wait and post
//wait similar to lock in a mutex 
//post similar to unlock


//sem_wait is going to check the semaphores value, if it is 0 and it can no longer be decremented,
//then the thread itself is going to wait on that semaphore
//if it's higher than 0, then it's gonna just decrement it and not wait, just start executing the next lines of code
//sem_post does the reverse, instead of decremeting, it increments

//idea of semaphore: you have an integer and you either decrement that integer or increment it and if it's at zero you're
//gonna have to wait on it

//defining a variable
sem_t semaphore;

void* routine(void* args){
    //acts like mutex
    sem_wait(&semaphore);
    sleep(1);
    printf("Hello from thread %d\n", *(int*)args);
    sem_post(&semaphore);
    free(args);
    return (NULL);
}

int main(int argc, char *argv[])
{
    pthread_t th[THREAD_NUM];
    //initializing a semaphore
    //in second parameter if you have only multiple threads then you should pass 0
    //if you use the multiple processes it will be more than 0
    //the third parameter is the initial value of the semaphore (number of threads executed at the same time)
    sem_init(&semaphore, 0, 4);
    int i;
    for (i = 0; i < THREAD_NUM; i++) {
        int* a = malloc(sizeof(int));
        *a = i;
        if (pthread_create(&th[i], NULL, &routine, a) != 0) {
            perror("Failed to create thread");
        }
    }

    for (i = 0; i < THREAD_NUM; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }
    sem_destroy(&semaphore);
    return (0);
}