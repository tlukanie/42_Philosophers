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

//you can't have a pipe between two processes that aren't on the same hierarchy
//FIFOs are a file type to which you can read or write from any process that you open
//FIFOs are very similar to a file

//open function for FIFOs
//Opening the read or write end of a FIFO blocks until the other end is
//also opened (by another process or thread)
//Means: if you open FIFO for writing - the open call hangs blocks 
//until another process comes on and opens the same FIFO for reading
//the process opened for writing will continue after another process opens FIFO for reading

//can create fifo file in the terminal running command mkfifo fifoname

int main(int argc, char* argv[]){
    //FIFO file that is goig to be used as a pipe
    //FIFO is really unnamed pipe
    //creating a FIFO file (1 param - name, 2 - permission) 0777-by anybody
    if (mkfifo("myfifo1", 0777) == -1)
    {
        if (errno != EEXIST){
            printf("Could not create fifo file\n");
            return 1;
        }
    }
    printf("Opening...\n");
    int fd = open("myfifo1", O_WRONLY); //returns a file descriptor // O_RDWR will finish its execution without cat
    if (fd == -1){
        return 3;
    }
    printf("Opened\n");
    int x = 98; //will get ASCII b
    if (write(fd, &x, sizeof(x)) == -1)
    {
        return 2;
    }
    printf("Written\n");
    close(fd);
    printf("Closed\n");
    return 0;
}