#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include "../include/lib.h"
//#define MAX_GN 100000
//#define CYCLE 10

int rndnm(){
	return rand()%MAX_GN;
}

int follover(int pid, sigset_t *mask){
		sigval_t s_val;
		siginfo_t s_info;
		int sig;

		while(1){
			s_val.sival_int = rndnm()+1;
			sigqueue(pid, SIGRTMIN, s_val);
			sig = sigwaitinfo(mask, &s_info); 
			if(sig != SIGUSR1 && sig != SIGUSR2)
				continue;
			if(s_info.si_value.sival_int == 1){
				break;
			}
		}
		return 0;
}

int leader(int pid, sigset_t *mask){
	int tries, sig;
	time_t start = time(NULL);
	time_t end;
	sigval_t s_val;
	siginfo_t s_info;
	int gn = 0;
       	while(gn == 0)
       		gn= rand()%MAX_GN;

	while(1){
	
		sig = sigwaitinfo(mask, &s_info); 
		if(sig != SIGRTMIN)
			continue;
		tries++;
		if(s_info.si_value.sival_int == gn){
					s_val.sival_int = 1;
					sigqueue(pid, SIGUSR1, s_val);
					break;
		}
		s_val.sival_int = 0;
		sigqueue(pid, SIGUSR2, s_val);

	}
	end = time(NULL);
	printf("time %d\t", end-start);
	return tries;
}

