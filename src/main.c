#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>

#define MAX_GUESS_NUM 1000

void usr1(){
	write(1, "usr1\n", 5);
}

void usr2(){
	write(1, "usr2\n", 5);
}

int main(){
	signal(SIGUSR1, usr1);
	signal(SIGUSR2, usr2);
	
	time_t start_time = time(NULL);
	int cnt_guesses = 0;	

	int cid = fork();
	if(!cid){
		//child here;
		while(1){
			kill(getppid(), SIGUSR2);
		}
	}

	//parent here;
	while(1){
		kill(cid, SIGUSR1);
	}
		
}
