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

void handle_sigtstp(int sig){
    printf("Stop not allowed\n");
}

//for portability reasons better to use sigaction instead of signal function

int main(int argc, char* argv[]){

    //does the same thing as sigaction
    signal(SIGTSTP, &handle_sigtstp);

	int x;
	printf("Input number: ");
	scanf("%d", &x);
	printf("Result %d * 5 = %d\n", x, x*5);
	return 0;
}