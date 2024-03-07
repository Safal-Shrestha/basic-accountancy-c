#include<stdio.h>
#include<stdlib.h>

typedef struct details{
	char uname[25];
	char pw[25];
}creds;

int main()
{
	creds login, *auth;
	FILE *fptr;
	int i=0;
	fptr=fopen("users.txt","ab+");
	auth=(creds *)calloc(1,sizeof(creds));
//	printf("Username: ");
//	gets(login.uname);
//	printf("Password: ");
//	gets(login.pw);
//	fwrite(&login,sizeof(creds),1,fptr);
	fseek(fptr,0,SEEK_SET);
	
	for(i=0;fread(auth,sizeof(creds),1,fptr)==1;i++)
	{
		auth=(creds *)realloc(auth,(i+1)*sizeof(creds));
	}
//	
//	fread(auth,sizeof(creds),2,fptr);
//	auth=(creds *)realloc(auth,i+1*(sizeof(creds)));
	
	printf("uname: %s\npw: %s\n",auth[0].uname,auth[0].pw);
}
