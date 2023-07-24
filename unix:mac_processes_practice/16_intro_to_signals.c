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

//with signals you just sort of send short notifications (simple integral) that says to 
//the other process what it should do (it doesn't send any more infromation)
//that is used to take control of that process

//Example: if I have a process and I want to pause it's execution, I can do it using signals

//receiving signals doesn't depend on the order of execution of the code
//even we were in a while loop, that signal was handled here

int main(int argc, char* argv[]){
    int pid = fork();
    if (pid == -1){
        return 1;
    }

    if (pid == 0){
        while(1){
            printf("Some text goes here\n");
            usleep(50000);
        }
    } else {
        sleep(1);
        //send  a signal to terminate the process
        //1 param - pid, 2 -signal
        kill(pid, SIGKILL);
        wait(NULL);
    }
    return 0;
}