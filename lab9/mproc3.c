#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>

#define NUM_OF_THREAD 10

pthread_mutex_t mymutex;
int min_count=0,res=0,num_of_thread=0;
pthread_t tid[NUM_OF_THREAD];

void* subproc(void *arg){
	int *count= (int *)arg;
	int isMutex = 0, j, num=0;
	struct tm *t;
	time_t timer;

	while(1){
		sleep(rand()%10);
		while(1){
			pthread_mutex_lock(&mymutex);
			if((*count)<=min_count || (*count) != -1) break;
			pthread_mutex_unlock(&mymutex);	
		}
		
		timer = time(NULL);
		t = localtime(&timer);
		
		(*count)++;
		printf("%lu, %d:%d:%d, %d\n", pthread_self(), t->tm_hour, t->tm_min, t->tm_sec, *count);	
		fflush(stdout);
	
		for(j=0, num=0;j<NUM_OF_THREAD;j++){
			if(tid[j] != -1) num++;
		}
		res = (res+1)%num;
		if(res == 0) min_count++;

		pthread_mutex_unlock(&mymutex);
	}
	return NULL;
}

int isThread(){
	FILE *p;
	int count =0, len;
	char *re;
	char buf[3][15];

	if((p = popen("ps -aL", "r")) == NULL){
		printf("popen error\n");
	}

	while((len = fscanf(p, "%s %s %*s %*s", buf[0], buf[1])) > 0 && (re = fgets(buf[2], 15, p))!=NULL){
		if((strcmp(buf[2], " mproc3\n") == 0)
			 && (strcmp(buf[0], buf[1]) != 0)){
			count++;
		}
	}
	pclose(p);
	return count;
}

int main(){
	int res, j, i;
	int count[NUM_OF_THREAD]={0};

	pthread_mutex_init(&mymutex, NULL);

	srand(time(NULL));

	printf("2011136015 김상균\n");
	
	for(i=0;i<NUM_OF_THREAD;i++){
		res = pthread_create(&tid[i], NULL, subproc, &count[i]);
		pthread_detach(tid[i]);
		num_of_thread++;
		if(res != 0){
			num_of_thread--;
			perror("Thread creation failed"); exit(EXIT_FAILURE);
		}
	}	
	i=0;
	while(1){
		if(res == 0)num_of_thread = isThread();
		if(num_of_thread == 0) break;
		usleep(200);
		for(j=0;j<NUM_OF_THREAD;j++){
			if(tid[j] == -1) continue;

			if(count[j] >= 20){
				i++;
				pthread_cancel(tid[j]);
				printf("%d : %lu terminated\n", i, tid[j]);
				tid[j] = -1;
				count[j] = -1;
			}
		}
	}	

	printf("finished (thread)\n");
	pthread_mutex_destroy(&mymutex);
	return 0;
}
