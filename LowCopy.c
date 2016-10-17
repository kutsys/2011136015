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

	// �Է��� ������ �� ����
	//(���α׷� �̸�, �Է����� �̸�, ����� ���� �̸�) 
	if(argc <= 2){
		fprintf(stderr, "input format: LowCopy source_file dest_file\n");
		return 0;
	}

	//File descriptor�� ������
	if((sourceFile = open(argv[1], O_RDONLY)) == -1){
		fprintf(stderr, "%s open error\n", argv[1]);
		return 0;
	}
	if((destFile = open(argv[2], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)) == -1){
		fprintf(stderr, "%s open error\n", argv[2]);
		return 0;
	}

	b = time(NULL);	
	//������ ������
	while((nread = read(sourceFile, block, sizeof(block))) > 0){
		c = time(NULL);
		if(c - b >= 1){	//���� �ð�(1��)���� '. '�� ��� 
			fprintf(stdout, ". ");
			b = c;
			fflush(stdout);
		}
		write(destFile, block, nread);
	}
	

	//������ ���� �ݱ�
	if(close(sourceFile) == -1 || close(destFile)== -1){
		fprintf(stderr, "file close error\n");
		return 0;
	}

	printf("\n");
	return 0;
}
