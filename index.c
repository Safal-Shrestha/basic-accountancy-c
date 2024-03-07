#include<stdio.h>

typedef struct details{
	char uname[25];
	char pw[25];
}creds;

int main()
{
	creds login, *auth;
	FILE *fptr;
	fptr=fopen("users.txt","ab+");
//	auth=(creds *)calloc(1*sizeof(creds));
	printf("Username: ");
	gets(login.uname);
	printf("Password: ");
	gets(login.pw);
	fwrite(&login,sizeof(creds),1,fptr);
}
