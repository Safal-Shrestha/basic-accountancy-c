#include<stdio.h>
#include<stdlib.h>

typedef struct login{
	char uname[25], pw[25];
}creds;

creds *readStructure;

int main()
{
	FILE *fptr;
	creds auth;
	int no=1, readLoop=0, newSize=1;
	
	readStructure=(creds *)calloc(no,sizeof(creds));
	
	printf("Username: ");
	gets(auth.uname);	
	printf("Password: ");
	gets(auth.pw);	
	
	fptr=fopen("user.txt","ab+");
	
	fwrite(&auth, sizeof(creds), 1, fptr);
	
	rewind(fptr);
	
	while(fread((readStructure+readLoop), sizeof(creds),1,fptr)==1)
	{
		newSize++;
		readStructure=(creds *)realloc(readStructure, (newSize)*sizeof(creds));
		readLoop++;
	}
	
	for(int i=0; i<newSize-1;i++)
	{
		printf("\n\n%s\n%s",readStructure[i].uname,readStructure[i].pw);
	}
	
	
	fclose(fptr);	
	free(readStructure);
}