#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <sys/wait.h>

//process IDs - identification numbers for processes
//getppid() - returns the parent process id
//child process always should terminate first before the termination of the parent process
//if the main process terminates and child process keeps running - a new parent process will be assigned
//to this child process

int main(int argc, char* argv[]){
    int id = fork();
    /*
    if (id == 0)
        printf("child id is %d\n", getpid());
    else
        printf("main id is %d\n", getpid());
    */
   if (id == 0)
   {
       sleep(1);
   }
   printf("Current ID: %d, parent ID: %d\n", getpid(), getppid());

   //wait for the child to finish
   //works without if as well
   //if (id != 0)
  // {
        //wait(NULL);
  // }
  int res = wait(NULL);
  if (res == -1){
      printf("No children to wait for\n");
  } else {
      //wait(NULL) returns the PID of the process we waited for
      printf("%d finished execution\n", res);
  }
    return 0;
}