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

	// �Է��� ������ �� ����
	//(���α׷� �̸�, �Է����� �̸�, ����� ���� �̸�) 
	if(argc <= 2){	
		fprintf(stderr, "input format: LowCopy source_file dest_file\n");
		return 0;
	}

	// ���� ��Ʈ�� ���� 
	if((sourceFile = fopen(argv[1], "r")) == NULL){
		fprintf(stderr, "%s open error\n", argv[1]);
		return 0;
	}
	if((destFile = fopen(argv[2], "w")) == NULL){
		fprintf(stderr, "%s open error\n", argv[2]);
		return 0;
	}
	
	b = time(NULL);
	//������ block�� ũ�⸸ŭ �а�, �ٸ� ���Ͽ� �о�� ũ�⸸ŭ ��
	while((nread = fread(block, sizeof(char), sizeof(block)/sizeof(char), sourceFile)) > 0){
		c = time(NULL);
		if(c - b>=1){	//1�� ���� '. '�� ��� 
			fprintf(stdout, ". ");
			b = c;
			fflush(stdout);
		}
		fwrite(block, sizeof(char), nread, destFile);
	}
	
	//������ ���� ��Ʈ���� �ݱ�
	if(fclose(sourceFile) == EOF || fclose(destFile) == EOF){
		fprintf(stderr, "file close error\n");
		return 0;
	}

	printf("\n");
	return 0;
}
