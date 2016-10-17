#include <stdlib.h>
#include <stdio.h>
 
int main(int argc, char **argv) {
    char *value; 
    /* TEST_ENV란 이름의 환경변수에 변수값을 수정하거나 추가한다.
    수정되거나 새로 추가된 값은 실행 중인 프로그램에서만 유효하며 외부적으로는 변경되지 않는다.
    첫번째 인자는 환경 변수 이름, 두번째 인자는 환경변수의 값,
    세번째 인자가 0일 경우 환경변수가 이미 존재하면 변경하지 않고, 1이면 존재하더라도 값을 변경한다. */
    setenv("TEST_ENV", "1234", 0);   

    if((value = getenv("TEST_ENV")) != NULL){
            fprintf(stdout, "%s=%s\n", "TEST_ENV", value); 
    }
 
    return 0;
}
