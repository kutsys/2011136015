#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <signal.h>
#include <stdlib.h>

void sigUSR1Handle(int sig){
	system("./ptest");
}


int main(){
	(void) signal(SIGUSR1, sigUSR1Handle);

	while(1){
		sleep(50);
	}
	return 0;
}
