#include <stdlib.h>
#include <stdio.h>
 
int main(int argc, char **argv) {
    char *str[4] = {"HOME", "PS1", "PATH", "LD_LIBRARY_PATH"};
    int i;
    char *value;
 
    for(i=0;i<4;i++){
        /* str[i]에 저장된 이름의 환경변수 값을 value에 저장 */
        if((value = getenv(str[i])) != NULL){
            fprintf(stdout, "%s=%s\n", str[i], value); 
        }
        else {    //value가 NULL일 경우 str[i]에 저장된 이름의 환경변수가 없음.
            fprintf(stdout, "%s is nonexistent", str[i]);
        }
    }
 
    fprintf(stdout, "\n"); 
 
    return 0;
}
