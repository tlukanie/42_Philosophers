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

int main(int argc, char* argv[]){
    int arr[5];
    int fd = open("sum", O_RDONLY);
    if (fd == -1){
        return 1;
    }
    int i;
    //for (i = 0; i < 5; i++){
    if (read(fd, arr, sizeof(int) * 5) == -1)
    {
        return 2;
    }
    //printf("Received %d\n", arr[i]);
    //}
    close(fd);
    int sum = 0;
    for (i = 0; i < 5; i++)
    {
        sum += arr[i];
    }
    printf("Result is %d\n", sum);

    //Task: try to send this sum back to the other program

    return 0;
}