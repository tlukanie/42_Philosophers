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

//exec fucntions are actually replace the whole process
//all the memory is going to be replaced by its own memory
//the execution line is going to be replaced by its own line, you are left with nothing

//should use fork() and call exec functions inside of the child process

int main(int argc, char* argv[]){
    int pid = fork();
    if (pid == -1)
        return 1;
    //"-c" "3" for how many times to calls
    if (pid == 0){
        //here the child process got replaced by the ping process
        execlp("ping", "ping", "-c", "3", "google.com", NULL);
        //execlp("mkfifo", "mkfifo", "sum", NULL);
        printf("Hi!\n");
    }
    else
    {
        wait(NULL);
        printf("Success!\n");
        printf("Some post processing goes here!\n");
    }
    return 0;
}