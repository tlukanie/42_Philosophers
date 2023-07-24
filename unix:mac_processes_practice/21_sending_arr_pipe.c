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

// 2 processes
// 1) child process should generate random numbers and send them to the parent
// 2) parent receives, and is going to sum all the numbers and print the result

//to send an array through a pipe you always need to send the number of elements
//in that array first

int main(int argc, char* argv[]){
    int fd[2];
    if (pipe(fd) == -1){
        return 2;
    }
    int pid = fork();
    if (pid == -1){
        return 1;
    }

    if (pid == 0){
        //fd[0] is read file descriptor
        close(fd[0]);
        int n, i;
        int arr[10];
        srand(time(NULL));
        n = rand() % 10 + 1;
        printf("Generated: ");
        for (i = 0; i < n; i++){
            arr[i] = rand() % 11;
            printf("%d ", arr[i]);
        }
        printf("\n");
        if (write(fd[1], &n, sizeof(int)) < 0) {
            return 4;
        }
        printf("Sent n = %d\n", n);
        if (write(fd[1], arr, sizeof(int) * n) < 0) {
            return 3;
        }
        printf("Sent array\n");
        close(fd[1]);
    } else {
        // Parent process
        close(fd[1]);
        int arr[10];
        int n, i, sum = 0;
        if (read(fd[0], &n, sizeof(int)) < 0) {
            return 5;
        }
        printf("received n = %d\n", n);
        if (read(fd[0], arr, sizeof(int) * n) < 0){
            return 6;
        }
        printf("Received array\n");
        close(fd[0]);
        for (i = 0; i < n; i++){
            sum += arr[i];
        }
        printf("Result is %d\n", sum);
        wait(NULL);
    }

    return 0;
}