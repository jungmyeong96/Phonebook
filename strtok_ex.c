#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main() {

	char str[] = "now # is the time # to strat preparing ### for the exam#"; //배열 vs 포인터 == char array vs string literal == 수정가능 vs 불가
	char delim[] = "#"; //구분자 설정,delim자체도 하나의 string으로 주어짐
	char* token;

	token = strtok(str, delim); //첫번째 호출 'n'의 주소
	
	while (token != NULL) {
		printf("next token is: %s:%d\n", token, strlen(token));
		token = strtok(NULL, delim); //이어진 호출들 두번째 strtok의 매개변수는 null
	}


	//strtok은 delim로 구분한 뒤 마지막주소에 '\0'을 붙여준다
	//그렇기 때문에 printf로 출력시 토큰이 출력이 가능하다
	//(printf는 '\0'를 끝으로 인식함)

	/*
	strtok은 원본 문자열을 변화시킨다('\0' 삽입)
	따라서 만약 원본 문자열이 보존되어야 한다면 복사한 후 strtok을 해야한다.
	strtok은 새로운 배열을 생성하지 않는다.
	즉 strdup와는 다르다.
	*/

	return 0;
}
