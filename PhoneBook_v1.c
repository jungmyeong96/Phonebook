#define _CRT_SECURE_NO_WARNINGS
#define swap(x, y, temp) ((temp) = (x), (x) = (y), (y) = (temp))
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACITY 100
#define BUFFER_SIZE 20

typedef struct _phonebook {

	char* names[CAPACITY];
	char* numbers[CAPACITY];
	

}phonebook;

void add();
void find();
void status();
void remove();
void save();
void load();
int search(char*a);

phonebook pb;
int n;

int main()
{
	

	char command[BUFFER_SIZE];
	while (1) {
		printf("$ ");
		scanf("%s", command);

		if (strcmp(command, "add") == 0)
			add();
		else if (strcmp(command, "load") == 0)
			load();
		else if (strcmp(command, "find") == 0)
			find();
		else if (strcmp(command, "status") == 0)
			status();
		else if (strcmp(command, "delete") == 0)
			remove();
		else if (strcmp(command, "save") == 0)
			save();

	}
	 
	return 0;
}
int search(char* a) 
{
	for (int i = 0; i < n; i++)
	{
		if (strcmp(pb.names[i], a) == 0)
			return i;
		else
			return -1;
	}
}

void add() {
	
	//scanf("%s", pb->names[n]);
	//scanf("%s", pb->numbers[n]);
	////디버그 오류뜸

	//printf("%s was added successfully.\n", pb->names[n]);

	//n++;
	
	char buf1[BUFFER_SIZE], buf2[BUFFER_SIZE];
	scanf("%s",buf1);
	scanf("%s",buf2);

	int i = n - 1;
	while (i >= 0 && strcmp(pb.names[i], buf1) > 0) {
		pb.names[i + 1] = pb.names[i];
		pb.numbers[i + 1] = pb.names[i];
		i--;
	}

	pb.names[i + 1] = _strdup(buf1); //strdup & strcpy의 차이는?? 
	pb.numbers[i + 1] = _strdup(buf2); //add는 지역변수기때문에 다른주소에 값을 담아야함
	
	n++;
	printf("%s was added successfully.\n", buf1);
	
}
void find() {
	char buf[BUFFER_SIZE];
	scanf("%s", &buf);

	for (int i = 0; i < n; i++) {
		if (strcmp(pb.names[i], buf) == 0)
		{
			printf("%s", pb.numbers[i]);
			return;
		}

		else {
			printf("No person named '%s' exists.", buf);
			return;
		}
	}

}
void status() {

	for (int i = 0; i < n; i++)
	{
		printf("%s %s\n", pb.names[i], pb.numbers[i]);
	}
	printf("Total %d persons. \n", n);

}
void remove() {

	char buf[BUFFER_SIZE];
	scanf("%s", buf);

	int index = search(buf);
	if (index == -1)
	{
		printf("No person named '%s' exists.\n", buf);
		return;
	}


	for (int j = index; j < n-1; j++)
	{
		pb.names[j] = pb.names[j+1];
		pb.numbers[j] = pb.numbers[j + 1];
	}

	n--;

	printf("'%s' was deleted successfully. \n", buf);

	return;

}

void load()
{
	char fileName[BUFFER_SIZE];
	char buf1[BUFFER_SIZE];
	char buf2[BUFFER_SIZE];

	scanf("%s", fileName);

	FILE* fp = fopen(fileName, "r");
	if (fp == NULL)
	{
		printf("Open failed.\n");
		return;
	}
	while ((fscanf(fp, "%s", buf1) != EOF)) {
		fscanf(fp, "%s", buf2);
		pb.names[n] = _strdup(buf1);
		pb.numbers[n] = _strdup(buf2);
		n++;
	}

	int tmp,j,i;
	char *temp;
	for (i = 0; i < n-1; i++) //선택정렬
	{
		tmp = i;

		for (j = i+1; j < n; j++) {
			if (strcmp(pb.names[j], pb.names[tmp]) == -1)
				tmp = j;
		}

		if (i != tmp) {
			temp = pb.names[i];
			pb.names[i] = pb.names[tmp];
			pb.names[tmp] = temp;

			temp = pb.numbers[i];
			pb.numbers[i] = pb.numbers[tmp];
			pb.numbers[tmp] = temp;
		}
	}

	printf("successed bringing data.\n");
	fclose(fp);
}

void save()
{
	int i;
	char fileName[BUFFER_SIZE];

	scanf("%s", fileName);

	FILE* fp = fopen(fileName, "w");
	if (fp == NULL) {
		printf("Open failed.\n");
		return;
	}

	for (i = 0; i < n; i++)
	{
		fprintf(fp, "%s %s\n", pb.names[i], pb.numbers[i]);
	}

	fclose(fp);
}