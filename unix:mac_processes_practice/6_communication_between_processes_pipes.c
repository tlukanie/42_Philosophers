#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>

//this program asks a user to input a number and then it sends it to the other process
//from the child process to the parent process, and the parent process prints it on the screen
//or does some operations with it

//pipe is in-memory file
//it's a file that only has sort of buffer that is saved in memory
//and you can write or read from it

//to open a pipe call a function pipe()

int main(int argc, char* argv[]){
    //fd[0] - read (to read from)
    //fd[1] - write (to write to)
    int fd[2];
    //takes an array of two integers, that are the file descriptors for this pipe
    //a file descriptor is a key for the access to a file, where we want to read or write data to
    //this function will save inside fd array the file descriptors that it opens when we create this pipe
    //returns 0 if seccessful, -1 if not
    if (pipe(fd) == -1){
        printf("An error ocurred opening the pipe\n");
        return 1;
    }
    int id = fork();
    //checking fork for errors
    if (id == -1)
    {
        printf("An error ocurred with fork\n");
        return 4;
    }
    //two file descriptors will be copied over from fd arr and inherited as well
    //they can be opened or closed independently of each other
    if (id == 0)
    {
        //because we don't read anything from fd[0]
        close(fd[0]);
        int x;
        printf("Input a number: ");
        scanf("%d", &x);
        //checking for the errors
        if (write(fd[1], &x, sizeof(int)) == -1)
        {
            printf("An error ocurred with writing to the pipe\n");
            return 2;
        }
        //after we are done writing we should close fd[1] file descriptor
        close(fd[1]);
    } else {
        close(fd[1]);
        int y;
        if (read(fd[0], &y, sizeof(int)) == -1){
            printf("An error ocurred with reading from the pipe\n");
            return 3;
        }
        y = y * 3;
        close(fd[0]);
        printf("Got from child process %d\n", y);
    }

    return 0;
}