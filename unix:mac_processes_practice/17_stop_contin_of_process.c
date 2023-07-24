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

//Stoping and continuing the execution of a process (using SIGCONT and SIGSTOP)
//This program prompts to give a number of seconds, and from then on the child process
//starts executing exactly for 5 seconds and after those 5 seconds have elapsed
//it stops executing (doesn't necessary kill or terminate it's process), and I give
//another prompt to actually give it another input of seconds and have it execute 
//for another set of seconds

int main(int argc, char* argv[]){
    int pid = fork();
    if (pid == -1){
        return 1;
    }

    if (pid == 0){
        //kind of listener of data where you can control it's execution
        while(1){
            printf("Some output\n");
            usleep(50000);
        }
    } else {
        kill(pid, SIGSTOP);
        int t;
        do {
            printf("Time in seconds for execution: ");
            scanf("%d", &t);

            if (t > 0){
                kill(pid, SIGCONT);
                sleep(t);
                kill(pid, SIGSTOP);
            }
        } while (t > 0);
        /*
        kill(pid, SIGSTOP); //says to child process to stop executing
        sleep(1);
        kill(pid, SIGCONT); //continue the child process's execution
        sleep(1); */
        kill(pid, SIGKILL);
        wait(NULL);
    }

    return 0;
}