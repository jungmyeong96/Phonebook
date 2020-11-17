//��ǥ: �߸��� ��ɾ ���ؼ� ������ �����Ѵ�.
//		���� �޸��Ҵ����� �迭�� ũ�⸦ Ű���.

#define _CRT_SECURE_NO_WARNINGS
#define swap(x, y, temp) ((temp) = (x), (x) = (y), (y) = (temp))
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 20
#define INIT_CAPACITY 3


char** names;
char** numbers;
	
int capacity = INIT_CAPACITY;
int n = 0;

char delim[] = " "; //strtok ����ϱ⵵�� tokenizing

void add(char* arg1, char* arg2);
void find(char* arg1);
void status();
void remove(char* arg1);
void save();
void load(char* arg1);
int search(char*a);
int read_line(char str[],int limit);
void init_derectory(); 
void process_command();
void reallocate();

int main()
{

	init_derectory(); //�迭 �����Լ�
	process_command();//������� ���ó��
	
	return 0;
}

void init_derectory() {
	names = (char**)malloc(INIT_CAPACITY * sizeof(char*));
	numbers = (char**)malloc(INIT_CAPACITY * sizeof(char*));
}

void process_command() {

	char command_line[BUFFER_SIZE]; //�� ������ ��ä�� �о���� ���� ����
	char* command, * argument1, * argument2;

	while (1) {
		printf("$ ");

		if (read_line(command_line, BUFFER_SIZE) <= 0) //��ɹ��� ��ä�� ����
			continue;

		command = strtok(command_line, delim); //ù���� ��ū�� ��ɾ��̴�.
		if (command == NULL) continue;

		if (strcmp(command, "add") == 0) {
			argument1 = strtok(NULL, delim);
			argument2 = strtok(NULL, delim);

			if (argument1 == NULL || argument2 == NULL) {
				printf("Invalid arguments.\n");
				continue;
			}

			add(argument1, argument2);
			printf("%s was added successfully. \n", argument1);
		}

		else if (strcmp(command, "load") == 0) {
			argument1 = strtok(NULL, delim);

			if (argument1 == NULL) {
				printf("File name required. \n");
				continue;
			}

			load(argument1);

		}

		else if (strcmp(command, "find") == 0){
			argument1 = strtok(NULL, delim);

			if (argument1 == NULL) {
				printf("Invalid arguments.\n");
				continue;
			}

			find(argument1);
		}

		else if (strcmp(command, "status") == 0)
			status();	

		else if (strcmp(command, "delete") == 0){
			argument1 = strtok(NULL, delim);

			if (argument1 == NULL) 
			{
				printf("Invalid arguments.\n");
				continue;
			}
			remove(argument1);
		}
		
		else if (strcmp(command, "save") == 0) {
			argument1 = strtok(NULL, delim);

			if (argument1 == NULL)
			{
				printf("Invalid arguments. \n");
				continue;
			}

			save(argument1);
		}
			

	}

}

void reallocate() {
	int i;

	capacity *= 2;

	char** tmp1 = (char**)malloc(capacity * sizeof(char*));
	char** tmp2 = (char**)malloc(capacity * sizeof(char*));

	for (i = 0; i < n; i++)
	{
		tmp1[i] = names[i];
		tmp2[i] = numbers[i];
	}

	free(names);// free�Լ��� �̿��Ͽ� ��ȯ������
	free(numbers);

	names = tmp1; //�迭�� �̸��� ������ �����̱⶧��
	numbers = tmp2;

}

int read_line(char str[], int limit) {	//line������ �Է��� fgets,getline
	int ch, i = 0;						//���� �Լ����� �̿��Ͽ� �� ���� ����	
	
	while ((ch = getchar()) != '\n')
		if (i < limit - 1) //���ڿ��� ���� '\0' ����
			str[i++] = ch;

	str[i] = '\0';

	return i;
}


int search(char* a) 
{
	for (int i = 0; i < n; i++)
	{
		if (strcmp( names[i], a) == 0)
			return i;
		else
			return -1;
	}
}

void add(char*arg1,char*arg2) {

	if (n >= capacity) //�迭�� ���� ��� ���Ҵ�
		reallocate();

	int i = n - 1;
	while (i >= 0 && strcmp( names[i], arg1) > 0) {
		 names[i + 1] =  names[i];
		 numbers[i + 1] =  names[i];
		i--;
	}

	 names[i + 1] = _strdup(arg1); //strdup & strcpy�� ���̴�?? 
	 numbers[i + 1] = _strdup(arg2); //add�� ���������⶧���� �ٸ��ּҿ� ���� ��ƾ���
	
	n++;
	
	
}

void find(char*agr1) {
	int index = search(agr1);
		
	if (index == -1)
		printf("No person named '%s' exists.", agr1);
	else
		printf("%s\n", numbers[index]);
}

void status() {

	for (int i = 0; i < n; i++)
	{
		printf("%s %s\n",  names[i],  numbers[i]);
	}
	printf("Total %d persons. \n", n);

}

void remove(char *arg1) {

	int index = search(arg1);
	if (index == -1)
	{
		printf("No person named '%s' exists.\n", arg1);
		return;
	}


	for (int j = index; j < n; j++)
	{
		 names[j] =  names[j+1];
		 numbers[j] =  numbers[j + 1];
	}
	n--;

	printf("'%s' was deleted successfully. \n", arg1);

	return;

}

void load(char*arg1)
{
	
	char buf1[BUFFER_SIZE];
	char buf2[BUFFER_SIZE];

	FILE* fp = fopen(arg1, "r");
	if (fp == NULL)
	{
		printf("Open failed.\n");
		return;
	}
	while ((fscanf(fp, "%s", buf1) != EOF)) {
		fscanf(fp, "%s", buf2);
		add(buf1, buf2);
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
		fprintf(fp, "%s %s\n",  names[i],  numbers[i]);
	}

	fclose(fp);
}

