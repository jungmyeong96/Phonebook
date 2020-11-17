//목표: 잘못된 명령어에 대해서 적절히 반응한다.
//		동적 메모리할당으로 배열의 크기를 키운다.

#define _CRT_SECURE_NO_WARNINGS
#define swap(x, y, temp) ((temp) = (x), (x) = (y), (y) = (temp))
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 100
#define INIT_CAPACITY 100

typedef struct person {
	char* name;
	char* number;
	char* email;
	char* group;
}Person;

int capacity = INIT_CAPACITY;

Person directory[INIT_CAPACITY];

int n = 0;

char delim[] = " "; //strtok 사용하기도함 tokenizing

void add(char* name, char* number, char* email, char* group);
void find(char* arg1);
void status();
void deleter(char *arg1);
void save(char* arg1);
void load(char* arg1);
int search(char*a);
int read_line(FILE* fp, char str[], int limit);
//void init_derectory(); 
void process_command();
int compose_name(char str[], int limit);
void handle_add(char* name);
void print_person(Person p);
//void reallocate();

int main()
{

	//init_derectory(); //배열 생성함수
	process_command();//사용자의 명령처리
	
	return 0;
}

//void init_derectory() {
//	names = (char**)malloc(INIT_CAPACITY * sizeof(char*));
//	numbers = (char**)malloc(INIT_CAPACITY * sizeof(char*));
//}

void process_command() {

	char command_line[BUFFER_SIZE]; //한 라인을 통채로 읽어오기 위한 버퍼
	char* command, * argument;
	char name_str[BUFFER_SIZE];

	while (1) {
		printf("$ ");

		if (read_line(stdin,command_line, BUFFER_SIZE) <= 0) //명령문을 통채로 읽음
			continue;

		command = strtok(command_line, delim); //첫번재 토큰은 명령어이다.
		if (command == NULL) continue;

		if (strcmp(command, "load") == 0) {
			argument = strtok(NULL, delim);

			if (argument == NULL) {
				printf("File name required. \n");
				continue;
			}

			load(argument);

		}

		else if (strcmp(command, "add") == 0) {

			if (compose_name(name_str, BUFFER_SIZE) <= 0) {
				printf("Invalid arguments.\n");
				continue;
			}

			handle_add(name_str);
		}



		else if (strcmp(command, "find") == 0) {

			if (compose_name(name_str, BUFFER_SIZE) <= 0) {
				printf("Invalid arguments.\n");
				continue;
			}

			find(name_str);
		}

		else if (strcmp(command, "status") == 0)
			status();

		else if (strcmp(command, "delete") == 0) {

			if (compose_name(name_str, BUFFER_SIZE) <= 0) {
				printf("Invalid arguments.\n");
				continue;
			}

			deleter(name_str);
		}

		else if (strcmp(command, "save") == 0) {
			argument = strtok(NULL, " ");

			if (argument == NULL) {
				printf("Invalid arguments.\n");
				continue;
			}
			save(argument);
		}
		else if (strcmp(command, "exit") == 0)
			break;

	}

}

//void reallocate() {
//	int i;
//
//	capacity *= 2;
//
//	char** tmp1 = (char**)malloc(capacity * sizeof(char*));
//	char** tmp2 = (char**)malloc(capacity * sizeof(char*));
//
//	for (i = 0; i < n; i++)
//	{
//		tmp1[i] = names[i];
//		tmp2[i] = numbers[i];
//	}
//
//	free(names);// free함수를 이용하여 반환시켜줌
//	free(numbers);
//
//	names = tmp1; //배열의 이름은 포인터 변수이기때문
//	numbers = tmp2;
//
//}
int compose_name(char str[], int limit)
{
	char* ptr;
	int length = 0;

	ptr = strtok(NULL, " ");
	if (ptr == NULL)
		return 0;

	strcpy(str, ptr);
	length += strlen(ptr);

	while ((ptr = strtok(NULL, " ")) != NULL) {
		if (length + strlen(ptr) + 1 < limit) {
			str[length++] = ' ';
			str[length] = '/0';
			strcat(str, ptr); // 두개의 str이 뒤에 '/0'을 가지고 있어야 작동
			length += strlen(ptr);
		}
	}
	return length;
}

