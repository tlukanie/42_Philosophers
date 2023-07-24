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

//to simulate pipe we use two processes and dup2 + pipe

int main(int argc, char* argv[]){
    int fd[2];
    if (pipe(fd) == -1){
        return 1;
    }

    //we need to create two processses
    int pid1 = fork();
    if (pid1 < 0) {
        return 2;
    }

    //child process will get replaced by the ping program
    if (pid1 == 0){
        //we need to rerout the standard output of our previous process (ping program)
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        // child process 1 (ping)
        execlp("ping", "ping", "-c", "5", "google.com", NULL);
    }
    //everything after this can only be executed by the parent process, cause the exec function replace the whole process itself
    

    //creating process for grep
    int pid2 = fork();
    if (pid2 < 0) {
        return 3;
    }

    if (pid2 == 0) {
        //child process 2(grep)
        //grep replaces it's standard output with reading end of the pipe
        //grep is waiting to read from that pipe
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        execlp("grep", "grep", "r", NULL);
    }

    //important to close, otherwise grep won't finish it's execution
    close(fd[0]);
    close(fd[1]);

    //since we use two processes we need to wait for them individualy, so we use waitpid
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}