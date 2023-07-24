#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h> 
#include <signal.h>

int x = 0;

void handle_sigusr1(int sig){
    if (x == 0)
        printf("\n(HINT) Remember that multiplication is repetitive addition!\n");
}

//Program: a simple question to be asked by the program and user is gonna answer it
//if it takes 5 second longer to answer the question

int main(int argc, char* argv[]){
    int pid = fork();
    if (pid == -1){
        return 1;
    }

    if (pid == 0){
        //child process will do the waiting for us
        sleep(5);
        //after waiting, send a signal to the parent
        kill(getppid(), SIGUSR1);

    } else {
        //Parent process
        //adding handler for SIGUSR1
        struct sigaction sa = { 0 };
        sa.sa_flags = SA_RESTART;
        sa.sa_handler = &handle_sigusr1;
        //bind sigusr1 signal to the handler
        sigaction(SIGUSR1, &sa, NULL);


        printf("What is the result of 3 x 5: ");
        scanf("%d", &x);
        if (x == 15){
            printf("Right!\n");
        } else {
            printf("Wrong!\n");
        }
        wait(NULL);
    }

    return 0;
}