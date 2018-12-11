#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "subject.c"
#include "account.c"

typedef struct Transcript
{
	char mssv[20];
	char id_subject[20];
	float giua_ki;
	float cuoi_ki;
	char diem_chu[5];
}Transcript;

Transcript transcript[100];

int total_transcript = 0;

void readFileTranscript(char *fname) {

	FILE *fp;
	char buf[1024];
	fp = fopen(fname,"r");
	int i = 0;
	while((fgets(buf,sizeof(buf),fp))!=NULL) {
		sscanf(buf, "%[^\t]%*c%[^\t]%*c%f%f%*c%[^\n]%*c", 
			transcript[i].mssv,
			transcript[i].id_subject, 
			&transcript[i].giua_ki,
			&transcript[i].cuoi_ki,
			transcript[i].diem_chu);
		i++;
	}
	total_transcript = i;
}

char* getNameSubject(char * name, char id_subject[10]){
	

	for (int i = 0; i < total_subject; ++i)
	{
		if(strcmp(id_subject,subject[i].id) == 0){
			sprintf(name, "%-50s", subject[i].name);
			// strcpy(name, subject[i].name);
			return name;
		}
	}
	return NULL;
}

void getTableSubjectOfStudent(char * mssv, char * id_subject,  char * temp){
	printf("%s\n",mssv);
	int flag = 0;
	for (int i = 0; i < total_transcript; ++i)
	{
		printf("\n>>%d\n", i);
		if ((strcmp(transcript[i].mssv, mssv) == 0))
		{
			if (!flag)
			{
				flag = (id_subject == NULL); // flag to get All subject
			}
			if (!flag)
			{
				flag = (strcmp(id_subject, transcript[i].id_subject) == 0); //flag to get spectified subject
			}
			if (flag)
			{				
				char xxx[1000];
				sprintf(xxx, "%s %f %f %s$", 
					transcript[i].id_subject, 
					transcript[i].giua_ki, 
					transcript[i].cuoi_ki, 
					transcript[i].diem_chu);
				printf("%s\n", xxx);
				strcat(temp, xxx);
			}
			flag = 0;
		}
	}
	puts("end");
}
int checkMarkOfStudent(char mssv[20]){

	for (int i = 0; i < total_transcript; ++i)
	{
		if(strcmp(mssv,transcript[i].mssv) == 0)
			return 1;
	}
	return 0;
}

int checkIdSubject(char id_subject[20]){

	for (int i = 0; i < total_subject; ++i)
	{
		if(strcmp(id_subject,subject[i].id)==0)
			return 1;
	}
	return 0;
}

Transcript *searchByIdSubject(char mssv[20],char id_subject[20]){

	for (int i = 0; i < total_transcript; ++i)
	{
		if(checkMarkOfStudent(mssv) == 1 && checkIdSubject(id_subject) == 1)
			return &transcript[i];
	}
	return NULL;
}


/*
int main(int argc, char const *argv[])
{
	readFileSubject("subject.txt");
	readFileTranscript("transcript.txt");
	printf("%d\n",checkMarkOfStudent("20153979"));
	return 0;
}*/