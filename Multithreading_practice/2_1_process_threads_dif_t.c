#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int x = 2;

void* routine(){
    //printf("Process id %d\n", getpid());
    x+=5;
    sleep(2);
    printf("Value of x: %d\n", x);
    return (NULL);
}

void* routine2(){
    //printf("Process id %d\n", getpid());
    
    sleep(2);
    printf("Value of x: %d\n", x);
    return (NULL);
}

int main(int argc, char *argv[])
{
    pthread_t t1, t2;
    if (pthread_create(&t1, NULL, &routine, NULL))
    {
        return 1;
    }
    if (pthread_create(&t2, NULL, &routine2, NULL))
    {
        return 2;
    }
    if (pthread_join(t1, NULL))
    {
        return 3;
    }
    if (pthread_join(t2, NULL))
    {
        return 4;
    }
    return 0;
}