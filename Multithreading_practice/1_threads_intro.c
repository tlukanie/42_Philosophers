#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void* routine() {
    printf("Test from threads\n");
    sleep(3);
    printf("Ending thread\n");
    return (NULL);
}

int main(int argc, char *argv[])
{
    //declaring variable for thread
    pthread_t t1, t2;
    //initializing a thread
    if (pthread_create(&t1, NULL, &routine, NULL) != 0){
        return 1;
    }
    if (pthread_create(&t2, NULL, &routine, NULL) != 0){
        return 2;
    }
    //wait for the thread to finish its execution
    if(pthread_join(t1, NULL) != 0){
        return 3;
    }
    if(pthread_join(t2, NULL) != 0){
        return 4;
    }
    return 0;
}