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

//Program: create 3 prcesses: 1)main x = 0; 2) 1st child x += 5; 3) 2nd child x + 5 = 10
//--> return 10 to the main process (use 3 pipes for this)

//all the file descriptors that are open in the main process got duplicated in every other process
//that's why should be managed multiple times, independently in every process

int main(int argc, char* argv[]){
	//because we'll need 3 pipes
	int fd[3][2];
	int i;
	//open 3 pipes
	for (i = 0; i < 3; i++){
		if (pipe(fd[i]) < 0){
			return 1;
		}
	}

	//create processes 
	int pid1 = fork();
	if (pid1 < 0){
		return 2;
	}

	if (pid1 == 0){
		//child process #1
		close(fd[0][1]);
		close(fd[1][0]);
		close(fd[2][0]);
		close(fd[2][1]);
		int x;
		if (read(fd[0][0], &x, sizeof(int)) < 0) {
			return 3;
		}
		x += 5;
		if (write(fd[1][1], &x, sizeof(int)) < 0) {
			return 4;
		}
		close(fd[0][0]);
		close(fd[1][1]);
		return 0; //the code under this will only be executed by the parent
	}

	int pid2 = fork();
	if (pid2 < 0){
		return 5;
	}

	if (pid2 == 0){
		//child process #2
		close(fd[0][0]);
		close(fd[0][1]);
		close(fd[1][1]);
		close(fd[2][0]);
		int x;
		if (read(fd[1][0], &x, sizeof(int)) < 0) {
			return 6;
		}
		x += 5;
		if (write(fd[2][1], &x, sizeof(int)) < 0) {
			return 7;
		}
		close(fd[1][0]);
		close(fd[2][1]);
		return 0;
	}

	//parent process
	close(fd[0][0]);
	close(fd[1][0]);
	close(fd[1][1]);
	close(fd[2][1]);
	int x;
	printf("Input number: ");
	scanf("%d", &x);
	if (write(fd[0][1], &x, sizeof(int)) < 0) {
		return 8;
	}
	if (read(fd[2][0], &x, sizeof(int)) < 0) {
		return 9;
	}
	printf("Result is %d\n", x);
	close(fd[0][1]);
	close(fd[2][0]);

	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return 0;
}

//Exercise: generalize this program, instead of 3 processes use n processes and for loop