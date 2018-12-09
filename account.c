#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Account{
	char mssv[20];
	char password[50];
	char name[50];	
}Account;

Account account[100];
Account accountLogin;

int total_account = 0;

void readFileAccount(char *fname) {

	FILE *fp;
	char buf[1024];
	fp = fopen(fname,"r");
	int i = 0;
	while((fgets(buf,sizeof(buf),fp))!=NULL) {
		sscanf(buf, "%[^\t]%*c%[^\t]%*c%[^\n]%*c", account[i].mssv,account[i].password, account[i].name);
		i++;
	}
	total_account = i;
	
}

int checkLogin(Account acc){
	for (int i = 0; i < total_account; ++i)
	{
		if(strcmp(acc.mssv,account[i].mssv)==0&&strcmp(acc.password,account[i].password)==0){
			strcpy(accountLogin.mssv,acc.mssv);
			strcpy(accountLogin.name,account[i].name);
			return 1;
		}
	}
	return 0;
}
