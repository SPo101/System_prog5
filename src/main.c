#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

#include "../include/lib.h"

int main(){
	srand(time(NULL));

	sigset_t mask;
	sigfillset(&mask);
	sigdelset(&mask, SIGINT);
	sigdelset(&mask, SIGTERM);
	sigprocmask(SIG_SETMASK, &mask, NULL);
	

	int pid = fork();
	int (*player[2])(int, sigset_t *) = {follover, leader};
	int tries;

	if(!pid){
		for(int i=0; i<CYCLE; i++){
			tries = player[i%2](getppid(), &mask);
			if(i%2==1)
				printf("RES_ch - %d\n", tries);
		}

	}
	if(pid){
		for(int i=0; i<CYCLE; i++){
			tries = player[(i+1)%2](pid, &mask);
			if((i+1)%2==1)
				printf("RES_pr - %d\n", tries);
		}

	}

	exit(EXIT_SUCCESS);
}

