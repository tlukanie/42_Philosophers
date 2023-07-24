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

//fork() splits the execution of the process, so it has to return two different values

int main(int argc, char* argv[]){
    int id = fork();
    // Inside parent process - child process id - it's going to be different than getpid()
    // Inside child process - 0  - it's going to be different than getpid()
    if (id == 0){
        sleep(1);
    }
    printf("Returned by fork: %d, Curent ID: %d, parent ID: %d\n", id, getpid(), getppid());

    int res = wait(NULL);

    if (res == -1){
        printf("No children to wait for\n");
    } else {
        printf("%d finished execution\n", res);
    }
    return 0;
}

// OUTPUT
/*
Returned by fork: 2022, Curent ID: 2021, parent ID: 898
Returned by fork: 0, Curent ID: 2022, parent ID: 2021
No children to wait for
2022 finished execution
*/