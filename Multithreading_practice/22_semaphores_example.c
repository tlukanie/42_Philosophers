#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <semaphore.h>

#define THREAD_NUM 16

/* ================== LOGIN QUEUES ==================
Login Queues are usually used in server side software systems that have limited total resources and 
Quality of Service parameters mandate that the user is allocated atleast a certain amount of resources on the server 
to have an acceptable user experience.
Example: In case of an online game, each user needs a certain amount of CPU cycles and 
memory space to have an acceptable user experience (like no lag). 
So game servers implement a queue so that too many users don't choke up the server resulting in 
a bad use experience for all the users. So if the authentication system simply sets a "is-loggedin" flag 
after validating your credentials then the total number of concurrent users will not be capped resulting in degraded performance for the users.
In enterprise systems, such mechanisms are used for heavy on-demand resources like remote desktops, etc.
*/

//defining a variable
sem_t semaphore;

void* routine(void* args){
    printf("(%d) Waiting in the login queue\n", *(int*)args);
    //acts like mutex
    sem_wait(&semaphore);
    printf("(%d) Logged in\n", *(int*)args);
    sleep(rand() % 5 + 1);
    printf("(%d) Logged out\n", *(int*)args);
    sem_post(&semaphore);
    free(args);
    return (NULL);
}

//semaphores are used for limiting access to a resource
//here the resourse is our "server"
//the semaphore was limiting users to connect to or use this resourse at the same time

int main(int argc, char *argv[])
{
    pthread_t th[THREAD_NUM];
    //initializing a semaphore
    //the third parameter is the initial value of the semaphore (number of threads executed at the same time)
    sem_init(&semaphore, 0, 32);
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