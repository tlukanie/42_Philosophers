#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>

#define THREAD_NUM 4

//all the values are 0???

sem_t sem;

void* routine(void* args) {
    int index = *(int*)args;
    int semVal;
    sem_wait(&sem);
    sleep(index + 1);
    sem_getvalue(&sem, &semVal);
    printf("(%d) Current semaphore value after wait is %d\n", index, semVal);
    sem_post(&sem);
    sem_getvalue(&sem, &semVal);
    printf("(%d) Current semaphore value after post is %d\n", index, semVal);
    free(args);
}

int main(int argc, char *argv[]) {
    pthread_t th[THREAD_NUM];
    sem_init(&sem, 0, 4);
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
    sem_destroy(&sem);
    return 0;
}