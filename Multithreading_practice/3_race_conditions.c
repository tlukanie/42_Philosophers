#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int mails = 0;

void* routine()
{
    for (int i = 0; i < 1000000; i++)
        mails++;
        //read mails
        //increment
        //write mails
    return (NULL);
}

int main(int argc, char *argv[])
{
    pthread_t t1, t2;
    if (pthread_create(&t1, NULL, &routine, NULL))
    {
        return 1;
    }
    if (pthread_create(&t2, NULL, &routine, NULL))
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
    printf("Number of mails: %d\n", mails);
    return 0;
}