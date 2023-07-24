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

//in this program we'll stop ping command from printing on the terminal

//file descriptor is a number that is unique across the process
//read(0) is similar to scanf


int main(int argc, char* argv[]){
    int pid = fork();
    if (pid == -1)
        return 1;
    if (pid == 0){
        //child process
        //use | to choose multiple flags
        int file = open("pingResults.txt", O_WRONLY | O_CREAT, 0777);
        if (file == -1){
            return 2;
        }
        printf("The fd to pingResults: %d\n", file); //3
        //dup function returns another file descriptor for our ping results
        //int file2 = dup(file);
        //dup2(file_to_clone, value_of_new_fd)
        //1 is the same as STDOUT_FILENO
        /*
        int file2 = dup2(file, STDOUT_FILENO);
        printf("The duplicated fd: %d\n", file2); //1
        */
        dup2(file, STDOUT_FILENO);
        //close original file as we don't use it
        close(file);
        int err = execlp("ping", "ping", "-c", "3", "google.com", NULL);
        if (err == -1){
            printf("Could not find program to execute!\n");
            return 2;
        }

    }
    else
    {
        int wstatus;
        wait(&wstatus);
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