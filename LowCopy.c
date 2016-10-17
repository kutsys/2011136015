#include <sys/stat.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>


int main(int argc, char **argv){
	int sourceFile, destFile;
	time_t b, c;
	int nread;
	char block[1024];

	// 입력이 부족할 때 실행
	//(프로그램 이름, 입력파일 이름, 복사될 파일 이름) 
	if(argc <= 2){
		fprintf(stderr, "input format: LowCopy source_file dest_file\n");
		return 0;
	}

	//File descriptor를 가져옴
	if((sourceFile = open(argv[1], O_RDONLY)) == -1){
		fprintf(stderr, "%s open error\n", argv[1]);
		return 0;
	}
	if((destFile = open(argv[2], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)) == -1){
		fprintf(stderr, "%s open error\n", argv[2]);
		return 0;
	}

	b = time(NULL);	
	//파일을 복사함
	while((nread = read(sourceFile, block, sizeof(block))) > 0){
		c = time(NULL);
		if(c - b >= 1){	//일정 시간(1초)마다 '. '을 출력 
			fprintf(stdout, ". ");
			b = c;
			fflush(stdout);
		}
		write(destFile, block, nread);
	}
	

	//열었던 파일 닫기
	if(close(sourceFile) == -1 || close(destFile)== -1){
		fprintf(stderr, "file close error\n");
		return 0;
	}

	printf("\n");
	return 0;
}
