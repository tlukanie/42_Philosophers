#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h> //to open FIFO


int main(int argc, char* argv[]){
    int pid = fork();
    if (pid == -1)
        return 1;
    if (pid == 0){
        //child process
        int err = execlp("ping", "ping", "-c", "3", "google.com", NULL);
        //there could be two types of errors
        //if program ping doesn't exist, if actual ping is found and executed but gives out an error
        //if there is no ping, exec function won't stop the child process from its execution
        if (err == -1){
            printf("Could not find program to execute!\n");
            return 2;
        }

    }
    else
    {
        int wstatus;
        wait(&wstatus);
        //to check if the process terminated normally
        //if returns true (if return something different than 0)
        //return 1 and exit(1) re the same
        //in linux the exit code that is not 0 signifies an error
        if(WIFEXITED(wstatus)){
            //return value inside the main or the value that it exited with
            int statusCode = WEXITSTATUS(wstatus);
            if(statusCode == 0){
                printf("Success!\n");
            } else {
                printf("Failure with status code %d\n", statusCode);
            }
        }
        printf("Some post processing goes here!\n");
    }
    return 0;
}