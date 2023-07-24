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

//grep command helps to sort out the output of the program
//exec functions execute a simple executable
//whereis ping to find a ping path

int main(int argc, char* argv[])
{
    int pid = fork();
    if (pid == -1){
        return 1;
    }

    if (pid == 0){
        int err = execlp("ping", "ping", "-c", "1", "google.com", NULL);
        if (err == -1){
            printf("Could not find program to execute!\n");
            return 2;
        }
    } else {
        int wstatus;
        wait(&wstatus);
        if (WIFEXITED(wstatus)) {
            int statusCode = WEXITSTATUS(wstatus);
            if (statusCode == 0) {
                printf("Success!\n");
            } else {
                printf("Failure with status code %d\n", statusCode);
            }
        }

        printf("Some post processing goes here!\n");
    }
}