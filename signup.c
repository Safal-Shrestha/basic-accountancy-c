#include<stdio.h>
#include<stdlib.h>

typedef struct login{
	char uname[25], pw[25];
}creds;

int main()
{
	FILE *fptr;
	creds auth;
	int no=1, readLoop=0, newSize=1;
	
	fptr=fopen("user.txt","ab+");
	
	printf("Username: ");
	gets(auth.uname);	
	printf("Password: ");
	gets(auth.pw);
	
	fwrite(&auth, sizeof(creds),1,fptr);
	
	system("index");

	
	fflush(fptr);
	fclose(fptr);
}