void handle_add(char * name) {
	char number[BUFFER_SIZE], email[BUFFER_SIZE], group[BUFFER_SIZE];
	char empty[] = " ";

	printf(" Phone: ");
	read_line(stdin, number, BUFFER_SIZE);

	printf(" Email: ");
	read_line(stdin, email, BUFFER_SIZE);

	printf(" Group: ");
	read_line(stdin, group, BUFFER_SIZE);

	add(name, (char*)(strlen(number) > 0 ? number : empty),
		(char*)(strlen(email) > 0 ? email : empty),
		(char*)(strlen(group) > 0 ? group : empty));
	//
}

int read_line(FILE * fp,char str[], int limit) {	//line단위의 입력은 fgets,getline
	int ch, i = 0;						//등의 함수들을 이용하여 할 수도 있음	
	
	while ((ch = fgetc(fp)) != '\n' && ch != EOF)
		if (i < limit-1) //문자열의 끝에 '\0' 때문
			str[i++] = ch;

	str[i] = '\0';

	return i;
}


int search(char* a) 
{
	for (int i = 0; i < n; i++)
	{
		if (strcmp(a,directory[i].name) == 0)
			return i;
	}
	return -1;
}


void print_person(Person p)
{
	printf("%s:\n", p.name);
	printf("	Phone: %s:\n", p.number);
	printf("	Email: %s:\n", p.email);
	printf("	Group: %s:\n", p.group);
}

void add(char*name,char*number,char*email,char* group) {

	int i = n - 1;
	while (i >= 0 && strcmp( directory[i].name, name) > 0) {
		 directory[i + 1] =  directory[i];
		i--;
	}

	 directory[i + 1].name = _strdup(name);
	 directory[i + 1].number = _strdup(number);
	 directory[i + 1].email = _strdup(email);
	 directory[i + 1].group = _strdup(group);
	n++;
}

void find(char*agr1) {
	int index = search(agr1);
	if (index == -1)
		printf("No person named '%s' exists.", agr1);
	else
		print_person(directory[index]);
}

void status() {

	for (int i = 0; i < n; i++)
	{
		print_person(directory[i]);
	}
	printf("Total %d persons. \n", n);

}

void deleter(char *arg1) {

	int index = search(arg1);
	if (index == -1)
	{
		printf("No person named '%s' exists.\n", arg1);
		return;
	}


	for (int j = index; j < n; j++)
	{
		 directory[j] =  directory[j + 1];
	}
	n--;

	printf("'%s' was deleted successfully. \n", arg1);


}

void load(char*arg1)
{
	char buf[BUFFER_SIZE];
	char* name, * number, * email, * group;

	FILE* fp = fopen(arg1, "r");
	if (fp == NULL)
	{
		printf("Open failed.\n");
		return;
	}

	while (1) {
		if (read_line(fp, buf, BUFFER_SIZE) <= 0)
			break;
		name = strtok(buf, "#");
		number = strtok(NULL, "#");
		email = strtok(NULL, "#");
		group =	strtok(NULL, "#");
		add(name, number, email, group);
	}

	printf("successed bringing data.\n");
	fclose(fp);
}

void save(char *arg1)
{
	int i;
	FILE* fp = fopen(arg1, "w");
	if (fp == NULL) {
		printf("Open failed.\n");
		return;
	}

	for (i = 0; i < n; i++)
	{
		fprintf(fp, "%s#", directory[i].name);
		fprintf(fp, "%s#", directory[i].number);
		fprintf(fp, "%s#", directory[i].email);
		fprintf(fp, "%s#\n", directory[i].group);
	}

	fclose(fp);
}

