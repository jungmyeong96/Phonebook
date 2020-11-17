//��ǥ: �߸��� ��ɾ ���ؼ� ������ �����Ѵ�.
//		���� �޸��Ҵ����� �迭�� ũ�⸦ Ű���.

#define _CRT_SECURE_NO_WARNINGS
#define swap(x, y, temp) ((temp) = (x), (x) = (y), (y) = (temp))
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 100
#define INIT_CAPACITY 100

typedef struct person {  //pass by assignment
	char* name;
	char* number;
	char* email;
	char* group;
}Person;

int capacity;
Person ** directory;
int n = 0;

void init()
{
	directory = (Person**)malloc(INIT_CAPACITY * sizeof(Person*));
	capacity = INIT_CAPACITY;
}

char delim[] = " "; //strtok ����ϱ⵵�� tokenizing

void add(char* name, char* number, char* email, char* group);
void find(char* arg1);
void status();
void deleter(char *arg1);
void release_person(Person* p);
void save(char* arg1);
void load(char* arg1);
int search(char*a);
int read_line(FILE* fp, char str[], int limit);
//void init_derectory(); 
void process_command();
int compose_name(char str[], int limit);
void handle_add(char* name);
void print_person(Person p);
void reallocate();
//void reallocate();

int main()
{
	init();
	//init_derectory(); //�迭 �����Լ�
	process_command();//������� ���ó��
	
	return 0;
}

//void init_derectory() {
//	names = (char**)malloc(INIT_CAPACITY * sizeof(char*));
//	numbers = (char**)malloc(INIT_CAPACITY * sizeof(char*));
//}

void process_command() {

	char command_line[BUFFER_SIZE]; //�� ������ ��ä�� �о���� ���� ����
	char* command, * argument;
	char name_str[BUFFER_SIZE];

	while (1) {
		
		printf("$ ");

		if (read_line(stdin,command_line, BUFFER_SIZE) <= 0) //��ɹ��� ��ä�� ����
			continue;

		command = strtok(command_line, delim); //ù���� ��ū�� ��ɾ��̴�.
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
			str[length] = '\0';
			strcat(str, ptr); // �ΰ��� str�� �ڿ� '/0'�� ������ �־�� �۵�
			length += strlen(ptr);
		}
	}
	return length;
}

void handle_add(char * name) {
	char number[BUFFER_SIZE], email[BUFFER_SIZE], group[BUFFER_SIZE];

	printf(" Phone: ");
	read_line(stdin, number, BUFFER_SIZE);

	printf(" Email: ");
	read_line(stdin, email, BUFFER_SIZE);

	printf(" Group: ");
	read_line(stdin, group, BUFFER_SIZE);

	add(_strdup(name), (char*)(strlen(number) > 0 ? _strdup(number) : NULL),
		(char*)(strlen(email) > 0 ? _strdup(email) : NULL),
		(char*)(strlen(group) > 0 ? _strdup(group) : NULL));
	//
}

int read_line(FILE * fp,char str[], int limit) {	//line������ �Է��� fgets,getline
	int ch, i = 0;						//���� �Լ����� �̿��Ͽ� �� ���� ����	
	
	while ((ch = fgetc(fp)) != '\n' && ch != EOF)
		if (i < limit-1) //���ڿ��� ���� '\0' ����
			str[i++] = ch;

	str[i] = '\0';

	return i;
}


int search(char* a) 
{
	for (int i = 0; i < n; i++)
	{
		if (strcmp(a,directory[i]->name) == 0)
			return i;
	}
	return -1;
}


void print_person(Person *p)
{
	printf("%s\n", (*p).name); //.�� �켱������ ���⶧���� ������ *�� ��ȣ�� ����� ex)(*p).name
	printf("	Phone: %s\n", (*p).number);
	printf("	Email: %s\n", p->email);
	printf("	Group: %s\n", p->group);
}

void add(char*name,char*number,char*email,char* group) {

	if (n >= capacity)
		reallocate();

	int i = n - 1;
	while (i >= 0 && strcmp( directory[i]->name, name) > 0) 
	{
		directory[i + 1] =  directory[i];
		i--;
	}

	directory[i + 1] = (Person*)malloc(sizeof(Person)); //�ſ��߿� �ּҸ� �þ���� ����ü �޸𸮰��ϳ� �Ҵ��������

	directory[i + 1]->name = name;
	directory[i + 1]->number = number;
	directory[i + 1]->email = email;
	directory[i + 1]->group = group;
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

	Person* p = directory[index]; //�ּҸ� �Űܵΰ�
	for (int j = index; j < n; j++)
	{
		 directory[j] =  directory[j + 1];
	}
	n--;

	release_person(p); // malloc���� �Ҵ�� �޸𸮰��� free�����ش�

	printf("'%s' was deleted successfully. \n", arg1);


}

void release_person(Person *p) { //strdup�ϸ� �ϳ��ϳ� malloc �ȰŶ� ����ü�ȿ� �ִ� ���빰�� free�������
	free(p->name);
	if (p->number != NULL) free(p->number);
	if (p->email != NULL) free(p->email);
	if (p->group != NULL) free(p->group);
	free(p);
}

void load(char*arg1)
{
	char buf[BUFFER_SIZE];
	char* name, * number, * email, * group, *token;

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
		token = strtok(NULL, "#");
		if (strcmp(token, " ") == 0)
			number = NULL;
		else
			number = _strdup(token); //file�� ������ ���� ������ϱ� strdup�ؾ��� �� �־����մ��� �ñ����ϰ��־���
		token = strtok(NULL, "#");
		if (strcmp(token, " ") == 0)
			email = NULL;
		else
			email = _strdup(token);
		token = strtok(NULL, "#");
		if (strcmp(token, " ") == 0)
			group = NULL;
		else
			group = _strdup(token);
		
		add(_strdup(name), number, email, group);
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
		fprintf(fp, "%s#", directory[i]->name);
		if(directory[i]->number == NULL)
			fprintf(fp, " #");
		else
			fprintf(fp, "%s#", directory[i]->number);
		if(directory[i]->email == NULL)
			fprintf(fp, " #");
		else
			fprintf(fp, "%s#", directory[i]->email);
		if(directory[i]->group == NULL)
			fprintf(fp, " #");
		else
			fprintf(fp, "%s#\n", directory[i]->group);
	}

	fclose(fp);
}

void reallocate() 
{
	capacity *= 2;
	Person** tmp = (Person**)malloc(capacity * sizeof(Person*));
	for (int i = 0; i < n; i++)
		tmp[i] = directory[i];
	free(directory);
	directory = tmp;
}


