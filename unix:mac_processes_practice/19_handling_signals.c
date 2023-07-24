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

void handle_sigcont(int sig){
    printf("Input number: ");
    //to make sure that line will be printed on the screen
    fflush(stdout);
}

//changing the way we are handling signals

int main(int argc, char* argv[]){
    //insige if the sigaction structure we can tell it how we want it to handle the signal
    struct sigaction sa;
    //first we want to set up a function that is going to be called whenever we receive a certain signal
    sa.sa_handler = &handle_sigcont;
    //sa.sa_handler = &handle_sigtstp;
    //because we use the combination of sigtstp and scanf, better to use flag
    sa.sa_flags = SA_RESTART;
    //next step is to hook this sigaction to the proper signal
    //sigaction is a function that takes in the signal, if we had sigaction set beforehand, it will set it
    //as the third parameter
    sigaction(SIGCONT, &sa, NULL);
    //sigaction(SIGTSTP, &sa, NULL);

	int x;
	printf("Input number: ");
	scanf("%d", &x);
	printf("Result %d * 5 = %d\n", x, x*5);
	return 0;
}