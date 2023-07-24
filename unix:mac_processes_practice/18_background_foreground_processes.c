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

// Topic: putting process to the background and bringing it back to the foreground

//bringing process to the background means actually stopping the process
//ctrl + z to stop the process, fg command to bring it to the foreground

//termination of the process means that the program reached an exit call or 
//reached a return statement inside its main

//stopping a process is more like closing the process 
//(in a state where it's stuck at a certain line of code which ever happens to be and it waits for a signal
//to continue it's execution)
//stopping in linux is basically like pausing

int main(int argc, char* argv[]){
	int x;
	printf("Input number: ");
	scanf("%d", &x);
	printf("Result %d * 5 = %d\n", x, x*5);
	return 0;

}
