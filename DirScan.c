#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

void printdir(char *dir, int depth){
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;

	/* dir에 저장된 이름의 디렉토리를 열고 그에 대한 디렉토리 스트림을 생성 */
	if((dp = opendir(dir)) == NULL) {
		fprintf(stderr, "cannot open directory: %s\n", dir);
		return ;
	}
	
	/* 현재 작업 디렉토리를 dir로 변경 */
	chdir(dir);

	/* dp로 지정된 디렉토리 스트림 안의 다음 디렉토리 항목에 대한 구조체의 포인터를 entry에 저장.
	연달아 호출함으로써 여러 디렉토리 항목들에 차례로 접근할 수 있다.*/
	while((entry = readdir(dp)) != NULL) {
		/* entry->d_name에 저장된 이름을 갖는 파일의 상태 정보를 statbuf에 저장한다. */
		lstat(entry->d_name, &statbuf);

		/* 저장된 파일의 상태 정보를 통해 디렉토리 여부를 검사 */
		if(S_ISDIR(statbuf.st_mode)) {
			/* Found a directory, but ignore . and .. */
			if(strcmp(".", entry->d_name) == 0 ||
				strcmp("..", entry->d_name) ==0) continue;

			/* ignore hidden directory*/
			if(entry->d_name[0]=='.') continue;			
	
			printf("%*s%s/\n", depth, "", entry->d_name);

			/* 현재 디렉토리의 하위 디렉토리를 탐색하기 위한 재귀호출.
			하위 디렉토리를 들여쓰기하기 위해 depth+4를 전달한다. */
			printdir(entry->d_name, depth+4);
		} else {
			
			// ignore hidden file	
			if(entry->d_name[0] == '.') continue;
			printf("%*s%s\n", depth, "", entry->d_name);
		}
	}

	/* printdir 함수로 진입 전에 작업하던 디렉토리로 이동 */
	chdir("..");

	/* 디렉토리 스트림을 닫고 그에 연관된 자원들을 해제한다.
	성공 시 0, 오류 발생 시 -1을 반환한다. */
	closedir(dp);
}


int main(){
	printf("Directory scan of ./:\n");
	printdir(".", 0);
	printf("done.\n");
	exit(0);
}
