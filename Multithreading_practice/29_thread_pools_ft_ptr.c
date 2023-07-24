// pthread barriers are not implemented in OS X, which is supposedly POSIX compliant.
// So to get my application to compile, I found an implementation of barriers using other pthread features.
//Paste the following into a file and include it in your Mac OS X code that uses pthread barriers:

#ifdef __APPLE__

#ifndef PTHREAD_BARRIER_H_
#define PTHREAD_BARRIER_H_

#include <pthread.h>
#include <errno.h>

typedef int pthread_barrierattr_t;
typedef struct
{
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int count;
    int tripCount;
} pthread_barrier_t;


int pthread_barrier_init(pthread_barrier_t *barrier, const pthread_barrierattr_t *attr, unsigned int count)
{
    if(count == 0)
    {
        errno = EINVAL;
        return -1;
    }
    if(pthread_mutex_init(&barrier->mutex, 0) < 0)
    {
        return -1;
    }
    if(pthread_cond_init(&barrier->cond, 0) < 0)
    {
        pthread_mutex_destroy(&barrier->mutex);
        return -1;
    }
    barrier->tripCount = count;
    barrier->count = 0;

    return 0;
}

int pthread_barrier_destroy(pthread_barrier_t *barrier)
{
    pthread_cond_destroy(&barrier->cond);
    pthread_mutex_destroy(&barrier->mutex);
    return 0;
}

int pthread_barrier_wait(pthread_barrier_t *barrier)
{
    pthread_mutex_lock(&barrier->mutex);
    ++(barrier->count);
    if(barrier->count >= barrier->tripCount)
    {
        barrier->count = 0;
        pthread_cond_broadcast(&barrier->cond);
        pthread_mutex_unlock(&barrier->mutex);
        return 1;
    }
    else
    {
        pthread_cond_wait(&barrier->cond, &(barrier->mutex));
        pthread_mutex_unlock(&barrier->mutex);
        return 0;
    }
}

#endif // PTHREAD_BARRIER_H_
#endif // __APPLE__

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>

//implementation of threadpools using pthread API
//threadpools are just a simple way of handling tasks in a multi-threaded manner
//threadpools help to execute multiple tasks at the same time

//a thread pool usually has a set number of threads always running
//so the thread is either executing a task that it has been given or it just waiting for a task
//to appear in the queue


//main thread (a user) ---> insert + create a task ---> task queue
//4x threads in thread pool ---> wait and get a task ---> task queue
//4x threads in thread pool <--- execute task

#define THREAD_NUM 8

//creating a task (adding two nums)
typedef struct Task {
    void (*taskFunction)(int, int);
    //to pass two parameters to the function
    int arg1, arg2;
} Task;


//task queue
Task taskQueue[256];
int taskCount = 0; //because we don't have any tasks at the beginning

pthread_mutex_t mutexQueue;
pthread_cond_t condQueue;

/*
void sumAndProduct(int a, int b) {
    usleep(50000);
    int sum = a + b;
    int prod = a * b;
    printf("Sum and product of %d and %d is %d and %d respectively\n",
        a, b, sum, prod);
}
*/

void sum(int a, int b) {
    usleep(50000);
    int sum = a + b;
    printf("Sum of %d and %d is %d\n", a, b, sum);
}

void product(int a, int b) {
    usleep(50000);
    int prod = a * b;
    printf("Product of %d and %d is %d\n", a, b, prod);
}

void executeTask(Task* task){
    task->taskFunction(task->arg1, task->arg2);
    // usleep(50000);
    // int result = task->a + task->b;
    // printf("The sum of %d and %d is %d\n", task->a, task->b, result);
}


//whenever we are submitting a task we should signal a single thread to check if there actually a task there
//and if it is - it should execute it
//we don't need broadcast, because we only add one task - and for one task we only need one thread
void submitTask(Task task){
    //make sure that everything is synchronized - add mutex
    pthread_mutex_lock(&mutexQueue);
    taskQueue[taskCount] = task;
    taskCount++;
    pthread_mutex_unlock(&mutexQueue);
    pthread_cond_signal(&condQueue);
}


// 1 2 3 4 5 
// 2 3 4 5 

void* startThread(void* args){
    while(1){
        Task task;
        
        pthread_mutex_lock(&mutexQueue);
        while (taskCount == 0) {
            //when we are waiting it unlocks the mutex for us so that other threads could check
            pthread_cond_wait(&condQueue, &mutexQueue);
        }
        task = taskQueue[0];
        int i;
        for (i = 0; i < taskCount - 1; i++){
            taskQueue[i] = taskQueue[i + 1];
        }
        taskCount--;
        pthread_mutex_unlock(&mutexQueue);
        executeTask(&task);
    }
}

int main(int argc, char* argv[]){
    /*
    Task t1 = {
        .a = 5,
        .b = 10
    };
    executeTask(&t1); */
    pthread_t th[THREAD_NUM];
    pthread_mutex_init(&mutexQueue, NULL);
    pthread_cond_init(&condQueue, NULL);
    int i;
    for (i = 0; i < THREAD_NUM; i++){
        if(pthread_create(&th[i], NULL, &startThread, NULL) != 0){
            perror("Failed to create the thread");
        }
    }

    srand(time(NULL));
    for (i = 0; i < 100; i++){
        Task t = {
            .taskFunction = i % 2 == 0 ? &sum : &product,
            //arguments being passed from the main function
            .arg1 = rand() % 100,
            .arg2 = rand() % 100
        };
        submitTask(t);
    }

    for (i = 0; i < THREAD_NUM; i++){
        if(pthread_join(th[i], NULL) != 0){
            perror("Failed to join the thread");
        }
    }
    pthread_mutex_destroy(&mutexQueue);
    pthread_cond_destroy(&condQueue);
    return 0;
}


//Task: how to return a value from the functions
//add another taskQueue