#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv){
	FILE *sourceFile, *destFile; 
	int nread;						
	char block[1024];				
	time_t c, b;

	// 입력이 부족할 때 실행
	//(프로그램 이름, 입력파일 이름, 복사될 파일 이름) 
	if(argc <= 2){	
		fprintf(stderr, "input format: LowCopy source_file dest_file\n");
		return 0;
	}

	// 파일 스트림 생성 
	if((sourceFile = fopen(argv[1], "r")) == NULL){
		fprintf(stderr, "%s open error\n", argv[1]);
		return 0;
	}
	if((destFile = fopen(argv[2], "w")) == NULL){
		fprintf(stderr, "%s open error\n", argv[2]);
		return 0;
	}
	
	b = time(NULL);
	//파일을 block의 크기만큼 읽고, 다른 파일에 읽어온 크기만큼 씀
	while((nread = fread(block, sizeof(char), sizeof(block)/sizeof(char), sourceFile)) > 0){
		c = time(NULL);
		if(c - b>=1){	//1초 마다 '. '을 출력 
			fprintf(stdout, ". ");
			b = c;
			fflush(stdout);
		}
		fwrite(block, sizeof(char), nread, destFile);
	}
	
	//열었던 파일 스트림을 닫기
	if(fclose(sourceFile) == EOF || fclose(destFile) == EOF){
		fprintf(stderr, "file close error\n");
		return 0;
	}

	printf("\n");
	return 0;
}
