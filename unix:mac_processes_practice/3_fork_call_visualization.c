#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>

//each process has a copy of its own variables
//when you fork it - you're gonna get the same values
//both processes in this case execute the same lines of code,
//but with different results because of id

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
        fflush(stdout);
    }
    if (id != 0)
        printf("\n");
    return 0;
}