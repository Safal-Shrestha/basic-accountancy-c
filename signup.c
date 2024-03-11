#include<stdio.h>
#include<stdlib.h>

typedef struct login{
	char uname[25], pw[25];
	int role;
}creds;

int main()
{
	system("cls");
	FILE *fptr;
	creds auth;
	int no=1, readLoop=0, newSize=1;
	
	fptr=fopen("user.txt","ab+");
	
	
	printf("Enter Sign Up Details:\n")
	printf("Username: ");
	gets(auth.uname);	
	printf("Password: ");
	gets(auth.pw);
	auth.role=1;
	
	fwrite(&auth, sizeof(creds),1,fptr);
	
	fflush(fptr);
	fclose(fptr);
}