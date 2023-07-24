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

int main(int argc, char* argv[]){
    int pid1  = fork();
    if (pid1 == -1){
        printf("Error creating process");
        return 1;
    }
    if (pid1 == 0){
        sleep(4);
        printf("Finished execution (%d)\n", getpid());
        return 0;
    }

    int pid2 = fork();
    if (pid2 == -1){
        printf("Error creating process");
        return 2;
    }
    if (pid2 == 0){
        sleep(1);
        printf("Finished execution (%d)\n", getpid());
        return 0;
    }

    /*
    int pid1_res = wait(NULL);
    printf("Waited for %d\n", pid1_res);
    int pid2_res = wait(NULL);
    printf("Waited for %d\n", pid2_res);
    */

   //in waitpid we can pass as the third parameter a flag like WNOHANG, that means
   //it's not gonna wait for the process to finish it's execution;
   //it's just gonna check if it is finished it's execution, then it's fine otherwise
   //it;s gonna return and save the status inside of the second parameter
   //WNOHANG won't wait for anything, just check
    int pid1_res = waitpid(pid1, NULL, 0);
    printf("Waited for %d\n", pid1_res);
    int pid2_res = waitpid(pid2, NULL, 0);
    printf("Waited for %d\n", pid2_res);

    return 0;
}