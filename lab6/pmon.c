#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio_ext.h>


void printH(){
	printf("Q: exit\n");
	printf("K: kill ptest\n");
	printf("S: start ptest\n");
	printf("R: restart ptest\n");
	printf("H: help\n");
	
}

//return ptest's pid
pid_t getPtestid(){
	FILE *p;
	int len, or=0, pid;
	int r;
	char buf[2][20];

	if((p = popen("ps -a", "r")) == NULL){
		printf("popen error\n");
	}

	while((len = fscanf(p, "%s%*s%*s%s", buf[0], buf[1])) > 0){
		if(!strcmp(buf[1], "ptest")){
			pclose(p);
			return (pid_t)atoi(buf[0]);
		}
	}
	
	pclose(p);

	return (pid_t)-1;
}

//SIGARLM
void ptestMon(int sig){
        pid_t pid = getPtestid();
        if(pid != -1)
                printf("\nrunning\n>>");
        else {
                printf("\nnot existed\n>>");
        }
	fflush(stdout);
        alarm(5);
}

int main(){
	char ch;
	pid_t pid;

	(void) signal(SIGALRM, ptestMon);
	alarm(5);

	while(1){
		printf(">>");
		ch = getchar();
		__fpurge(stdin);	

		switch(ch){
			case 'Q': case 'q':
				return 0;
				break;
			case 'K': case 'k':
				pid = getPtestid();
				if(pid != -1){
					kill(pid, SIGKILL);
				} else {
					printf("ptest is not running\n");
				}
				break;
			case 'S': case 's':
				if(getPtestid() == -1){
					system("./ptest &");
				} else {
					printf("already running");
				}
				break;
			case 'R': case 'r':
				pid = getPtestid();
				if(pid != -1){
					if(kill(pid, SIGKILL) == 0){
						system("./ptest &");
					}
				} else{
					printf("ptest is not existed\n");
				}
				break;
			case 'H': case 'h':
				printH();
				break;
			default :
				printf("command not found\n");
		}
	}


	return 0;
}
