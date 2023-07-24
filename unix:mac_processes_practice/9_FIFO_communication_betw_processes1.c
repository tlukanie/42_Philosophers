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

int main(int argc, char* argv[])
{
    int arr[5];
    srand(time(NULL));
    int i;
    for (i = 0; i < 5; i++){
        arr[i] = rand() % 10;
        printf("Generated %d\n", arr[i]);
    }

    //open FIFO
    int fd = open("sum", O_WRONLY);
    if (fd == -1){
        return 1;
    }
    //can write data to an array without using for loop
    if (write(fd, arr, sizeof(int) * 5) == -1){
        return 2;
    }
    //  printf("Wrote %d\n", arr[i]);
    
    close(fd);
    return 0;
}