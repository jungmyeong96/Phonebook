#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main() {

	char str[] = "now # is the time # to strat preparing ### for the exam#"; //�迭 vs ������ == char array vs string literal == �������� vs �Ұ�
	char delim[] = "#"; //������ ����,delim��ü�� �ϳ��� string���� �־���
	char* token;

	token = strtok(str, delim); //ù��° ȣ�� 'n'�� �ּ�
	
	while (token != NULL) {
		printf("next token is: %s:%d\n", token, strlen(token));
		token = strtok(NULL, delim); //�̾��� ȣ��� �ι�° strtok�� �Ű������� null
	}


	//strtok�� delim�� ������ �� �������ּҿ� '\0'�� �ٿ��ش�
	//�׷��� ������ printf�� ��½� ��ū�� ����� �����ϴ�
	//(printf�� '\0'�� ������ �ν���)

	/*
	strtok�� ���� ���ڿ��� ��ȭ��Ų��('\0' ����)
	���� ���� ���� ���ڿ��� �����Ǿ�� �Ѵٸ� ������ �� strtok�� �ؾ��Ѵ�.
	strtok�� ���ο� �迭�� �������� �ʴ´�.
	�� strdup�ʹ� �ٸ���.
	*/

	return 0;
}
