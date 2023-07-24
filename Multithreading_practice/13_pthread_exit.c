#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

//pthread_exit is useful when you want to start some threads in the main thread 
//and you want to leave them running while main simply just exits

void* roll_dice() {
    int value = (rand() % 6) + 1;
    int* result = malloc(sizeof(int));
    *result = value;
    sleep(2);
    printf("Thread result: %d\n", value);
    //another way to return a value
    //instead of calling return can call pthread_exit()
    pthread_exit((void*)result);
}

int main(int argc, char *argv[])
{
    int *res;
    srand(time(NULL));
    pthread_t th;
    if(pthread_create(&th, NULL, &roll_dice, NULL) != 0){
        return 1;
    }
    pthread_exit(0); //won't execute the code below
    //pthread_exit(0) does not kill the process, only exit() (or return 0) does
    if(pthread_join(th, (void **)&res) != 0){
        return 2;
    }
    //printf("Main res: %p\n", res);
    printf("Result: %d\n", *res);
    free(res);
    return 0;
}