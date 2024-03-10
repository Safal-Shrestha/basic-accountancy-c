#include<stdio.h>
#include<stdlib.h>

typedef struct login{
	char uname[25], pw[25];
	int role;
}creds;

int main()
{
	creds details;
	FILE *fptr;
	printf("Client\n");
	fptr=fopen("activeUser.txt","rb");
	rewind(fptr);
	fread(&details,sizeof(creds),1,fptr);
	printf("%s",details.uname);
	exit(0);
}