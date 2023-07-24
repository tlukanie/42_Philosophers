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

//everytime sending an str we have to send a number of chars in this str first!!!

int main(int argc, char* argv[]){
    int fd[2];
    if (pipe(fd) == -1){
        return 1;
    }

    int pid = fork();
    if (pid < 0){
        return 2;
    }

    if (pid == 0){
        //child process
        close(fd[0]);
        char str[200];
        printf("Input string: ");
        //READING INPUT FROM THE USER
        //1 arg - the string that you want to read into, 2 - maximum num of chars that it can fit into that str,
        //3 - the stream that it should read from (stdin = from the keyboard of the user)
        fgets(str, 200, stdin);
        //removing \n at the end of that string
        str[strlen(str) - 1] = '\0'; //setting \n to \0 terminator
        int n = strlen(str) + 1;
        if (write(fd[1], &n, sizeof(int)) < 0){
            return 6;
        }
        //sending string to the parent process
        if (write(fd[1], str, sizeof(char) * n) < 0){
            return 3;
        }
        close(fd[1]);
    } else {
        close(fd[1]);
        char *str[200];
        int n;
        if (read(fd[0], &n, sizeof(int)) < 0){
            return 4;
        }
        if (read(fd[0], str, sizeof(char) * n) < 0){
            return 5;
        }
        printf("%s\n", str);
        close(fd[0]);
        wait(NULL);
    }

    return 0;
}