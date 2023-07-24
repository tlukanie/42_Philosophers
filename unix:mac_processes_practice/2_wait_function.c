#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>

//waiting for processes to finish
//printig 1-5 from the child process, 6-10 from the main process
// wait() function helps to order the execution of the processes

int main(int argc, char* argv[]){
    int id = fork();
    int n;
    if (id == 0)
    {
        n = 1;
    } else {
        n = 6;
    }
    if (id != 0){ //if this is the main process
        wait(NULL); //wait for the child process to finish
    }
    int i;
    for (i = n; i < n + 5; i++) {
        printf("%d ", i);
        //every time I print the digit - it will be shown on the terminal
        fflush(stdout);
    }
    if (id != 0)
        printf("\n");
    return 0;
}