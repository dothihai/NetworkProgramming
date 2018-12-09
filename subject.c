#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Subject{
	char id[20];
	char name[100];
}Subject;

Subject subject[100];

int total_subject = 0;

void readFileSubject(char *fname) {

	FILE *fp;
	char buf[1024];
	fp = fopen(fname,"r");
	int i = 0;
	while((fgets(buf,sizeof(buf),fp))!=NULL) {
		sscanf(buf, "%[^\t]%*c%[^\n]%*c", subject[i].id,subject[i].name);
		i++;
	}
	total_subject = i;
	
}


