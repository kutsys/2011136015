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

	/* dir�� ����� �̸��� ���丮�� ���� �׿� ���� ���丮 ��Ʈ���� ���� */
	if((dp = opendir(dir)) == NULL) {
		fprintf(stderr, "cannot open directory: %s\n", dir);
		return ;
	}
	
	/* ���� �۾� ���丮�� dir�� ���� */
	chdir(dir);

	/* dp�� ������ ���丮 ��Ʈ�� ���� ���� ���丮 �׸� ���� ����ü�� �����͸� entry�� ����.
	���޾� ȣ�������ν� ���� ���丮 �׸�鿡 ���ʷ� ������ �� �ִ�.*/
	while((entry = readdir(dp)) != NULL) {
		/* entry->d_name�� ����� �̸��� ���� ������ ���� ������ statbuf�� �����Ѵ�. */
		lstat(entry->d_name, &statbuf);

		/* ����� ������ ���� ������ ���� ���丮 ���θ� �˻� */
		if(S_ISDIR(statbuf.st_mode)) {
			/* Found a directory, but ignore . and .. */
			if(strcmp(".", entry->d_name) == 0 ||
				strcmp("..", entry->d_name) ==0) continue;

			/* ignore hidden directory*/
			if(entry->d_name[0]=='.') continue;			
	
			printf("%*s%s/\n", depth, "", entry->d_name);

			/* ���� ���丮�� ���� ���丮�� Ž���ϱ� ���� ���ȣ��.
			���� ���丮�� �鿩�����ϱ� ���� depth+4�� �����Ѵ�. */
			printdir(entry->d_name, depth+4);
		} else {
			
			// ignore hidden file	
			if(entry->d_name[0] == '.') continue;
			printf("%*s%s\n", depth, "", entry->d_name);
		}
	}

	/* printdir �Լ��� ���� ���� �۾��ϴ� ���丮�� �̵� */
	chdir("..");

	/* ���丮 ��Ʈ���� �ݰ� �׿� ������ �ڿ����� �����Ѵ�.
	���� �� 0, ���� �߻� �� -1�� ��ȯ�Ѵ�. */
	closedir(dp);
}


int main(){
	printf("Directory scan of ./:\n");
	printdir(".", 0);
	printf("done.\n");
	exit(0);
}
