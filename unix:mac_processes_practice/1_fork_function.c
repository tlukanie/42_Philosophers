#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> //for linux

//fork() - a child process gets born and starts executing the folowwing lines 
//alongside with the main process at the same time

int main(int argc, char* argv[]){
    int id = fork();
    //id in the child process is always 0 
    //if id is not 0 - means you are in the main process
    //every single process - has a process id
    //printf("Hello world from id: %d\n", id);
    // if (id == 0) //we know that we are in the child process
    // {
    //     printf("Hello from the child process\n");
    // } else {
    //     printf("Hello from the main process\n");
    // }
    if (id != 0) //if we are in the main process
        fork();
    printf("Hello world\n");
    return 0;
}