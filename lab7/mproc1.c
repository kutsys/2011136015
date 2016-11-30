#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <signal.h>
#include <limits.h>

#define NUM_OF_CHILD 10

int main(){
	pid_t pid[NUM_OF_CHILD];
	int count=0, i, j, res, pipe_id[NUM_OF_CHILD];
	char buf[NUM_OF_CHILD][8];
	
	printf("2011136015 김상균\n");

	for(i=0;i<NUM_OF_CHILD;i++){
		pid[i] = fork();

		if(pid[i] == -1){
			perror("fork failed"); return 0;
		} else if(pid[i] != 0){
			sprintf(&buf[i][2], "%d", pid[i]);
			buf[i][0] = '.'; buf[i][1] = '/';

			if(access(buf[i], F_OK)==-1){
				res = mkfifo(buf[i], 0777);
				if(res!=0) exit(EXIT_FAILURE);
			}

			pipe_id[i] = open(buf[i], O_RDONLY | O_NONBLOCK, 0777);
		} else {
			execl("./subproc", "subproc", (char *)0);
			break;
		}
	}

	while(i>0){
		usleep(100);
		for(j=0;j<NUM_OF_CHILD;j++){
			if(pid[j] == 0) continue;			
			count=0;
			res = read(pipe_id[j], &count, sizeof(count));
			if(count == 20){
				kill(pid[j], SIGKILL);
				close(pipe_id[j]);
				unlink(buf[j]);
				i--;
				fprintf(stdout,"%d: %d terminated\n", i, pid[j]);
				waitpid(pid[j], NULL, 0);
				pid[j] = 0;
				fflush(stdout);
			}
		}
	}

	printf("finished (process)\n");

	return 0;
}
