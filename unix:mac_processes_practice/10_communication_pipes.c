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

//The program generates a number from 0 to 9, then the number is sent to the other process
//and what this other process does, it multiplies this number by n and the result is sent back
//to the original problem using pipes and fork


//We can't have a pipe that both sends data and receives data on the same process
//that means we have to have two pipes in order to achieve this solution in order for it to
//always work


int main(int argc, char* argv[]){
    int p1[2]; //child => to parent
    int p2[2]; //parent => to child
    if (pipe(p1) == -1){ return 1; }
    if (pipe(p2) == -1){ return 1; }
    int pid = fork();
    if (pid == -1) { return 2; }
    if (pid == 0) {
        close(p1[0]);
        close(p2[1]);
        //Child process
        //we want to read the data from the parent process
        int x;
        if (read(p2[0], &x, sizeof(x)) == -1) { return 3; }
        printf("Received %d\n", x);
        x *= 4;
        if (write(p1[1], &x, sizeof(x)) == -1) { return 4; }
        printf("Wrote in child %d\n", x);
        close(p1[1]);
        close(p2[0]);
    } else {
        close(p1[1]);
        close(p2[0]);
        // Parent process
        srand(time(NULL));
        int y = rand() % 10;
        if (write(p2[1], &y, sizeof(y)) == -1) { return 5; }
        printf("Wrote in main %d\n", y);
        //sleep(1);
        if (read(p1[0], &y, sizeof(y)) == -1) { return 6; }
        printf("Result is %d\n", y);
        close(p1[0]);
        close(p2[1]);
        wait(NULL);
    }
    return 0;
}