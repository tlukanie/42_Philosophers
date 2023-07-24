#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>

//this program will sum up the numbers
//half of the array will be calculated by one process, and another half by the other
//at the end we will have a partial sum
//and one process will write this partial sum to the pipe
//and the other one is gonna read it and just sum them all up together

//Task: try to add a child and divide array / 3

int main(int argc, char* argv[])
{
    int arr[] = {1, 2, 3, 4, 1, 2 , 7, 7};
    //will give us the number of integers
    int arrSize = sizeof(arr) / sizeof(int);
    //for process to know where to start/end its partial sum
    int start, end;
    int fd[2];
    if (pipe(fd) == -1){
        return 1;
    }
    int id = fork();
    if (id == -1)
    {
        return 2;
    }

    if (id == 0){
        start = 0;
        end = arrSize / 2;
    } else {
        start = arrSize / 2;
        end = arrSize;
    }

    int sum = 0;
    int i;
    for (i = start; i < end; i++){
        sum += arr[i];
    }
    
    printf("Calculated partial sum: %d\n", sum);

    if (id == 0)
    {
        close(fd[0]);
        if (write(fd[1], &sum, sizeof(sum)) == -1)
            return 3;
        close(fd[1]);
    } else {
        int sumFromChild;
        close(fd[1]);
        if (read(fd[0], &sumFromChild, sizeof(sumFromChild)) == -1)
            return 4;
        close(fd[0]);

        int totalSum = sum + sumFromChild;
        printf("Total sum is %d\n", totalSum);
        wait(NULL); //wait for the child process to finish
    }

    return 0;
}