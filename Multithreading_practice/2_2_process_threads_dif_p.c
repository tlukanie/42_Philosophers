#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char* argv[])
{
    int x = 2;
    int pid = fork();
    if (pid == -1){
        return 1;
    }
    //if we are inside of the child process, increment x
    if (pid == 0){
        x++;
    }
    sleep(2);
    printf("Value of x: %d\n", x);
    //printf("Process id %d\n", getpid());
    if (pid != 0){
        wait(NULL);
    }
    return 0;
}

//processes can contain multiple threads