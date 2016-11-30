#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>

#define NUM_OF_THREAD 10


void* subproc(void *arg){
	int *count= (int *)arg;
	struct tm *t;
	time_t timer;

	while(1){
		sleep(rand()%10);

		timer = time(NULL);
		t = localtime(&timer);
		
		(*count)++;
		printf("%lu, %d:%d:%d, %d\n", pthread_self(), t->tm_hour, t->tm_min, t->tm_sec, *count);	
		fflush(stdout);
	}
	return NULL;
}


int main(){
	int res, i, j;
	pthread_t tid[NUM_OF_THREAD];
	int count[NUM_OF_THREAD];

	srand(time(NULL));

	printf("2011136015 \n");
	
	for(i=0;i<NUM_OF_THREAD;i++){
		res = pthread_create(&tid[i], NULL, subproc, &count[i]);
		pthread_detach(tid[i]);
		if(res != 0){
			perror("Thread creation failed"); exit(EXIT_FAILURE);
		}
	}	

	while(i>0){
		usleep(500);
		for(j=0;j<NUM_OF_THREAD;j++){
			if(tid[j] == -1) continue;

			if(count[j] >= 20){
				pthread_cancel(tid[j]);
				i--;
				tid[j] = -1;
			}
		}
	}	

	printf("finished (thread)\n");

	return 0;
}
