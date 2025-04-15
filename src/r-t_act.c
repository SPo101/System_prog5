#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <string.h>

#define MAX_GUESS_NUM 1000
#define SIGRTMIN 34

void handler(int signum, siginfo_t *siginfo, void *context){
	char buff[1024];
	memset(&buff, 0, 1024);
	sprintf(buff, "%d\n", siginfo->si_value.sival_int);
	write(1, buff, 1024);
}

int main(){
	struct sigaction act;
	
	memset(&act, 0, sizeof(act));
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = handler;

	sigaction(SIGRTMIN, &act, NULL);
	union sigval sigval;
	

	int cid = fork();
	if(!cid){
		//child here;
		while(1){
		}
	}

	//parent here;
	while(1){
		sigval.sival_int = 10;
		sigqueue(cid, SIGRTMIN, sigval);
	}
		
}
