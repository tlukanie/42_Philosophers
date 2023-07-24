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

//exec functions on mac differ from linux functions, look source code


int main(int argc, char* argv[], char* envp[]){
    char* arr[] = {"ping", "google.com", NULL};
    char* env[] = {"TEST=environment variable", NULL};
    execvp("ping", arr);
    //execlp("ping", "ping", "google.com", NULL);
    int err = errno;

    printf("Ping finished executing\n"); //will print it if exec fucntion failde to run
    return 0;
}