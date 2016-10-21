#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

void alarmFunc(int sig){
	struct tm *ctime;
	time_t t;
	time(&t);
	ctime = localtime(&t);

	printf("%4d-%2d-%3d, %2d:%2d:%2d\n",
		ctime->tm_year+1900, ctime->tm_mon+1, ctime->tm_mday,
		ctime->tm_hour, ctime->tm_min, ctime->tm_sec);

	alarm(2);
}

int main(){
	(void) signal(SIGALRM, alarmFunc);

	alarm(2);	

	while(1){
		sleep(10);
	}

	return 0;
}
