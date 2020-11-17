char* strdup(char* s)
{
	char* p;
	p = (char*)malloc(strlen(s) + 1);
	if (p != NULL)
		strcpy(p, s);
	return p;
}

//새 메모리를 만든 다음 그 주소에 값을 복제한 뒤
//새 메모리 주소를 리턴