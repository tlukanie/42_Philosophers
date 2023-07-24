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

#define PROCESS_NUM 10

int main(int argc, char* argv[]){
    //storing process ids in an array
    int pids[PROCESS_NUM];
    int pipes[PROCESS_NUM + 1][2];
    int i;
    for (i = 0; i < PROCESS_NUM + 1; i++){
        if (pipe(pipes[i]) == -1){
            printf("Error with creating pipe\n");
            return 1;
        }
    }

    //creating n number of processes
    for (i = 0; i < PROCESS_NUM; i++){
        pids[i] = fork();
        if (pids[i] == -1){
            printf("Error with creating process\n");
            return 2;
        }
        if (pids[i] == 0){
            //child process
            //closing all the pipes that we don't use
            int j;
            for (j = 0; j < PROCESS_NUM + 1; j++){
                if (i != j){
                    close(pipes[j][0]);
                }
                if (i + 1 != j){
                    close(pipes[j][1]);
                } //because the main function will read from the last pipe and write to the first one
            }
            int x;
            if (read(pipes[i][0], &x, sizeof(int)) == -1){
                printf("Error at reading\n");
                return 3;
            }
            printf("(%d) Got %d\n",i, x);
            x++;
            //writing previous info to the next pipe, that's why +1
            if (write(pipes[i + 1][1], &x, sizeof(int)) == -1){
                printf("Error at writing\n");
                return 4;
            } 
            printf("(%d) Sent %d\n",i, x);
            //close the other pipes that we've done using them
            close(pipes[i][0]);
            close(pipes[i + 1][1]);

            //so that every child process does no execute fork again instead of return 0
            //break;
            return 0;
        }
    }

    //main process
    //closing all the fds that we don't use
    int j;
    for (j = 0; j < PROCESS_NUM + 1; j++){
        if (j != PROCESS_NUM){
            close(pipes[j][0]);
        }
        if (j != 0){
            close(pipes[j][1]);
        } //because the main function will read from the last pipe and write to the first one
    }
    int y = 5;
    printf("Main process sent %d\n", y);
    if (write(pipes[0][1], &y, sizeof(int)) == -1){
        printf("Error at writing\n");
        return 5;
    }

    if (read(pipes[PROCESS_NUM][0], &y, sizeof(int)) == -1){
        printf("Error at reading\n");
        return 6;
    }
    printf("The final result is %d\n", y);

    close(pipes[0][1]);
    close(pipes[PROCESS_NUM][0]);

    for (i = 0; i < PROCESS_NUM; i++){
        wait(NULL);
    }

    return 0;
}