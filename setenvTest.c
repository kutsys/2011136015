#include <stdlib.h>
#include <stdio.h>
 
int main(int argc, char **argv) {
    char *value; 
    /* TEST_ENV�� �̸��� ȯ�溯���� �������� �����ϰų� �߰��Ѵ�.
    �����ǰų� ���� �߰��� ���� ���� ���� ���α׷������� ��ȿ�ϸ� �ܺ������δ� ������� �ʴ´�.
    ù��° ���ڴ� ȯ�� ���� �̸�, �ι�° ���ڴ� ȯ�溯���� ��,
    ����° ���ڰ� 0�� ��� ȯ�溯���� �̹� �����ϸ� �������� �ʰ�, 1�̸� �����ϴ��� ���� �����Ѵ�. */
    setenv("TEST_ENV", "1234", 0);   

    if((value = getenv("TEST_ENV")) != NULL){
            fprintf(stdout, "%s=%s\n", "TEST_ENV", value); 
    }
 
    return 0;
}
