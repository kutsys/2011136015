#include <stdlib.h>
#include <stdio.h>
 
int main(int argc, char **argv) {
    char *str[4] = {"HOME", "PS1", "PATH", "LD_LIBRARY_PATH"};
    int i;
    char *value;
 
    for(i=0;i<4;i++){
        /* str[i]�� ����� �̸��� ȯ�溯�� ���� value�� ���� */
        if((value = getenv(str[i])) != NULL){
            fprintf(stdout, "%s=%s\n", str[i], value); 
        }
        else {    //value�� NULL�� ��� str[i]�� ����� �̸��� ȯ�溯���� ����.
            fprintf(stdout, "%s is nonexistent", str[i]);
        }
    }
 
    fprintf(stdout, "\n"); 
 
    return 0;
}
