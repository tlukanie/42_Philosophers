#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>

/*
Global Variable errno: When a function is called in C, a variable named as errno is automatically 
//assigned a code (value) which can be used to identify the type of error that has been encountered. 
//Its a global variable indicating the error occurred during any function call and defined in the header 
//file errno. h.
*/


//wait(NULL) returns -1 if there is nothing to wait for

//when you create multiple processes - make sure that you create them from the main process

int main(int argc, char* argv[])
{
    int id1 = fork();
    int id2 = fork();
    if (id1 == 0) //child of the parent process
    {
        if (id2 == 0) //child of that child
        {
            printf("We are process y\n");
        } else {
            printf("We are process x\n");
        }
    } else {
        if (id2 == 0) //another child of the parent process
        {
            printf("We are process z\n");
        } else {
            printf("We are the parent process!\n");
        }
    }
    //wait only for one child to finish execution
    //wait(NULL);

    //will wait for all the processes that it shoudl wait for
    while (wait(NULL) != -1 || errno != ECHILD)
    {
        printf("Waited for a child to finish\n"); //will get it 3 times
    }
    return 0;
}