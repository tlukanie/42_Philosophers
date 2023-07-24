#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <sys/syscall.h>

#define THREAD_NUM 2

// You can detach threads from the main thread

// The reason for using pthread_attr_t is usually because that there might be the case
// where the thread would finish its execution right in between calling pthread_create and pthread_detach
// therefore the resources wouldn't be freed automatically because it finished execution and wasn't joined
// and it wasn't in a detached state

void* routine(void* args){
    sleep(1);
    printf("Finished execution\n");
    return (NULL);
}

int main(int argc, char *argv[])
{
    pthread_t th[THREAD_NUM];
    // we can also create a detached thread instead of creating a thread and detach it after it's creation 
    //second parameter of the pthread_create function is used for this
    pthread_attr_t detachedThread;
    pthread_attr_init(&detachedThread);
    //the second parameter is either joinable or detached
    pthread_attr_setdetachstate(&detachedThread, PTHREAD_CREATE_DETACHED);

    int i;
    for (i = 0; i < THREAD_NUM; i++) {
        //change the second parameter for the detached thread
        if (pthread_create(&th[i], &detachedThread, &routine, NULL) != 0) {
            perror("Failed to create thread");
        }
        //a detached thread is no longer joinable
        //pthread_detach(th[i]);
    }

    // NO NEED TO JOIN
    // for (i = 0; i < THREAD_NUM; i++) {
    //     if (pthread_join(th[i], NULL) != 0) {
    //         perror("Failed to join thread");
    //     }
    // }

    pthread_attr_destroy(&detachedThread);
    //with this we no longer worried about the main thread being stopped and other threads are not being executed
    //used instead of (return 0)
    pthread_exit(0);
}